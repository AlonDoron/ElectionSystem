#include <iostream>
#include <typeinfo>
#include "DistrictsArr.h"
#include "CitizensArr.h";
#include "CitizensDB.h"
#include "PartiesArr.h"
#include "DividedDistrict.h"

using namespace std;

namespace elections {
	DistrictsArr::DistrictsArr() : districts(nullptr), logSize(0), phsSize(0) {}

	DistrictsArr::~DistrictsArr() {

		for (int i = 0; i < logSize; i++)
			delete districts[i];

		logSize = phsSize = 0;
	}

	DistrictsArr::DistrictsArr(const DistrictsArr& other)
	{
		*this = other;
	}

	void DistrictsArr::resize(int newSize)
	{
		District** temp = new District * [newSize];

		/*for (int i = 0; i < newSize; ++i)
			temp[i] = new District();*/

		for (int i = 0; i < logSize; ++i)
			temp[i] = districts[i];

		//for (int i = 0; i < logSize; i++)
		//	delete districts[i];

		districts = temp;
		phsSize = newSize;
	}

	DistrictsArr& DistrictsArr::operator=(const DistrictsArr& other)
	{
		logSize = other.logSize;
		phsSize = other.phsSize;
		districts = new District * [phsSize];

		for (int i = 0; i < logSize; i++)
			districts[i] = other.districts[i];

		return *this;
	}

	District& DistrictsArr::operator[](int index) const
	{
		return *districts[index];
	}

	const bool DistrictsArr::isDistExist(int distNum) const
	{
		return ((distNum < logSize) && (distNum >= 0));
	}


	void DistrictsArr::add(District* district)
	{
		if (logSize == phsSize)
			resize(phsSize * 2 + 1);

		districts[logSize] = district;
		++logSize;
	}


	const int DistrictsArr::getLogSize(void) const
	{
		return logSize;
	}

	const bool DistrictsArr::isDistrictExistsByName(string name) const
	{
		for (int i = 0; i < logSize; i++)
			if (districts[i]->getDistrictName() ==  name)
				return true;

		return false;
	}

	void DistrictsArr::addNewPartyToVotesCounters()
	{
		for (int i = 0; i < logSize; i++)
			districts[i]->addVotesCountersForNewParty();
	}

	void DistrictsArr::save(ostream& out) const
	{
		int type;
		out.write(rcastcc(&logSize), sizeof(logSize));

		for (int i = 0; i < logSize; i++) {
			(typeid(*districts[i]) == typeid(District)) ? type = 0 : type = 1;

			out.write(rcastcc(&type), sizeof(type));
			districts[i]->save(out);
		}

	}

	void DistrictsArr::load(istream& in)
	{
		int newLogSize, type;
		District* temp;
		in.read(rcastc(&newLogSize), sizeof(newLogSize));

		for (int i = 0; i < newLogSize; i++) {
			in.read(rcastc(&type), sizeof(type));
			if (type == 0)
				temp = new District();
			else
				temp = new DividedDistrict();

			temp->load(in);
			add(temp);
		}
	}

	void DistrictsArr::getElectedRepsFromAllDistricts(CitizensDB* _electorsByDistrict, PartiesArr* partiesArr, CitizensDB* _citizensDB)
	{
		int size = _electorsByDistrict->getLogSize();
		District* currDist;
		CitizensArr curr;
		int citizensNum;

		for (int i = 0; i < partiesArr->getLogSize(); i++)
		{
			currDist = districts[i];

			citizensNum = currDist->getCitizensNum();

			currDist->setElected(partiesArr, _electorsByDistrict, _citizensDB);

			VotesCounter votes = currDist->getVotesCounter();
			votes.printVotingStatictic(partiesArr, citizensNum);
		}

	}

	int* DistrictsArr::getTotalVotingCounters(int partyNum)
	{
		int* res = new int[partyNum];

		for (int i = 0; i < partyNum; i++)
			res[i] = 0;

		for (int i = 0; i < partyNum; i++)
			for (int j = 0; j < logSize; j++)
				res[i] += districts[j]->getVotesInIndex(i);

		return res;
	}


	ostream& operator<<(ostream& os, const DistrictsArr& districtArr)
	{
		for (int i = 0; i < districtArr.getLogSize(); i++)
			cout << districtArr[i];

		return os;
	}
}