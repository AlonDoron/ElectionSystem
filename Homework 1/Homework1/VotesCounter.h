#pragma once

namespace elections {
	class VotesCounter {
	private:
		int logSize = 0, phsSize = 0;
		int* votesByParty;

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
		void addVote(int districtNum);

		// Getters------------------------------------------
		// return the number of votes in district "idx"
		const int getLogSize() const;
		const int getPhiSize() const;

		int& operator[](int index) const;

		const int getVotesByIndex(int idx) const;
	};
}