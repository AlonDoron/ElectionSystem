#include <iostream>
#include "PartiesArr.h"

using namespace std;

namespace elections {
	PartiesArr::PartiesArr() : parties(nullptr), logSize(0), phsSize(0) {}

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

	void PartiesArr::printParties(void) const
	{
		if (logSize == 0)
			cout << "No parties found!" << endl;

		else
			for (int i = 0; i < logSize; i++)
				parties[i].printParty();
	}

	void PartiesArr::addRep(Citizen* rep, int partyNum, int districtNum)
	{
		parties[partyNum].addRepToParty(*rep, districtNum);
	}

	void PartiesArr::addDistrictToAllParties(void)
	{
		for (int i = 0; i < logSize; i++)
		{
			parties[i].addNewDistrictToRepArr();
			parties[i].addDistrictToVotersArr();
		}
	}

	void PartiesArr::addVoteToDistrictInParty(int partyID, int districtNum)
	{
		parties[partyID].addVoteToDistrict(districtNum);
	}

	const int PartiesArr::getLogSize() const
	{
		return logSize;
	}

	Party& PartiesArr::getPartyByIndex(int idx)
	{
		return parties[idx];
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
}
