#include "DividedDistrict.h"



namespace elections {

	DividedDistrict::DividedDistrict() : District() {};

	DividedDistrict::DividedDistrict(char* _name, int _nameLen, int _numOfRep, int _districtNum)
		: District(_name, _nameLen, _numOfRep, _districtNum) {};


}