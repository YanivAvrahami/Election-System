#include "State.h"

#include <iostream>
#include <vector>
#include "Election.h"
#include "Counter.h"
#include "Citizen.h"
#include "Party.h"
#include "UnifiedState.h"

namespace elec
{
	int State::_instances = 0;

	State::State(std::string name, const int numRepresentatives, Election* election)
		: _name(name), _numOfElectors(numRepresentatives), _serial(_instances++), _election(election) 
	{
		if (numRepresentatives < 0)
			throw std::invalid_argument("Error: invalid number of representatives");
	}

	State::State()
		: _election(nullptr), _numOfElectors(0), _serial(_instances++)
	{}

	void State::save(std::ostream& out) const
	{
		int size = _name.size();
		out.write(rcastccp(&size), sizeof(size));
		out.write(rcastccp(&_name[0]), size);
		
		out.write(rcastccp(&_instances), sizeof(_instances));
		out.write(rcastccp(&_serial), sizeof(_serial));
		out.write(rcastccp(&_numOfElectors), sizeof(_numOfElectors));

		try
		{
			_votesCounter.save(out);
		}
		catch(std::exception& err)
		{
			throw;
		}
		
		if (!out.good())
			throw std::exception("Error: bad writing");
	}

	void State::load(std::istream& in)
	{
		int size;
		in.read(rcastcp(&size), sizeof(size));
		_name.resize(size);
		in.read(rcastcp(&_name[0]), size);

		in.read(rcastcp(&_instances), sizeof(_instances));
		in.read(rcastcp(&_serial), sizeof(_serial));
		in.read(rcastcp(&_numOfElectors), sizeof(_numOfElectors));

		try
		{
			_votesCounter.load(in);
		}
		catch (std::exception& err)
		{
			throw;
		}

		if (!in.good())
			throw std::exception("Error: bad reading");
	}

	void State::saveStateCitizensIDs(std::ostream& out) const
	{
		int size = _citizens.size();
		out.write(rcastccp(&size), sizeof(size));

		for (int i = 0; i < _citizens.size(); ++i)
		{
			int id = _citizens[i]->getID();
			out.write(rcastccp(&id), sizeof(id));
		}

		if (!out.good())
			throw std::exception("Error: bad writing");
	}

	void State::saveElectorsByPartyIDs(std::ostream& out) const
	{
		int size = _electorsByParty.size();
		out.write(rcastccp(&size), sizeof(size));

		for (int i = 0; i < _electorsByParty.size(); ++i)
		{
			int size = _electorsByParty[i].size();
			out.write(rcastccp(&size), sizeof(size));

			for (int j = 0; j < _electorsByParty[i].size(); ++j)
			{
				int id = _electorsByParty[i][j]->getID();
				out.write(rcastccp(&id), sizeof(id));
			}
		}

		if (!out.good())
			throw std::exception("Error: bad writing");
	}

	void State::loadCitizensPointers(std::istream& in)
	{
		int size;
		in.read(rcastcp(&size), sizeof(size));
		for (int i = 0; i < size; ++i)
		{
			int id;
			in.read(rcastcp(&id), sizeof(id));

			try
			{
				_citizens.push_back(_election->findCitizen(id));
			}
			catch(std::exception& err)
			{
				throw;
			}
		}

		if (!in.good())
			throw std::exception("Error: bad reading");
	}

	void State::loadElectorsByPartyPointers(std::istream& in)
	{
		int sizeOf2DVec;
		in.read(rcastcp(&sizeOf2DVec), sizeof(sizeOf2DVec));
		_electorsByParty.resize(sizeOf2DVec);
		for (int i = 0; i < sizeOf2DVec; ++i)
		{
			int currSize;
			in.read(rcastcp(&currSize), sizeof(currSize));
			for (int j = 0; j < currSize; ++j)
			{
				int id;
				in.read(rcastcp(&id), sizeof(id));
				try
				{
					_electorsByParty[i].push_back(_election->findCitizen(id));
				}
				catch (std::exception& err)
				{
					throw;
				}
			}
		}

		if (!in.good())
			throw std::exception("Error: bad reading");
	}

	std::ostream& operator<<(std::ostream& os, const State& other)
	{
		other.print(os);

		return os;
	}

	void State::addCitizen(Citizen* citizen)
	{
		_citizens.push_back(citizen);
	}

	void State::addPartyElector(Citizen* citizen, int partySerial)
	{
		_electorsByParty[partySerial].push_back(citizen);
	}

	int State::getCurrentNumOfElectors() const
{
		int count = 0;
		for (auto elem : _electorsByParty)
			count += elem.size();
		return count;
	}

	float State::getVotePercentage() const
	{
		return (_votesCounter.getTotal() / (float)_citizens.size()) * 100;
	}

	const elec::Party& State::getLocalWinningParty() const
{
		int partiesSize = _election->getParties().size();
		int winningPartyIndex = 0;
		for (int i = 1; i < partiesSize; ++i) {
			//if next party has more electors, or they are equal but next party has lower serial number
			if (getNumOfElectorsToGrantParty(i) > getNumOfElectorsToGrantParty(winningPartyIndex) ||
				getNumOfElectorsToGrantParty(i) == getNumOfElectorsToGrantParty(winningPartyIndex) &&
				_election->findParty(i)->getSerial() < _election->findParty(winningPartyIndex)->getSerial())
			{
				winningPartyIndex = i;
			}
		}
		return *_election->findParty(winningPartyIndex);
	}

	int State::getNumOfElectorsToGrantParty(int partySerial) const
	{
		float partyVoteRatio = _votesCounter.get(partySerial) / (float)_votesCounter.getTotal();
		return (int)round(partyVoteRatio * _numOfElectors);
	}

	std::vector<Citizen*>* State::getLocalFinalElectors()
	{
		std::vector<Citizen*>* finalElectors; 
		
		try
		{
			finalElectors = new std::vector<Citizen*>;
		}
		catch (std::bad_alloc& err)
		{
			std::cout << "Error: " << err.what() << std::endl;
			exit(-1);
		}

		int partiesSize = _election->getParties().size();

		for (int i = 0; i < partiesSize; ++i)
			for (int j = 0; j < getNumOfElectorsToGrantParty(i); ++j)
				finalElectors->push_back(_electorsByParty[i][j]);
		return finalElectors;
	}
}