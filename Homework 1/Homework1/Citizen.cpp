#include <iostream>
#include "Citizen.h"
#include "District.h"
#include "DividedDistrict.h"

using namespace std;

namespace elections {
	Citizen::Citizen() : name(),  id(0), year(0), district(nullptr), voted(false) {}

	Citizen::Citizen(string& _name, long int _id, int _year, District* _district) :
		name(_name), id(_id), year(_year), district(_district) {}

	Citizen::Citizen(const Citizen& other) {
		*this = other;
	}

	Citizen::~Citizen() {}

	Citizen& Citizen::operator=(const Citizen& other)
	{
		year = other.year;
		id = other.id;
		name = other.name;
		district = other.district;

		return *this;
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

	const bool Citizen::setName(string& _name)
	{
		name = _name;

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


	const string& Citizen::getName() const
	{
		return name;
	}

	void Citizen::save(ostream& out) const
	{
		int distType;

		out.write(rcastcc(this), sizeof(*this));
		out.write(name.c_str(),name.size());

		(typeid(district) == typeid(District)) ? distType = 0 : distType = 1;

		out.write(rcastcc(&distType), sizeof(distType));
		district->save(out);
	}

	void Citizen::load(istream& in)
	{
		int distType;

		in.read(rcastc(this), sizeof(*this));
		in.read(rcastc(&name), sizeof(name));

		in.read(rcastc(&distType), sizeof(distType));
		if (distType == 0)
			district = new District();
		else
			district = new DividedDistrict();

		district->load(in);
	}

	ostream& operator<<(ostream& os, const Citizen& citizen)
	{
		cout << "Name: " << citizen.getName() << " | Year of birth: " << citizen.getYear()
			<< " | id: " << citizen.getId() << " | District: " << citizen.getDistrictNum() << endl;

		return os;
	}
}