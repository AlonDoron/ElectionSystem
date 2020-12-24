#pragma once
#include <fstream>


using namespace std;

namespace elections {
class CitizensArr;
	class VotesCounter {
	private:
		int votingNumber = 0;
		int winningPartyID = 0;
		int logSize = 0, phsSize = 0;
		int* votesByParty;
		int* votesPerc;

		// Resizing votersByDistrict arr and updating logSize, phsSize
		void resize(int newSize);

	public:
		// Ctors
		VotesCounter();
		VotesCounter(int size);
		// copy ctor
		VotesCounter(const VotesCounter&);

		// Dtor
		~VotesCounter();

		// Overload "=" operator
		void operator=(const VotesCounter&);

		// Setters----------------------------------------
		// allocating one more space when district is added
		void addEmptyCounter();

		// add one vote to in index "districtNum"
		void addVote(int partyNum);

		// Getters------------------------------------------
		// return the number of votes in district "idx"
		const int getLogSize() const;
		const int getPhiSize() const;
		const int getWinningPartID();
		void updatePercentage();
		void updateWinner();
		const int getVotingNumberInDistrict() const;
		int* getVotesByParty();
		int* getPercentageVotes();


		int& operator[](int index) const;

		void save(ostream& out) const;
		void load(istream& in);
	};
}