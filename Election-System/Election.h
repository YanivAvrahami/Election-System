#pragma once
#include "Date.h"
#include "Party.h"
#include "Citizen.h"
#include "State.h"
#include "ElectionUIHandler.h"
#include <vector>

namespace elec
{
	class Election
	{
	public:
		Election();
		Election(Date date);
		Election(const Election& other) = delete;
		virtual ~Election();
		Election(std::istream& in);

	public:
		Election& operator=(const Election& other) = delete;

	public:
		//returns the object that handles election input/output
		const ElectionUIHandler& getUIHandler() const { return _handler; }

		//return the election date
		const Date& getDate() const { return _date; }
		//return the list of parties in the election
		const std::vector<Party*>& getParties() const { return _parties; }
		//return the list of citizens in the election
		const std::vector<Citizen*>& getCitizens() const { return _citizens; }
		//return the list of states in the election
		const std::vector<State*>& getStates() const { return _states; }

		std::vector<Party*>& getParties() { return _parties; }
		//return the list of citizens in the election
		std::vector<Citizen*>& getCitizens() { return _citizens; }
		//return the list of states in the election
		std::vector<State*>& getStates() { return _states; }

		//return a citizen from the citizen list by specific id
		const Citizen* findCitizen(int id) const;
		//return a party from the party list by specific serial number
		const Party* findParty(int partySerial) const;
		//return a state from the state list by specific serial number
		const State* findState(int stateSerial) const;

		//return a citizen from the citizen list by specific id
		Citizen* findCitizen(int id);
		//return a party from the party list by specific serial number
		Party* findParty(int partySerial);
		//return a state from the state list by specific serial number
		State* findState(int stateSerial);

		//return the final election winner
		const Party* getOverallWinningParty() const;
		
		//return true if a given state exists
		bool isStateExist(int stateSerial) const;
		//return true if a given party exists
		bool isPartyExist(int partySerial) const;
		//return true if a given ID exists
		bool isIDExist(int id) const;

		//add a new state
		void addState(State* state);
		//add a new citizen
		void addCitizen(Citizen* citizen);
		//add a new party
		void addParty(Party* party);
		//elect a given citizen
		void makeCitizenAnElector(int id, int partySerial, int stateSerial);
		//make a citizen vote to a specific party
		void vote(int citizenID, int partySerial);

		//saves election
		void save(std::ostream& out) const;
		//loads election
		void load(std::istream& in);

		//sets all states pointers to the current election
		void setStatesPtrToElection();
		//sets all citizens pointers to the current election
		void setCitizensPtrToElection();
		//sets all parties pointers to the current election
		void setPartiesPtrToElection();

		//saves all state serials to file
		void saveStatesPtrs(std::ostream& out) const;
		//saves all citizens ids to file
		void saveCitizensPtrs(std::ostream& out) const;
		//saves all parties serials to file
		void savePartiesPtrs(std::ostream& out) const;

		//saves all state serials to file
		void loadStatesPtrs(std::istream& in);
		//saves all citizens ids to file
		void loadCitizensPtrs(std::istream& in);
		//saves all parties serials to file
		void loadPartiesPtrs(std::istream& in);

		//checks if there is enough electors in every state
		bool hasEnoughElectorsInStates();
		
	private:
		Date _date;
		std::vector<State*> _states;
		std::vector<Citizen*> _citizens;
		std::vector<Party*> _parties;
		ElectionUIHandler _handler;
		friend class ElectionUIHandler;
	};
}