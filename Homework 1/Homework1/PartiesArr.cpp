#include <iostream>
#include "PartiesArr.h"

using namespace std;

namespace elections {
	PartiesArr::PartiesArr() : parties(nullptr), logSize(0), phsSize(0) {}

	PartiesArr::PartiesArr(const PartiesArr& other)
	{
		*this = other;
	}

	PartiesArr::~PartiesArr()
	{
		delete[] parties;
	};

	void PartiesArr::resize(int newSize)
	{
		Party* temp = new Party[newSize];

		for (int i = 0; i < logSize; ++i)
			temp[i] = parties[i];

		if (logSize >= 1)
			delete[] parties;

		parties = temp;
		phsSize = newSize;
	}

	void PartiesArr::operator=(const PartiesArr& other)
	{
		logSize = other.logSize;
		phsSize = other.phsSize;
		parties = new Party[phsSize];

		for (int i = 0; i < logSize; i++)
			parties[i] = other.parties[i];
	}

	void PartiesArr::add(Party& party)
	{
		if (logSize == phsSize)
			resize(phsSize * 2 + 1);

		parties[logSize] = party;
		++logSize;
	}

	void PartiesArr::addRep(Citizen& rep, int partyNum, int districtNum)
	{
		parties[partyNum].addRepToParty(rep, districtNum);
	}

	void PartiesArr::addNewDistToRepArr(void)
	{
		for (int i = 0; i < logSize; i++)
			parties[i].addEmptyCellToRepArr();
	}


	const int PartiesArr::getLogSize() const
	{
		return logSize;
	}

	Party& PartiesArr::operator[](int index) const
	{
		return parties[index];
	}


	const bool PartiesArr::isCitizenAlreadyLeader(long int id) const
	{
		for (int i = 0; i < logSize; i++)
			if (parties[i].getLeaderId() == id)
				return true;

		return false;
	}

	const bool PartiesArr::isCitizenAlreadyRep(long int id) const
	{
		for (int i = 0; i < logSize; i++)
		{
			if (parties[i].isRepAlreadyExists(id))
				return true;
		}

		return false;
	}
	ostream& operator<<(ostream& os, const PartiesArr& partiesArr)
	{	
		for (int i = 0; i < partiesArr.getLogSize(); i++)
			cout << partiesArr[i];

		return os;
	}
}
