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

		// Setters
		void add(Party& party);
		void addRep(Citizen* rep, int partyNum, int districtNum);
		void addDistrictToAllParties(void);
		void addVoteToDistrictInParty(int partyID, int districtNum);

		// Getters
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