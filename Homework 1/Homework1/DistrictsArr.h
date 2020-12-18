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

		// Overload "=" operator
		void operator=(const DistrictsArr&);

		// Setters-----------------------------------------
		void add(District& district);

		// Getters-----------------------------------------
		// return district in index "districtNum"
		District* getDistrictByNum(int districtNum);
		int getLogSize(void);

		// Returns true if district's name equal to name 
		bool isDistrictExistsByName(char* name);

		// Prints all districts in DistrictsArr
		void printDistricts(void) const;
	};
}