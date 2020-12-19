#pragma once

namespace elections {
	class District {
	private:
		char* name;
		int nameLen, numOfRep, districtNum;

	public:
		// Ctors
		District();
		District(char* _name, int _nameLen, int _numOfRep, int _districtNum);

		// Dtor
		~District();

		// Overload "=" operator
		void operator=(const District&);

		// Getters-------------------------------
		int getDistrictNum(void);
		char* getDistrictName() const;

		// Print one district
		void printDistrict(void) const;
	};
}