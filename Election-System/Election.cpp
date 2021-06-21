#include "Election.h"
#include "UnifiedState.h"
#include "DividedState.h"
#include "StandardElection.h"
#include "SimpleElection.h"
#include "ElectionLoader.h"
#include <typeinfo>
#include "StateLoader.h"
#include <vcruntime_exception.h>
#include "Date.h"

namespace elec
{
	Election::Election()
		: _handler(this), _date({1,1,1}) {};

	Election::Election(Date date) 
		: _handler(this), _date(date) {};
	
	Election::Election(std::istream& in) 
		: _handler(this) 
	{ 
		load(in);
	};

	Election::~Election()
	{
		for (auto elem : _citizens)
			delete elem;
		_citizens.clear();

		for (auto elem : _states)
			delete elem;
		_states.clear();

		for (auto elem : _parties)
			delete elem;
		_parties.clear();
	}

	State* Election::findState(int stateSerial)
	{
		if (_states.size() == 0)
			return nullptr;

		for (auto elem : _states)
			if (elem->getSerial() == stateSerial)
				return elem;

		throw std::exception("Error: could not find state");
	}

	Citizen* Election::findCitizen(int id)
	{
		if (_citizens.size() == 0)
			return nullptr;

		for (auto elem : _citizens)
			if (elem->getID() == id)
				return elem;

		throw std::exception("Error: could not find citizen");
	}

	Party* Election::findParty(int partySerial)
	{
		if (_parties.size() == 0)
			return nullptr;

		for (auto elem : _parties)
			if (elem->getSerial() == partySerial)
				return elem;

		throw std::exception("Error: could not find party");
	}

	const State* Election::findState(int stateSerial) const
	{
		if (_states.size() == 0)
			return nullptr;

		for (auto elem : _states)
			if (elem->getSerial() == stateSerial)
				return elem;

		throw std::exception("Error: could not find state");
	}

	const Citizen* Election::findCitizen(int id) const
	{
		if (_citizens.size() == 0)
			return nullptr;
		
		for (auto elem : _citizens)
			if (elem->getID() == id)
				return elem;

		throw std::exception("Error: could not find citizen");
	}

	const Party* Election::findParty(int partySerial) const
	{
		if (_parties.size() == 0)
			return nullptr;

		for (auto elem : _parties)
			if (elem->getSerial() == partySerial)
				return elem;

		throw std::exception("Error: could not find party");
	}

	const Party* Election::getOverallWinningParty() const
{
		int winningPartyIndex = 0;

		for (int i = 1; i < _parties.size(); ++i)
		{
			if (_parties[i]->getOverallNumOfElectors() > _parties[winningPartyIndex]->getOverallNumOfElectors() ||
				_parties[i]->getOverallNumOfElectors() == _parties[winningPartyIndex]->getOverallNumOfElectors() &&
				_parties[i]->getSerial() < _parties[winningPartyIndex]->getSerial())
			{
				winningPartyIndex = i;
			}
		}
		return _parties[winningPartyIndex];
	}

	bool Election::isStateExist(int stateSerial) const
	{
		for (auto elem : _states)
			if (elem->getSerial() == stateSerial)
				return true;

		return false;
	}

	bool Election::isPartyExist(int partySerial) const
	{
		for (auto elem : _parties)
			if (elem->getSerial() == partySerial)
				return true;

		return false;
	}

	bool Election::isIDExist(int id) const
	{
		for (auto elem : _citizens)
			if (elem->getID() == id)
				return true;

		return false;
	}

	void Election::addState(State* state)
	{	
		_states.push_back(state);
		state->getElectorsByParty().resize(_parties.size());
		state->getVotesCounter().resize(_parties.size());
	}

	void Election::addCitizen(Citizen* citizen)
	{
		_citizens.push_back(citizen);
		citizen->getState()->addCitizen(citizen);
	}

	void Election::addParty(Party* party)
	{
		_parties.push_back(party);

		for (State* state : _states)
		{
			state->getElectorsByParty().resize(_parties.size());
			state->getVotesCounter().resize(_parties.size());
		}
	}

	void Election::makeCitizenAnElector(int id, int partySerial, int stateSerial)
	{
		findCitizen(id)->becomeElector(partySerial, stateSerial);
	}

	void Election::vote(int citizenID, int partySerial)
	{
		findCitizen(citizenID)->vote(partySerial);
	}

	void Election::save(std::ostream& out) const
	{
		int size;

		try
		{
			_date.save(out);

			//Saving states primitives
			size = _states.size();
			out.write(rcastccp(&size), sizeof(size));
			for (auto elem : _states)
				StateLoader::save(elem, out);

			//Saving citizens primitives
			size = _citizens.size();
			out.write(rcastccp(&size), sizeof(size));
			for (auto elem : _citizens)
				elem->save(out);

			//Saving parties primitives
			size = _parties.size();
			out.write(rcastccp(&size), sizeof(size));
			for (auto elem : _parties)
				elem->save(out);

			saveStatesPtrs(out);
			saveCitizensPtrs(out);
			savePartiesPtrs(out);
		}
		catch(std::exception& err)
		{
			throw;
		}
		
	}

	void Election::load(std::istream& in)
	{
		_date.load(in);

		int size;

		//Loading States primitives
		in.read(rcastcp(&size), sizeof(size));
		for (int i = 0; i < size; ++i)
			_states.push_back(StateLoader::load(in));

		//Loading Citizens primitives
		in.read(rcastcp(&size), sizeof(size));
		for (int i = 0; i < size; ++i) 
		{
			try
			{
				_citizens.push_back(new Citizen(in));
			}
			catch (std::bad_alloc& err)
			{
				std::cout << "Error: " << err.what() << std::endl;
				exit(-1);
			}
		}

		//Loading Parties primitives
		in.read(rcastcp(&size), sizeof(size));
		for (int i = 0; i < size; ++i) 
		{
			try
			{
				_parties.push_back(new Party(in));
			}
			catch (std::bad_alloc& err)
			{
				std::cout << "Error: " << err.what() << std::endl;
				exit(-1);
			}	
		}

		setStatesPtrToElection();
		setCitizensPtrToElection();
		setPartiesPtrToElection();

		try
		{
			loadStatesPtrs(in);
			loadCitizensPtrs(in);
			loadPartiesPtrs(in);
		}
		catch(std::exception& err)
		{
			throw;
		}

		if (!in.good())
			throw std::exception("Error: bad reading to file");
	}

	void Election::setStatesPtrToElection()
	{
		for (auto elem : _states)
			elem->setElection(this);
	}

	void Election::setCitizensPtrToElection()
	{
		for (auto elem : _citizens)
			elem->setElection(this);
	}

	void Election::setPartiesPtrToElection()
	{
		for (auto elem : _parties)
			elem->setElection(this);
	}

	void Election::saveStatesPtrs(std::ostream& out) const
	{
		try
		{
			for (auto elem : _states)
			{
				elem->saveStateCitizensIDs(out);
				elem->saveElectorsByPartyIDs(out);
			}
		}
		catch(std::exception& err)
		{
			throw;
		}
	}

	void Election::saveCitizensPtrs(std::ostream& out) const
	{
		try
		{
			for (auto elem : _citizens)
			{
				elem->saveStateSerial(out);
				elem->savePartySerial(out);
			}
		}
		catch (std::exception& err)
		{
			throw;
		}
	}

	void Election::savePartiesPtrs(std::ostream& out) const
	{
		try
		{
			for (auto elem : _parties)
				elem->savePresidentialCandidateID(out);
		}
		catch (std::exception& err)
		{
			throw;
		}
	}


	void Election::loadStatesPtrs(std::istream& in)
	{
		try
		{
			for (auto elem : _states)
			{
				elem->loadCitizensPointers(in);
				elem->loadElectorsByPartyPointers(in);
			}
		}
		catch(std::exception& err)
		{
			throw;
		}
	}

	void Election::loadCitizensPtrs(std::istream& in)
	{
		try
		{
			for (auto elem : _citizens)
			{
				elem->loadStatePtr(in);
				elem->loadPartyPtr(in);
			}
		}
		catch(std::exception& err)
		{
			throw;
		}
	}

	void Election::loadPartiesPtrs(std::istream& in)
	{
		try
		{
			for (auto elem : _parties)
				elem->loadPresidentialCandidatePtr(in);
		}
		catch (std::exception& err)
		{
			throw;
		}
	}

	bool Election::hasEnoughElectorsInStates()
	{
		for (auto elem : _states)
			if (elem->getCurrentNumOfElectors() < elem->getMaxNumOfElectors())
				return false;

		return true;
	}
}