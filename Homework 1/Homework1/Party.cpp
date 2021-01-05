#include <iostream>
#include "Party.h"
#include "Citizen.h"
#include "CitizensArr.h"

using namespace std;

namespace elections {
	Party::Party() : name(), id(0), representatives() {}

	Party::Party(string& _name, long int _id, int numOfDistricts) :
		name(_name), id(_id), representatives(numOfDistricts)
	{}

	Party::Party(const Party& other)
	{
		*this = other;
	}

	Party::~Party()
	{
	}


	const bool Party::isRepAlreadyExists(long int repId)
	{
		if (representatives.isCitizenExistsById(repId))
			return true;
		else
			return false;
	}

	const long int Party::getLeaderId() const
	{
		return id;
	}

	const CitizensDB& Party::getRepresentatives() const
	{
		return representatives;
	}

	Party& Party::operator=(const Party& other)
	{
		id = other.id;
		name = other.name;
		representatives = other.representatives;

		return *this;
	}

	const string& Party::getPartyName() const
	{
		return name;
	}


	void Party::addRepToParty(Citizen& rep, int districtNum)
	{
		representatives.addCitizenToIndex(rep, districtNum);
	}

	void Party::addEmptyCellToRepArr(void)
	{
		representatives.addEmptyCitizensArr();
	}


	ostream& operator<<(ostream& os, const Party& party)
	{

		cout << "Party's Name: " << party.getPartyName() << " | ID of party leader: " << party.getLeaderId() << endl;
		cout << "Representatives by district: " << endl;
		cout << party.getRepresentatives();

		return os;
	}

	void Party::save(ostream& out) const
	{
		out.write(name.c_str(), name.size());
		out.write(rcastcc(&id), sizeof(id));

		representatives.save(out);
	}

	void Party::load(istream& in)
	{
		in.read(rcastc(&name), sizeof(name));
		in.read(rcastc(&id), sizeof(id));

		representatives.load(in);
	}
}