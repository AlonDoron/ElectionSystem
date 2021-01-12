#include <iostream>
#include "PartiesArr.h"

using namespace std;

namespace elections {
	PartiesArr::PartiesArr() {}

	void PartiesArr::init()
	{
		parties.resize(0);
	}

	void PartiesArr::add(Party& party)
	{
		parties.push_back(party);
	}

	void PartiesArr::addRep(Citizen& rep, int partyNum, int districtNum, int numOfDistrict)
	{
		if (!((partyNum < parties.size() && (partyNum >= 0))))
			throw "number of party is out of range !!!";
		if (!((districtNum < numOfDistrict && (districtNum >= 0))))
			throw "number of district is out of range !!!";

		parties[partyNum].addRepToParty(rep, districtNum);
	}

	void PartiesArr::addNewDistToRepArr(void)
	{
		int size = parties.size();

		for (int i = 0; i < size; i++)
			parties[i].addEmptyCellToRepArr();
	}


	const int PartiesArr::getLogSize() const
	{
		return parties.size();
	}

	const Party& PartiesArr::operator[](int index) const
	{
		return parties[index];
	}


	const bool PartiesArr::isCitizenAlreadyLeader(long int id) const
	{
		int size = parties.size();

		for (int i = 0; i < size; i++)
			if (parties[i].getLeaderId() == id)
				return true;

		return false;
	}

	const bool PartiesArr::isCitizenAlreadyRep(long int id) const
	{
		int size = parties.size();

		for (int i = 0; i < size; i++)
		{
			if (parties[i].isRepAlreadyExists(id))
				return true;
		}

		return false;
	}

	void PartiesArr::isPartyNumberExist(int partyNum)
	{
		if (!(partyNum >= 0 && partyNum < parties.size()))
			throw "party does not exist !!!";
	}

	void PartiesArr::save(ostream& out) const
	{
		int size = parties.size();

		out.write(rcastcc(&size), sizeof(size));

		for (int i = 0; i < size; i++)
			parties[i].save(out);
	}

	void PartiesArr::load(istream& in)
	{
		int newLogSize = 0;

		in.read(rcastc(&newLogSize), sizeof(newLogSize));

		for (int i = 0; i < newLogSize; i++) {
			Party temp;
			temp.load(in);

			add(temp);
		}
	}

	ostream& operator<<(ostream& os, PartiesArr& partiesArr)
	{
		for (int i = 0; i < partiesArr.getLogSize(); i++)
		{
			cout << "Party number: " << i << " ";
			cout << partiesArr[i];
		}

		return os;
	}
}
