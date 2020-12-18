#include <iostream>
#include "Citizen.h"
#include "District.h"

using namespace std;

namespace elections {
	Citizen::Citizen() : name(nullptr), nameLen(0), id(0), year(0), district(nullptr), voted(false) {}

	Citizen::Citizen(char* _name, int _nameLen, long int _id, int _year, District* _district) :
		nameLen(_nameLen), id(_id), year(_year), district(_district)
	{
		name = new char[_nameLen + 1];

		memcpy(name, _name, nameLen);

		name[nameLen] = '\0';
	}

	Citizen::~Citizen()
	{
		delete[] name;
	}

	void Citizen::operator=(const Citizen& other)
	{
		nameLen = other.nameLen;
		year = other.year;
		id = other.id;
		name = new char[nameLen + 1];
		district = other.district;

		memcpy(name, other.name, other.nameLen);

		name[nameLen] = '\0';
	}

	const bool Citizen::getVoted() const
	{
		return voted;
	}

	const bool Citizen::setVoted(bool val) {
		voted = val;
		return 1;
	}

	const int Citizen::getDistrictNum() const
	{
		return district->getDistrictNum();
	}

	const long int Citizen::getId(void) const
	{
		return id;
	}

	void Citizen::printCitizen(void)
	{
		cout << "Name: " << name << " | Year of birth: " << year
			<< " | id: " << id << " | District: " << district->getDistrictNum() << endl;
	}

	char* Citizen::getName()
	{
		return name;
	}
}