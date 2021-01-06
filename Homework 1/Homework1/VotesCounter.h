#pragma once
#include <fstream>
#include <vector>


using namespace std;

namespace elections {
	class PartiesArr;
	class CitizensArr;
	class VotesCounter {
	private:
		int votingNumber = 0;
		int winningPartyID = 0;
		vector<int> votesByParty;
		vector<int> votesPerc;

		// Resizing votersByDistrict arr and updating logSize, phsSize
		//void resize(int newSize);

	public:
		// Ctors
		VotesCounter();
		VotesCounter(int size);
		// copy ctor
		VotesCounter(const VotesCounter&);

		// Dtor
		~VotesCounter();

		// Overload "=" operator
		VotesCounter& operator=(const VotesCounter&);

		// Setters----------------------------------------
		// allocating one more space when district is added
		void addEmptyCounter();

		// add one vote to in index "districtNum"
		void addVote(int partyNum);

		// Getters------------------------------------------
		// return the number of votes in district "idx"
		const int getWinningPartID();
		void updatePercentage();
		void updateWinner();
		const int getVotingNumberInDistrict() const;
		vector<int> getVotesByParty();
		vector<int> getPercentageVotes();
		void printVotingStatictic(PartiesArr* partiesArr, int citizensNum);

		const int operator[](int index) const;

		//Save and load from BIN file methods.
		void save(ostream& out) const;
		void load(istream& in);
	};
}