#include <iostream>
#include "DistrictsArr.h"
#include "CitizensArr.h";

using namespace std;

namespace elections {
	DistrictsArr::DistrictsArr() : districts(nullptr), logSize(0), phsSize(0) {}

	DistrictsArr::~DistrictsArr() {

		for (int i = 0; i < logSize; i++)
			delete districts[i];

	}

	DistrictsArr::DistrictsArr(const DistrictsArr& other)
	{
		*this = other;
	}

	void DistrictsArr::resize(int newSize)
	{
		District** temp = new District*[newSize];

		for (int i = 0; i < newSize; ++i)
			temp[i] = new District();

		for (int i = 0; i < logSize; ++i)
			*temp[i] = *districts[i];

		for (int i = 0; i < logSize; i++)
			delete districts[i];

		districts = temp;
		phsSize = newSize;
	}

	void DistrictsArr::operator=(const DistrictsArr& other)
	{
		logSize = other.logSize;
		phsSize = other.phsSize;
		districts = new District*[phsSize];

		for (int i = 0; i < logSize; i++)
			districts[i] = other.districts[i];
	}

	District& DistrictsArr::operator[](int index) const
	{
		return *districts[index];
	}

	const bool DistrictsArr::isDistExist(int distNum) const
	{
		return ((distNum < logSize) && (distNum >= 0));
	}


	void DistrictsArr::add(District* district)
	{
		if (logSize == phsSize)
			resize(phsSize * 2 + 1);

		districts[logSize] = district;
		++logSize;
	}


	const int DistrictsArr::getLogSize(void) const
	{
		return logSize;
	}

	const bool DistrictsArr::isDistrictExistsByName(char* name) const
	{
		for (int i = 0; i < logSize; i++)
		{
			if (strcmp(districts[i]->getDistrictName(), name) == 0)
				return true;
		}

		return false;
	}
	void DistrictsArr::addNewPartyToVotesCounters()
	{
		for (int i = 0; i < logSize; i++)
			districts[i]->addVotesCountersForNewParty();


	}

	void DistrictsArr::save(ostream& out) const
	{
		out.write(rcastcc(&logSize), sizeof(logSize));
		out.write(rcastcc(&phsSize), sizeof(phsSize));

		for (int i = 0; i < logSize; i++)
			districts[i]->save(out);
	}

	void DistrictsArr::load(istream& in)
	{
		int newLogSize;
		in.read(rcastc(&newLogSize), sizeof(newLogSize));
		resize(newLogSize);
		logSize = newLogSize;
		in.read(rcastc(&phsSize), sizeof(phsSize));

		for (int i = 0; i < logSize; i++)
			districts[i]->load(in);
	}

	ostream& operator<<(ostream& os, const DistrictsArr& districtArr)
	{
		for (int i = 0; i < districtArr.getLogSize(); i++)
			cout << districtArr[i];

		return os;
	}
}