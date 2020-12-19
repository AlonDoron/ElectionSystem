#pragma once
#include "Party.h"
#include "CitizensArr.h"

namespace elections {
	class PartiesArr {
	private:
		int logSize = 0, phsSize = 0;
		Party* parties;

		// Resizing parties arr and updating logSize, phsSize
		void resize(int size);

	public:
		// Ctor
		PartiesArr();

		// Dtor
		~PartiesArr();

		// Overload "=" operator
		void operator=(const PartiesArr&);

		// Setters---------------------------------------------------------
		// add one party to partiesArr
		void add(Party& party);

		// add rep to party in index partyNum to it's array in index districtNum
		void addRep(Citizen* rep, int partyNum, int districtNum);

		// allocating one more space to each party when district is added
		void addDistrictToAllParties(void);

		// add one vote to party in index "partyId" in votersArr in index "districtNum"
		void addVoteToDistrictInParty(int partyID, int districtNum);

		// Getters----------------------------------------------------------------
		const int getLogSize() const;
		Party& getPartyByIndex(int idx);

		// returns true if citizen with the id is already leader
		const bool isCitizenAlreadyLeader(long int id) const;

		// returns true if citizen with the id is already rep
		const bool isCitizenAlreadyRep(long int id) const;

		// Print all parties in PartiesArr
		void printParties(void) const;
	};
}