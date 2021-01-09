#include <iostream>
#include "CitizensArr.h"

using namespace std;

namespace elections {
	CitizensArr::CitizensArr(int size) : citizens(size) {}

	int CitizensArr::getLogSize()
	{
		return citizens.size();
	}

	void CitizensArr::add(Citizen& citizen)
	{
		citizens.push_back(citizen);
	}

	void CitizensArr::appendCitizensArr(CitizensArr& other)
	{
		int size = citizens.size();

		for (int i = 0; i < size; i++)
			citizens.push_back(other[i]);
	}

	void CitizensArr::init()
	{
		citizens.resize(0);
	}

	const Citizen& CitizensArr::operator[](int index) const
	{
		return citizens[index];
	}

	const Citizen& CitizensArr::operator[](long int id) const
	{
		int size = citizens.size();

		for (int i = 0; i < size; i++)
			if (id == citizens[i].getId())
				return citizens[i];
	}

	void CitizensArr::save(ostream& out) const
	{
		int size = citizens.size();

		out.write(rcastcc(&size), sizeof(size));

		for (int i = 0; i < size; i++)
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
		int size = citizens.size();

		for (int i = 0; i < size; i++)
			if (citizens[i].getId() == id)
				return true;

		return false;
	}

	DynamicArray<Citizen>& CitizensArr::getCitizens()
	{
		return citizens;
	}

	CitizensArr CitizensArr::getCitizensUntillIndex(int numOfElected)
	{
		CitizensArr electedReps;

		for (int i = 0; i < numOfElected; i++)
			electedReps.add(citizens[i]);

		return electedReps;
	}

	ostream& operator<<(ostream& os, CitizensArr& citizensArr)
	{
		int size = citizensArr.getCitizens().size();

		for (int i = 0; i < size; i++)
			cout << citizensArr[i];

		return os;
	}
}





