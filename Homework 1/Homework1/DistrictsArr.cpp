#include <iostream>
#include "DistrictsArr.h"
#include "CitizensArr.h";

using namespace std;

namespace elections {
	DistrictsArr::DistrictsArr() : districts(nullptr), logSize(0), phsSize(0) {}

	DistrictsArr::~DistrictsArr() {
		delete[] districts;
	}

	void DistrictsArr::resize(int newSize)
	{
		District* temp = new District[newSize];

		for (int i = 0; i < logSize; ++i)
			temp[i] = districts[i];

		if (phsSize >= 1)
			delete[] districts;

		districts = temp;
		phsSize = newSize;
	}

	void DistrictsArr::operator=(const DistrictsArr& other)
	{
		logSize = other.logSize;
		phsSize = other.phsSize;
		districts = new District[phsSize];

		for (int i = 0; i < logSize; i++)
			districts[i] = other.districts[i];
	}

	District* DistrictsArr::getDistrictByNum(int districtNum)
	{
		if (districts != nullptr)
			if (districts[districtNum].getDistrictName() != nullptr)
				return &districts[districtNum];

		return nullptr;
	}

	void DistrictsArr::add(District& district)
	{
		if (logSize == phsSize)
			resize(phsSize * 2 + 1);

		districts[logSize] = district;
		++logSize;
	}

	void DistrictsArr::printDistricts(void) const
	{
		if (logSize == 0)
			cout << "No districts found!" << endl;

		else
			for (int i = 0; i < logSize; i++)
				districts[i].printDistrict();
	}

	int DistrictsArr::getLogSize(void)
	{
		return logSize;
	}

	bool DistrictsArr::isDistrictExistsByName(char* name)
	{
		for (int i = 0; i < logSize; i++)
		{
			if (strcmp(districts[i].getDistrictName(), name) == 0)
				return true;
		}

		return false;
	}
}