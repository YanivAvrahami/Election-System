#include "ElectionUIHandler.h"
#include "State.h"
#include "Citizen.h"
#include "Party.h"
#include "StandardElection.h"
#include "UnifiedState.h"
#include "DividedState.h"
#include "SimpleElection.h"
#include <string>
#include <exception>
#include <algorithm>
#include "CompareByNumElectors.h"
#include "CompareByVotes.h"

namespace elec
{
	void ElectionUIHandler::addStuff() const
	{
		_election->addState(new UnifiedState("s1", 5, _election));
		_election->addCitizen(new Citizen("a1", 123456789, 1993, _election->findState(0), _election));
		_election->addParty(new Party("P1", _election->findCitizen(123456789), _election));
		_election->addState(new DividedState("s2", 5, _election));
	}

	void ElectionUIHandler::addState() const
	{
		if (typeid(*_election) == typeid(StandardElection))
		{
			StandardElection* elec = static_cast<StandardElection*>(_election);
			std::string name;
			int numOfElectors;
			int stateType;

			std::cout << "-----Add new state-----\n";
			std::cout << "State type (1-unified 2-divided): ";
			std::cin >> stateType;

			std::cout << "State name: ";
			std::cin.ignore();
			std::getline(std::cin, name);

			std::cout << "State max representatives: ";
			try
			{
				numOfElectors = getNumOfElectors();
			}
			catch (std::invalid_argument& err)
			{
				std::cout << err.what() << std::endl;
				pause();
				return;
			}
			
			if (stateType == 1)
			{
				try
				{
					elec->addState(new UnifiedState(name, numOfElectors, elec));
				}
				catch (std::invalid_argument& err)
				{
					std::cout << err.what() << std::endl;
					pause();
					return;
				}
				catch (std::bad_alloc& err)
				{
					std::cout << "Error: " << err.what() << std::endl;
					pause();
					return;
				}
			}
			else if(stateType == 2)
			{
				try
				{
					elec->addState(new DividedState(name, numOfElectors, elec));
				}
				catch (std::invalid_argument& err)
				{
					std::cout << err.what() << std::endl;
					pause();
					return;
				}
				catch (std::bad_alloc& err)
				{
					std::cout << "Error: " << err.what() << std::endl;
					pause();
					return;
				}
			}
		}
	}

	void ElectionUIHandler::addCitizen() const
{
		std::cout << "-----Add new citizen-----\n";

		std::string name;
		std::cout << "Name: ";
		std::cin.ignore();
		std::getline(std::cin, name);

		int id, yearOfBirth;
		try 
		{
			std::cout << "ID: ";
			id = getNewID();

			std::cout << "Year of birth: ";
			yearOfBirth = getYearOfBirth();
		}
		catch (std::invalid_argument& err)
		{
			std::cout << err.what() << std::endl;
			pause();
			return;
		}

		if (typeid(*_election) == typeid(StandardElection))
		{
			int stateSerial;
			std::cout << "State serial: ";
			try 
			{
				stateSerial = getAnExistingStateSN();
			}
			catch (std::invalid_argument& err)
			{
				std::cout << err.what() << std::endl;
				pause();
				return;
			}

			try
			{
				_election->addCitizen(new Citizen(name, id, yearOfBirth, _election->findState(stateSerial), _election));
			}
			catch(std::invalid_argument& err)
			{
				std::cout << err.what() << std::endl;
				pause();
				return;
			}
			catch (std::bad_alloc& err)
			{
				std::cout << "Error: " << err.what() << std::endl;
				pause();
				return;
			}
		}
		else if (typeid(*_election) == typeid(SimpleElection))
		{
			try
			{
				_election->addCitizen(new Citizen(name, id, yearOfBirth, _election->findState(0), _election));
			}
			catch (std::invalid_argument& err)
			{
				std::cout << err.what() << std::endl;
				pause();
				return;
			}
			catch (std::bad_alloc& err)
			{
				std::cout << "Error: " << err.what() << std::endl;
				pause();
				return;
			}
		}
	}

	void ElectionUIHandler::addParty() const
	{
		std::cout << "-----Add new party-----\n";

		std::string name;
		std::cout << "Party name: ";
		std::getline(std::cin ,name);

		int id;
		try
		{
			std::cout << "Presidential candidate ID: ";
			id = getAnExistingID();
		}
		catch (std::invalid_argument& err)
		{
			std::cout << err.what() << std::endl;
			pause();
			return;
		}

		if (_election->findCitizen(id)->getParty())
		{
			std::cout << "Error: citizen is already an elector";
			pause();
			return;
		}

		try
		{
			_election->addParty(new Party(name, _election->findCitizen(id), _election));
		}
		catch (std::bad_alloc& err)
		{
			std::cout << "Error: " << err.what() << std::endl;
			pause();
			return;
		}

		return;
	}

	void ElectionUIHandler::showStates() const
	{
		if (typeid(*_election) == typeid(StandardElection))
		{
			StandardElection* elec = static_cast<StandardElection*>(_election);
			
			std::cout << "---------STATES---------\n";

			for (auto elem : _election->_states)
				std::cout << *elem;
			
			pause();
		}
	}

	void ElectionUIHandler::showCitizens() const
	{
		std::cout << "--------CITIZENS---------\n"; 
		
		for (auto elem : _election->_citizens)
			std::cout << *elem;
	
		pause();
	}

	void ElectionUIHandler::showParties() const
	{
		std::cout << "---------PARTIES---------\n";

		for (auto elem : _election->_parties)
			std::cout << *elem;

		pause();
	}

	void ElectionUIHandler::showResults() const
	{
		if (_election->_citizens.size() < 1 ||
			_election->_parties.size() < 1 ||
			_election->_states.size() < 1 ||
			!_election->hasEnoughElectorsInStates())
		{
			throw std::exception("Error: not enough data to show election results");
		}

		std::cout << "---------RESULTS: " << _election->getDate() << "---------\n\n";

		if (typeid(*_election) == typeid(StandardElection))
		{
			//showing states results information
			for (int i = 0; i < _election->_states.size(); ++i)
			{
				State* curState = _election->findState(i);
				std::cout << "State name: " << curState->getName() << std::endl;
				std::cout << "Amount of electors state grants: " << curState->getMaxNumOfElectors() << std::endl;
				
				if (typeid(*curState) == typeid(UnifiedState))
				{
					std::cout << "Local winner presidential candidate: " << curState->getLocalWinningParty().getPresidentialCandidate()->getName() << std::endl;
				}

				std::cout << "Chosen Electors: " << std::endl;
				//show every chosen elector name and and it's party name 
				const std::vector<Citizen*>& LocalElectors = *curState->getLocalFinalElectors();
				for (int i = 0; i < LocalElectors.size(); ++i)
				{
					std::cout << LocalElectors[i]->getName();
					std::cout << " from party " << LocalElectors[i]->getParty()->getName() << std::endl;
				}

				//show the amount of votes and vote percentage that each party got in each state
				for (int i = 0; i < _election->_parties.size(); ++i)
				{
					std::cout << "Party " << _election->findParty(i)->getName() << " has " << curState->getVotesCounter().get(i) << " votes ";
					std::cout << "(" << curState->getVotesCounter().getRatioInPercentage(i) << "% of total votes)" << std::endl;
				}

				//show overall voting percentage in the state
				std::cout << "Overall voting percentage: " << _election->findState(i)->getVotePercentage() << "%\n\n";
			}

			//showing parties results information
			std::sort(_election->_parties.begin(), _election->_parties.end(), ComparePartiesByNumOfElectors());
			
			for (auto elem : _election->_parties)
			{
				std::cout << "Party name: "					 << elem->getName() << std::endl;
				std::cout << "Presidential candidate name: " << elem->getPresidentialCandidate()->getName() << std::endl;
				std::cout << "Overall number of electors: "  << elem->getOverallNumOfElectors() << std::endl;
				std::cout << "Total votes: "				 << elem->getTotalVotes() << std::endl;
			}
		}
		else if (typeid(*_election) == typeid(SimpleElection))
		{
			//show overall voting percentage in the state
			std::cout << "Overall voting percentage: " << _election->findState(0)->getVotePercentage() << "%\n\n";

			//showing parties results information
			std::sort(_election->_parties.begin(), _election->_parties.end(), CompareByVotes());

			for (auto elem : _election->_parties)
			{
				std::cout << "Party name: "                 << elem->getName() << std::endl;
				std::cout << "Overall number of electors: " << elem->getOverallNumOfElectors() << std::endl;
				std::cout << "Total votes: "                << elem->getTotalVotes();
				std::cout << "(" << _election->_states[0]->getVotesCounter().getRatioInPercentage(elem->getSerial()) << "% of total votes)" << std::endl;

				std::cout << "Electors:\n"; 
				elem->printElectors();

				std::cout << "Presidential candidate name: " << elem->getPresidentialCandidate()->getName() << std::endl;

				std::cout << std::endl;
				std::cout << std::endl;
			}
		}
		pause();
	}

	void ElectionUIHandler::generateTest() const
	{
		if (typeid(*_election) == typeid(StandardElection))
		{
			StandardElection* elec = static_cast<StandardElection*>(_election);

			std::string name("");

			elec->addState(new UnifiedState("a", 15, elec));
			elec->addState(new DividedState("b", 10, elec));
			elec->addState(new UnifiedState("c", 7, elec));

			for (int i = 1; i <= 100; ++i)
			{
				name += 'a';
				name += std::to_string(i);
				elec->addCitizen(new Citizen(name.c_str(), i + 200000000, 1900, elec->findState(0), elec));
				name.clear();
			}
			for (int i = 1; i <= 100; ++i)
			{
				name += 'b';
				name += std::to_string(i);
				elec->addCitizen(new Citizen(name.c_str(), i + 100 + 200000000, 1900, elec->findState(1), elec));
				name.clear();
			}
			for (int i = 1; i <= 100; ++i)
			{
				name += 'c';
				name += std::to_string(i);
				elec->addCitizen(new Citizen(name.c_str(), i + 200 + 200000000, 1900, elec->findState(2), elec));
				name.clear();
			}

			elec->addParty(new Party("Dambo", elec->findCitizen(1 + 200000000), elec));
			elec->addParty(new Party("Ayor", elec->findCitizen(2 + 200000000), elec));

			for (int i = 1 + 200000000; i <= 15 + 200000000; ++i)
				elec->findCitizen(i)->becomeElector(0, 0);
			for (int i = 16 + 200000000; i <= 30 + 200000000; ++i)
				elec->findCitizen(i)->becomeElector(1, 0);
			
			for (int i = 1 + 200000000; i <= 10 + 200000000; ++i)
				elec->findCitizen(i + 100)->becomeElector(0, 1);
			for (int i = 11 + 200000000; i <= 20 + 200000000; ++i)
				elec->findCitizen(i + 100)->becomeElector(1, 1);

			for (int i = 1 + 200000000; i <= 7 + 200000000; ++i)
				elec->findCitizen(i + 200)->becomeElector(0, 2);
			for (int i = 8 + 200000000; i <= 14 + 200000000; ++i)
				elec->findCitizen(i + 200)->becomeElector(1, 2);
			
			//state 'a' votes:
			for (int i = 1 + 200000000; i <= 60 + 200000000; ++i)
				elec->findCitizen(i)->vote(0);
			for (int i = 61 + 200000000; i <= 100 + 200000000; ++i)
				elec->findCitizen(i)->vote(1);
			//state 'b' votes:
			for (int i = 101 + 200000000; i <= 125 + 200000000; ++i)
				elec->findCitizen(i)->vote(0);
			for (int i = 126 + 200000000; i <= 150 + 200000000; ++i)
				elec->findCitizen(i)->vote(1);
			//state 'c' votes:
			for (int i = 201 + 200000000; i <= 240 + 200000000; ++i)
				elec->findCitizen(i)->vote(0);
			for (int i = 241 + 200000000; i <= 290 + 200000000; ++i)
				elec->findCitizen(i)->vote(1);

			std::cout << std::endl;
		}
		else if (typeid(*_election) == typeid(SimpleElection))
		{
			SimpleElection* elec = static_cast<SimpleElection*>(_election);

			std::string name("");

			//creating citizens
			for (int i = 1; i <= 100; ++i)
			{
				name += 'a';
				name += std::to_string(i);
				elec->addCitizen(new Citizen(name.c_str(), i + 200000000, 1900, elec->findState(0), elec));
				name.clear();
			}

			//creating parties
			elec->addParty(new Party("P1", elec->findCitizen(1 + 200000000), elec));
			elec->addParty(new Party("P2", elec->findCitizen(2 + 200000000), elec));

			//electing citizens
			for (int i = 3 + 200000000; i <= 12 + 200000000; ++i)
				elec->findCitizen(i)->becomeElector(0, 0);
			for (int i = 13 + 200000000; i <= 22 + 200000000; ++i)
				elec->findCitizen(i)->becomeElector(1, 0);

			for (int i = 11 + 200000000; i <= 50 + 200000000; ++i)
				elec->findCitizen(i)->vote(1);
			for (int i = 51 + 200000000; i <= 100 + 200000000; ++i)
				elec->findCitizen(i)->vote(0);

			std::cout << std::endl;
		}
	}

	void ElectionUIHandler::electCitizen() const
	{
		std::cout << "-----Add new elector-----\n";

		int id, partySerial;

		try
		{
			std::cout << "ID: ";
			id = getAnExistingID();
			
			std::cout << "Party serial: ";
			partySerial = getAnExistingPartySN();
		}
		catch (std::invalid_argument& err)
		{
			std::cout << err.what() << std::endl;
			pause();
			return;
		}

		if (typeid(*_election) == typeid(StandardElection))
		{
			StandardElection* elec = static_cast<StandardElection*>(_election);
			int stateSerial;
			try
			{
				std::cout << "State serial: ";
				stateSerial = getAnExistingStateSN();
			}
			catch (std::invalid_argument& err)
			{
				std::cout << err.what() << std::endl;
				pause();
				return;
			}

			elec->makeCitizenAnElector(id, partySerial, stateSerial);
		}
		else if (typeid(*_election) == typeid(SimpleElection))
		{
			SimpleElection* elec = static_cast<SimpleElection*>(_election);
			elec->makeCitizenAnElector(id, partySerial, 0);
		}

	}

	void ElectionUIHandler::addVote() const
	{
		std::cout << "-----Add new vote-----\n";

		try
		{
			int id, partySerial;

			std::cout << "ID: ";
			id = getUnvotedID();
			
			std::cout << "Party serial: ";
			partySerial = getAnExistingPartySN();
			
			_election->vote(id, partySerial);
		}
		catch (std::invalid_argument& err)
		{
			std::cout << err.what() << std::endl;
			pause();
			return;
		}
	}

	void ElectionUIHandler::showVotes() const
	{
		std::cout << "---------VOTES---------\n";

		for (auto elem : _election->_parties)
			std::cout << "Votes for party " << elem->getName() << ": " << elem->getTotalVotes() << std::endl;

		pause();
	}

	void ElectionUIHandler::pause() const
	{
		std::cout << "\nPress 'enter' to continue\n";
		std::string temp;
		std::getline(std::cin, temp);
	}

	void ElectionUIHandler::clearData() const
	{
		for (auto elem : _election->_citizens)
			delete elem;
		_election->_citizens.clear();
		
		for (auto elem : _election->_states)
			delete elem;
		_election->_states.clear();

		for (auto elem : _election->_parties)
			delete elem;
		_election->_parties.clear();
	}

	int ElectionUIHandler::getAnExistingID() const
	{
		int id;
		std::cin >> id;
		std::cin.ignore();

		if (id > 100000000 && id < 999999999)
		{
			try
			{
				_election->findCitizen(id);
				return id;
			}
			catch(...)
			{
				throw std::invalid_argument("Error: id doesn't exist in citizens list");
			}
		}
		else
		{
			throw std::invalid_argument("Error: wrong id format");
		}
	}

	int ElectionUIHandler::getNewID() const
	{
		int id;
		std::cin >> id;
		std::cin.ignore();

		if (id > 100000000 && id < 999999999)
		{
			if (!_election->isIDExist(id))
				return id;
			else
				throw std::invalid_argument("Error: id already exist in citizens list");
		}
		else
			throw std::invalid_argument("Error: wrong id format");
	}

	int ElectionUIHandler::getUnvotedID() const
	{
		int id;

		try
		{
			id = getAnExistingID();
		}
		catch(std::invalid_argument& err)
		{
			throw;
		}

		if (!_election->findCitizen(id)->hasVoted())
			return id;
		else
			throw std::invalid_argument("Error: citizen already voted");
	}

	int ElectionUIHandler::getAnExistingStateSN() const
	{
		int serial;
		std::cin >> serial;
		std::cin.ignore();

		if (_election->isStateExist(serial))
			return serial;
		else
			throw std::invalid_argument("Error: state doesn't exist in states list");
	}

	int ElectionUIHandler::getNewStateSN() const
	{
		int serial;
		std::cin >> serial;
		std::cin.ignore();

		if (!_election->isStateExist(serial))
			return serial;
		else
			throw std::invalid_argument("Error: state already exist in states list");
	}

	int ElectionUIHandler::getAnExistingPartySN() const
	{
		int serial;
		std::cin >> serial;
		std::cin.ignore();

		if (_election->isPartyExist(serial))
			return serial;
		else
			throw std::invalid_argument("Error: party doesn't exist in parties list");
	}

	int ElectionUIHandler::getNewPartySN() const
	{
		int serial;
		std::cin >> serial;
		std::cin.ignore();

		if (!_election->isPartyExist(serial))
			return serial;
		else
			throw std::invalid_argument("Error: party already exist in parties list");
	}


	int ElectionUIHandler::getNumOfElectors() const
	{
		int numElectors;
		std::cin >> numElectors;
		std::cin.ignore();

		if (numElectors >= 0)
			return numElectors;
		else
			throw std::invalid_argument("Error: negative number of electors");
	}

	int ElectionUIHandler::getYearOfBirth() const
	{
		int yearOfBirth;
		std::cin >> yearOfBirth;
		std::cin.ignore();

		int age = _election->_date.getYear() - yearOfBirth;

		if (age < 18 || yearOfBirth <= 0)
			throw std::invalid_argument("Error: invalid age");
		else
			return yearOfBirth;
	}

}