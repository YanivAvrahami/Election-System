#pragma once
#include <iostream>
#include <fstream>
#include "Serializable.h"

namespace elec
{
	class State;
	class Party;
	class Election;

	class Citizen
	{
	public:
		Citizen(std::string name, const int id, const int yearOfBirth, Election* election);
		Citizen(std::string name, const int id, const int yearOfBirth, State* state, Election* election);
		Citizen(const Citizen& other) = delete;
		Citizen(std::istream& in) { load(in); };

	public:
		friend std::ostream& operator<<(std::ostream& os, const Citizen& other);
		Citizen& operator=(const Citizen& other) = delete;

	public:
		//sets the current election
		void setElection(Election* election) { _election = election; }
		//adds a vote to a given party
		void vote(int partySerial);
		//return true if the citizen already voted, else false
		bool hasVoted() const { return _voted; };
		//adds the citizen an elector of a given party and state
		void becomeElector(int partySerial, int stateSerial);
		//returns the name of the citizen
		const std::string& getName() const { return _name; }
		//returns the id of the citizen
		int getID() const { return _id; }
		//returns the year which the citizen was born
		int getYearOfBirth() const { return _yearOfBirth; }
		//returns the state in which the citizen lives
		State* getState() const { return _state; }
		//returns the party in which the citizen is elector of, else return null
		Party* getParty() const { return _party; }

		void save(std::ostream& out) const;
		void load(std::istream& in);

		void saveStateSerial(std::ostream& out) const;
		void loadStatePtr(std::istream& in);

		void savePartySerial(std::ostream& out) const;
		void loadPartyPtr(std::istream& in);

	private:
		Election* _election;
		std::string _name;
		int _id;
		int _yearOfBirth;
		bool _voted;
		State* _state;
		Party* _party;
	};
}