#pragma once
#include <iostream>
#include <math.h>
#include <fstream>
#include "Counter.h"
#include <string>
#include <vector>

namespace elec
{
	class Election;
	class Citizen;
	class Party;

	class State
	{
	public:
		State();
		State(std::string name, const int amountOfElectors, Election* election);
		State(const State& other) = delete;
		State(std::istream& in) { load(in); };
		virtual ~State() {};

	public:
		friend std::ostream& operator<<(std::ostream& os, const State& other);
		virtual void print(std::ostream& os) const = 0;
		State& operator=(const State& other) = delete;

	public:
		//sets the current election
		void setElection(Election* election) { _election = election; }
		//return the unique identifier of a given instance
		int getSerial() const { return _serial; }
		//return the name of the state
		const std::string& getName() const { return _name; }
		//return the amount of electors given to a given state
		int getMaxNumOfElectors() const { return _numOfElectors; }
		//return the amount of current electors
		int getCurrentNumOfElectors() const;
		//return the votes counter of a given state
		const Counter& getVotesCounter() const { return _votesCounter; }
		//return the votes counter of a given state
		Counter& getVotesCounter() { return _votesCounter; }
		//return a list of electors of each party
		const std::vector<std::vector<Citizen*>>& getElectorsByParty() const { return _electorsByParty; }
		//return a list of electors of each party
		std::vector<std::vector<Citizen*>>& getElectorsByParty() { return _electorsByParty; }
		//return state vote percentage
		float getVotePercentage() const;
		//add citizen to state citizens list
		void addCitizen(Citizen* citizen);
		//add a citizen to the electors list
		void addPartyElector(Citizen* citizen, int partySerial);
		//return the local winning party
		const Party& getLocalWinningParty() const;
		//return the amount of electors granted to a given party
		int getNumOfElectorsToGrantParty(int partySerial) const;
		//returns a list of the final electors of a given state
		std::vector<Citizen*>* getLocalFinalElectors();

		void save(std::ostream& out) const;
		void load(std::istream& in);

		void saveStateCitizensIDs(std::ostream& out) const;
		void saveElectorsByPartyIDs(std::ostream& out) const;
		void loadCitizensPointers(std::istream& in);
		void loadElectorsByPartyPointers(std::istream& in);

	protected:
		Election* _election;
		std::string _name;
		static int _instances;
		int _serial;
		int _numOfElectors;
		std::vector<Citizen*> _citizens;
		std::vector<std::vector<Citizen*>> _electorsByParty;
		Counter _votesCounter;
	};
}