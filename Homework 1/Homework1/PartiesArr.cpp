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

	void PartiesArr::addRep(Citizen& rep, int partyNum, int districtNum)
	{
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


	void PartiesArr::isCitizenAlreadyLeader(long int id) const
	{
		int size = parties.size();

		for (int i = 0; i < size; i++)
			if (parties[i].getLeaderId() == id)
				throw "This citizen is already party leader! ";
	}

	void PartiesArr::isCitizenAlreadyRep(long int id)
	{
		int size = parties.size();

		for (int i = 0; i < size; i++)
		{
			parties[i].isRepAlreadyExists(id);
		}
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
