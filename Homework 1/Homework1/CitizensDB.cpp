#include <iostream>
#include "CitizensDB.h"

using namespace std;

namespace elections {
	CitizensDB::CitizensDB() : phsSize(0), logSize(0), citizensByDist(nullptr) {}

	CitizensDB::CitizensDB(int size) : phsSize(size), logSize(size) {
		citizensByDist = new CitizensArr[size];
	}
	CitizensDB::CitizensDB(const CitizensDB& other)
	{
		*this = other;
	}

	CitizensDB::~CitizensDB() {
		delete[] citizensByDist;

	}

	const int CitizensDB::getLogSize() const {
		return logSize;
	}

	const int CitizensDB::getPhsSize() const
	{
		return phsSize;
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

	bool CitizensDB::setLogSize(int size)
	{
		logSize = size;

		return true;
	}

	bool CitizensDB::setPhsSize(int size)
	{
		phsSize = size;

		return true;
	}

	void CitizensDB::addEmptyCitizensArr()
	{
		CitizensArr newCitizensArr;

		if (logSize == phsSize)
			resize(phsSize * 2 + 1);

		citizensByDist[logSize] = newCitizensArr;
		++logSize;
	}

	void CitizensDB::addCitizenToIndex(Citizen& citizen, int index)
	{
		citizensByDist[index].add(citizen);
	}


	CitizensArr& CitizensDB::operator[](int index) const
	{
		return citizensByDist[index];
	}

	const bool CitizensDB::isCitizenExistsById(long int id) const {
		for (int i = 0; i < logSize; i++)
			if (citizensByDist[i].isCitizenExistsById(id))
				return true;

		return false;
	}

	Citizen& CitizensDB::operator[](long int id) const
	{
		for (int i = 0; i < logSize; i++)
			if (citizensByDist[i].isCitizenExistsById(id))
				return (citizensByDist[i])[id];
	}

	CitizensArr& CitizensDB::getCitizensArrByIndex(int ind)
	{
		return citizensByDist[ind];
	}

	ostream& operator<<(ostream& os, const CitizensDB& citizensDB)
	{
		for (int i = 0; i < citizensDB.getLogSize(); i++)
			cout << citizensDB[i];

		return os;
	}
}
