#pragma once
#include <fstream>
#include "VotesCounter.h"
#include <iostream>

using namespace std;

#define rcastcc reinterpret_cast<const char*>
#define rcastc reinterpret_cast<char*>

namespace elections {
	class PartiesArr;
	class CitizensDB;

	class District {
	protected:
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
		const VotesCounter& getVotesCounter();
		// get voting percentage

		// voting --------------------------------------
		void addVotesCountersForNewParty();
		void addVoteToVotesCountersInIdx(int partyNum);
		const int getVotesInIndex(int idx) const;
		void addOneCitizen();


		virtual void setElected(PartiesArr* _partiesArr, CitizensDB* _electorsByParty,CitizensDB* _citizensDB);
		void printResultElectionInDist(PartiesArr* _partiesArr, CitizensDB* _citizensDB);

		// Printer operator
		friend ostream& operator<<(ostream& os, const District& district);

		void save(ostream& out) const;
		void load(istream& in);
	};


}