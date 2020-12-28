#include <iostream>
#include "Party.h"
#include "Citizen.h"
#include "CitizensArr.h"

using namespace std;

namespace elections {
	Party::Party() : name(nullptr), nameLen(0), id(0), representatives() {}

	Party::Party(char* _name, int _nameLen, long int _id, int numOfDistricts) :
		nameLen(_nameLen), id(_id), representatives(numOfDistricts)
	{
		name = new char[_nameLen + 1];

		memcpy(name, _name, nameLen + 1);

		name[_nameLen] = '\0';
	}

	Party::Party(const Party& other)
	{
		*this = other;
	}

	Party::~Party()
	{
		delete[] name;
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
		nameLen = other.nameLen;
		id = other.id;
		name = new char[nameLen + 1];

		for (int i = 0; i < other.nameLen; i++)
			name[i] = other.name[i];

		name[nameLen] = '\0';

		representatives = other.representatives;

		return *this;
	}

	const char* Party::getPartyName() const
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
		out.write(rcastcc(&nameLen), sizeof(nameLen));
		out.write(name, nameLen);
		out.write(rcastcc(&id), sizeof(id));

		representatives.save(out);
	}

	void Party::load(istream& in)
	{
		in.read(rcastc(&nameLen), sizeof(nameLen));
		name = new char[nameLen + 1];
		in.read(name, nameLen);
		name[nameLen] = '\0';
		in.read(rcastc(&id), sizeof(id));

		representatives.load(in);
	}
}