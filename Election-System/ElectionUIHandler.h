#pragma once

namespace elec
{
	class Election;

	class ElectionUIHandler
	{
	public:
		ElectionUIHandler() = default;
		ElectionUIHandler(Election* election) noexcept : _election(election) {}

	public:
		void addStuff() const;

		//the following functions handle interaction 
		//with an election object through CUI
		void addState() const;
		void addCitizen() const;
		void addParty() const;
		void showStates() const;
		void showCitizens() const;
		void showParties() const;
		void showResults() const;
		void generateTest() const;
		void electCitizen() const;
		void addVote() const;
		void showVotes() const;
		void pause() const;
		void clearData() const;

		int getYearOfBirth() const;
		int getNumOfElectors() const;

		int getAnExistingID() const;
		int getNewID() const;
		int getUnvotedID() const;

		int getAnExistingStateSN() const;
		int getNewStateSN() const;

		int getAnExistingPartySN() const;
		int getNewPartySN() const;

	private:
		Election* _election;
	};
}
