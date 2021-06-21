#pragma once
#include <iostream>
#include "Serializable.h"
#include <fstream>
#include <string>

namespace elec
{
	class Election;
	class Citizen;

	class Party
	{
	public:
		Party(std::string name, Citizen* _presidentialCandidate, Election* election);
		Party(const Party& other) = delete;
		Party(std::istream& in) { load(in); };

	public:
		friend std::ostream& operator<<(std::ostream& os, Party& other);
		Party& operator=(const Party& other) = delete;

	public:
		//sets the current election
		bool setElection(Election* election) { _election = election; return election ? true : false; }
		//return the unique identifier of a given party instance
		int getSerial() const { return _serial; }
		//return the name of the party
		const std::string& getName() const { return _name; }
		//return the party presidential candidate
		Citizen* getPresidentialCandidate() const { return _presidentialCandidate; }
		//return the overall party votes from all states
		int getTotalVotes() const;
		//print all electors
		void printElectors();

		int getOverallNumOfElectors() const;

		void save(std::ostream& out) const;

		void load(std::istream& in);

		void savePresidentialCandidateID(std::ostream& out) const;
		
		void loadPresidentialCandidatePtr(std::istream& in);

	private:
		Election* _election;
		std::string _name;
		static int _instances;
		int _serial;
		Citizen* _presidentialCandidate;
	};
}