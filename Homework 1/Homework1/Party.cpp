#include <iostream>
#include <string>
#include "Party.h"
#include "Citizen.h"
#include "CitizensArr.h"

using namespace std;

namespace elections {
	Party::Party() : name(), id(0), representatives() {}

	Party::Party(string& _name, long int _id, int numOfDistricts) :
		name(_name), id(_id), representatives(numOfDistricts)
	{}

	const bool Party::isRepAlreadyExists(long int repId) const
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

	CitizensDB& Party::getRepresentatives()
	{
		return representatives;
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
		Party& tempParty = const_cast<Party&>(party);
		CitizensDB& reps = tempParty.getRepresentatives();

		cout << "Party's Name: " << party.getPartyName() << " | ID of party leader: " << party.getLeaderId() << endl;
		cout << "Representatives by district: " << endl;
		cout << reps;

		return os;
	}

	void Party::save(ostream& out) const
	{
		out.write(rcastcc(&id), sizeof(id));
		out.write(name.c_str(), name.size() + 1);

		representatives.save(out);
	}

	void Party::load(istream& in)
	{
		in.read(rcastc(&id), sizeof(id));
		getline(in, name, '\0');

		representatives.load(in);
	}
}