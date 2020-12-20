#pragma once
#include "District.h"

namespace elections {
	class DistrictsArr {
	private:
		int phsSize = 0, logSize = 0;
		District* districts;

		// Resizing districts arr and updating logSize, phsSize
		void resize(int size);

	public:
		// Ctor
		DistrictsArr();

		// Dtor
		~DistrictsArr();

		//copy ctor
		DistrictsArr(const DistrictsArr&);

		// Overload "=" operator
		void operator=(const DistrictsArr&);

		// Setters-----------------------------------------
		void add(District& district);

		// Getters-----------------------------------------
		District& operator[](int index) const;
		const bool isDistExist(int distNum) const;
		const int getLogSize(void) const;

		// Returns true if district's name equal to name 
		const bool isDistrictExistsByName(char* name) const;

		// votesArr handler
		void addNewPartyToVotesCounters();

		// Printer operator
		friend ostream& operator<<(ostream& os, const DistrictsArr& districtArr);
	};
}