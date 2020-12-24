#pragma once
#include "District.h"

namespace elections {

class DividedDistrict : public District {

public:
	DividedDistrict();

	DividedDistrict(char* _name, int _nameLen, int _numOfRep, int _districtNum);


	virtual void TEST();

};

}