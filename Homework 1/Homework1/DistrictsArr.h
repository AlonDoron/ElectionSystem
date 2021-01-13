#pragma once
#include "District.h"
#include "DynamicArray.h"

#define rcastcc reinterpret_cast<const char*>
#define rcastc reinterpret_cast<char*>

namespace elections {
	class CitizensDB;
	class PartiesArr;

	class DistrictsArr {
	private:
		DynamicArray<District*> districts;

	public:
		// Ctor
		DistrictsArr();

		~DistrictsArr() {
		}
		// Setters-----------------------------------------
		void add(District* district);

		// Getters-----------------------------------------
		District& operator[](int index) const;
		const bool isDistExist(int distNum) const;
		const int getLogSize(void) const;

		// Returns true if district's name equal to name 
		const bool isDistrictExistsByName(string name) const;

		// votesArr handler
		void addNewPartyToVotesCounters();

		// Printer operator
		friend ostream& operator<<(ostream& os, const DistrictsArr& districtArr);

		//Save and load from BIN file methods.
		void save(ostream& out) const;
		void load(istream& in);

		void getElectedRepsFromAllDistricts(CitizensDB* _electorsByDistrict, PartiesArr* _partiesArr, CitizensDB* _citizensDB);
		int* getTotalVotingCounters(int partyNum);
	};
}