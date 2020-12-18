#include <iostream>
#include "CitizensDB.h"

using namespace std;

namespace elections {
	CitizensDB::CitizensDB() : phsSize(0), logSize(0), citizensByDist(nullptr) {}

	CitizensDB::CitizensDB(int size) : phsSize(size), logSize(size) {
		citizensByDist = new CitizensArr[size];
	};

	CitizensDB::~CitizensDB() {
		delete[] citizensByDist;

	}

	const int CitizensDB::getLogSize() const {
		return logSize;
	}

	void CitizensDB::resize(int newSize)
	{
		CitizensArr* temp = new CitizensArr[newSize];

		for (int i = 0; i < logSize; ++i)
			temp[i] = citizensByDist[i];

		if (logSize >= 1)
			delete[] citizensByDist;

		citizensByDist = temp;
		phsSize = newSize;
	}

	void CitizensDB::operator=(const CitizensDB& other)
	{
		logSize = other.logSize;
		phsSize = other.phsSize;
		citizensByDist = new CitizensArr[phsSize];

		for (int i = 0; i < logSize; i++)
			citizensByDist[i] = other.citizensByDist[i];
	}

	void CitizensDB::add()
	{
		CitizensArr newCitizensArr;

		if (logSize == phsSize)
			resize(phsSize * 2 + 1);

		citizensByDist[logSize] = newCitizensArr;
		++logSize;
	}

	void CitizensDB::add(CitizensArr& citizensArr, int distId)
	{
		citizensByDist[distId] = citizensArr;
	}

	void CitizensDB::addRep(Citizen& rep, int districtNum)
	{
		citizensByDist[districtNum].add(rep);
	}

	void CitizensDB::printRep(void) const
	{
		for (int i = 0; i < logSize; i++)
		{
			citizensByDist[i].printCitizens();
		}
	}

	CitizensArr& CitizensDB::getCitizensArrByIndex(int ind)
	{
		return citizensByDist[ind];
	}
}
