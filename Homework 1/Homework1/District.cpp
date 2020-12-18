#include <iostream>
#include "District.h"

using namespace std;

namespace elections {
	District::District() : name(nullptr), nameLen(0), numOfRep(0), districtNum(0) {}

	District::District(char* _name, int _nameLen, int _numOfRep, int _districtNum) {
		nameLen = _nameLen;
		numOfRep = _numOfRep;
		districtNum = _districtNum;
		name = new char[_nameLen + 1];

		memcpy(name, _name, nameLen + 1);

		name[nameLen] = '\0';
	}

	District::~District()
	{
		delete[] name;
	}

	void District::printDistrict(void) const
	{
		cout << "District Number: " << districtNum
			<< " | Name: " << name << " | Number of representative: " << numOfRep << endl;
	}

	void District::operator=(const District& other)
	{
		numOfRep = other.numOfRep;
		nameLen = other.nameLen;
		districtNum = other.districtNum;
		name = new char[nameLen + 1];

		for (int i = 0; i < other.nameLen; i++)
			name[i] = other.name[i];

		name[nameLen] = '\0';
	}
	int District::getDistrictNum(void)
	{
		return districtNum;
	}

	char* District::getDistrictName() const
	{
		return name;
	}
}

