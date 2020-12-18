#include <iostream>
#include "CitizensArr.h"

using namespace std;

namespace elections {
	CitizensArr::CitizensArr() : citizens(nullptr), logSize(0), phsSize(0) {}

	CitizensArr::CitizensArr(int size) : logSize(0), phsSize(size) {
		citizens = new Citizen[size];
	}

	CitizensArr::~CitizensArr() {
		delete[] citizens;
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

	void CitizensArr::add_citizenArr(CitizensArr& other)
	{
		int size = other.getLogSize();

		for (int i = 0; i < size; i++)
			add(other.getCitizenByIndex(i));
	}

	void CitizensArr::printCitizens(void)
	{
		if (logSize == 0)
			cout << "No citizens found!" << endl;

		else
			for (int i = 0; i < logSize; i++)
				citizens[i].printCitizen();
	}

	Citizen* CitizensArr::getCitizen(long int citizenId)
	{

		for (int i = 0; i < logSize; i++) {
			if (citizenId == citizens[i].getId()) {
				return &(citizens[i]);
			}
		}

		return nullptr;
	}

	bool CitizensArr::setLogSize(int size)
	{
		logSize = size;
		return 1;
	}

	bool CitizensArr::setPhsSize(int size)
	{
		phsSize = size;
		return 1;
	}

	const int CitizensArr::getLogSize() const
	{
		return logSize;
	}

	Citizen& CitizensArr::getCitizenByIndex(int ind)
	{
		return citizens[ind];
	}

	CitizensArr* CitizensArr::getElectReps(int numOfElected)
	{
		CitizensArr* electedReps = new CitizensArr();

		for (int i = 0; i < numOfElected; i++)
			electedReps->add(citizens[i]);
			
		cout << "Everything is okay!" << endl;

		return electedReps;
	}
}





