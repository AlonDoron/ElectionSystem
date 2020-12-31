#include <iostream>
#include "PartiesArr.h"

using namespace std;

namespace elections {
	PartiesArr::PartiesArr() : parties(nullptr), logSize(0), phsSize(0) {}

	PartiesArr::PartiesArr(int size) : logSize(0), phsSize(size)
	{
		parties = new Party[size];
	}

	PartiesArr::PartiesArr(const PartiesArr& other)
	{
		*this = other;
	}

	PartiesArr::~PartiesArr()
	{
		delete[] parties;
		logSize = phsSize = 0;
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

	PartiesArr& PartiesArr::operator=(const PartiesArr& other)
	{
		logSize = other.logSize;
		phsSize = other.phsSize;
		parties = new Party[phsSize];

		for (int i = 0; i < logSize; i++)
			parties[i] = other.parties[i];

		return *this;
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

	void PartiesArr::save(ostream& out) const
	{
		out.write(rcastcc(&logSize), sizeof(logSize));

		for (int i = 0; i < logSize; i++)
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

	ostream& operator<<(ostream& os, const PartiesArr& partiesArr)
	{
		for (int i = 0; i < partiesArr.getLogSize(); i++)
		{
			cout << "Party number: " << i << " ";
			cout << partiesArr[i];

		}

		return os;
	}
}
