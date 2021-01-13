#pragma once
#include <fstream>
#include "Party.h"
#include "CitizensArr.h"
#include "DynamicArray.h"

#define rcastcc reinterpret_cast<const char*>
#define rcastc reinterpret_cast<char*>

namespace elections {
	class PartiesArr {
	private:
		DynamicArray<Party> parties;

	public:
		// Ctor
		PartiesArr();

		void add(Party& party);

		// add rep to party in index partyNum to it's array in index districtNum
		void addRep(Citizen& rep, int partyNum, int districtNum, int numOfDistrict);

		// allocating one more space to each party when district is added
		void addNewDistToRepArr(void);

		// Getters----------------------------------------------------------------
		const int getLogSize() const;

		const Party& operator[](int index) const;

		// returns true if citizen with the id is already leader
		const bool isCitizenAlreadyLeader(long int id) const;

		// returns true if citizen with the id is already rep
		const bool isCitizenAlreadyRep(long int id) const;

		void isPartyNumberExist(int partyNum);

		friend ostream& operator<<(ostream& os, PartiesArr& partiesArr);

		//Save and load from BIN file methods.
		void save(ostream& out) const;
		void load(istream& in);

	};
}