#include <iostream>
#include "CitizensArr.h"

using namespace std;

namespace elections {
	CitizensArr::CitizensArr() : citizens(nullptr), logSize(0), phsSize(0) {}

	CitizensArr::CitizensArr(int size) : logSize(0), phsSize(size) {
		citizens = new Citizen[size];
	}

	CitizensArr::CitizensArr(const CitizensArr& other)
	{
		*this = other;
	}

	CitizensArr::~CitizensArr() {
		delete[] citizens;
		logSize = phsSize = 0;
	}

	void CitizensArr::resize(int newSize)
	{
		Citizen* temp = new Citizen[newSize];

		for (int i = 0; i < logSize; ++i)
			temp[i] = citizens[i];

		if (logSize >= 1)
			delete[] citizens;

		citizens = temp;
		phsSize = newSize;
	}

	void CitizensArr::operator=(const CitizensArr& other)
	{
		logSize = other.logSize;
		phsSize = other.phsSize;
		citizens = new Citizen[phsSize];

		for (int i = 0; i < logSize; i++)
			citizens[i] = other.citizens[i];
	}

	void CitizensArr::add(Citizen& citizen)
	{
		if (logSize == phsSize)
			resize(phsSize * 2 + 1);

		citizens[logSize] = citizen;
		++logSize;
	}

	void CitizensArr::appendCitizensArr(CitizensArr& other)
	{
		int size = other.getLogSize();

		for (int i = 0; i < size; i++)
			add(other.getCitizenByIndex(i));
	}


	Citizen& CitizensArr::operator[](int index) const
	{
		return citizens[index];
	}

	Citizen& CitizensArr::operator[](long int id) const
	{
		for (int i = 0; i < logSize; i++)
			if (id == citizens[i].getId())
				return citizens[i];
	}

	void CitizensArr::save(ostream& out) const
	{
		out.write(rcastcc(&logSize), sizeof(logSize));

		for (int i = 0; i < logSize; i++)
			citizens[i].save(out);
	}

	void CitizensArr::load(istream& in)
	{
		int newLogSize;
		in.read(rcastc(&newLogSize), sizeof(newLogSize));

		for (int i = 0; i < newLogSize; i++)
		{
			Citizen temp;
			temp.load(in);
			add(temp);
		}
	}

	const bool CitizensArr::isCitizenExistsById(long int id) const {
		for (int i = 0; i < logSize; i++)
			if (citizens[i].getId() == id)
				return true;

		return false;
	}

	bool CitizensArr::setLogSize(int size)
	{
		logSize = size;

		return true;
	}

	bool CitizensArr::setPhsSize(int size)
	{
		phsSize = size;

		return true;
	}

	const int CitizensArr::getLogSize() const
	{
		return logSize;
	}

	const int CitizensArr::getPhsSize() const
	{
		return phsSize;
	}

	Citizen& CitizensArr::getCitizenByIndex(int ind)
	{
		return citizens[ind];
	}

	CitizensArr CitizensArr::getCitizensUntillIndex(int numOfElected)
	{
		CitizensArr electedReps;

		for (int i = 0; i < numOfElected; i++)
			electedReps.add(citizens[i]);

		return electedReps;
	}

	ostream& operator<<(ostream& os, const CitizensArr& citizensArr)
	{
		for (int i = 0; i < citizensArr.getLogSize(); i++)
			cout << citizensArr[i];

		return os;
	}
}





