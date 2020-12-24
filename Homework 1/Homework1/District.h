#pragma once
#include <fstream>
#include "VotesCounter.h"

using namespace std;

namespace elections {
	class District {
	private:
		char* name;
		int nameLen, numOfRep, districtNum;
		int citizensNum;
		VotesCounter votesCounter;

	public:
		// Ctors
		District();
		District(char* _name, int _nameLen, int _numOfRep, int _districtNum);
		District(const District&);

		// Dtor
		~District();

		// Overload "=" operator
		void operator=(const District&);

		// Getters-------------------------------
		const int getDistrictNum(void) const;
		const char* getDistrictName() const;
		const int getNumOfRep() const;
		const int getCitizensNum() const;
		VotesCounter getVotesCounter();

		// voting --------------------------------------
		void addCounterForNewParty();
		void addVoteToCounterInIdx(int partyNum);
		const int getVotesInIndex(int idx) const;
		void addOneCitizen();

		// Printer operator
		friend ostream& operator<<(ostream& os, const District& district);

		void save(ostream& out) const;
		void load(istream& in);
	};
}