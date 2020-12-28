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

	Citizen::Citizen(const Citizen& other) {
		*this = other;
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

	const bool Citizen::setId(long int _id)
	{
		id = _id;

		return 1;
	}

	const bool Citizen::setName(char* _name, int _nameLen)
	{
		nameLen = _nameLen;

		if (name)
			delete[] name;

		name = new char[nameLen + 1];
		memcpy(name, _name, nameLen);
		name[nameLen] = '\0';

		return 1;
	}

	const bool Citizen::setDistrict(District* _district)
	{
		district = _district;

		return true;
	}

	const bool Citizen::setYear(int _year)
	{
		year = _year;

		return true;
	}

	const int Citizen::getDistrictNum() const
	{
		return district->getDistrictNum();
	}

	const long int Citizen::getId(void) const
	{
		return id;
	}

	const int Citizen::getYear(void) const
	{
		return year;
	}


	const char* Citizen::getName() const
	{
		return name;
	}

	void Citizen::save(ostream& out) const
	{
		out.write(rcastcc(this), sizeof(*this));
		out.write(name, nameLen);

		district->save(out);
	}

	void Citizen::load(istream& in)
	{
		in.read(rcastc(this), sizeof(*this));
		name = new char[nameLen + 1];
		in.read(name, nameLen);
		name[nameLen] = '\0';

		district = new District();
		district->load(in);
	}

	ostream& operator<<(ostream& os, const Citizen& citizen)
	{
		cout << "Name: " << citizen.getName() << " | Year of birth: " << citizen.getYear()
			<< " | id: " << citizen.getId() << " | District: " << citizen.getDistrictNum() << endl;

		return os;
	}
}