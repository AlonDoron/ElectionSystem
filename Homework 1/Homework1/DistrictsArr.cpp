#include <iostream>
#include <typeinfo>
#include "DistrictsArr.h"
#include "CitizensArr.h";
#include "CitizensDB.h"
#include "PartiesArr.h"
#include "DividedDistrict.h"

using namespace std;

namespace elections {
	DistrictsArr::DistrictsArr() {}

	District& DistrictsArr::operator[](int index) const
	{
		return *districts[index];
	}

	const bool DistrictsArr::isDistExist(int distNum) const
	{
		int size = districts.size();

		return ((distNum < size) && (distNum >= 0));
	}

	void DistrictsArr::add(District* district)
	{
		if (isDistrictExistsByName(district->getDistrictName()))
		{
			delete district;
			throw ("The district with this name is already exists!!!");
		}

		districts.push_back(district);
	}

	const int DistrictsArr::getLogSize(void) const
	{
		return districts.size();
	}

	const bool DistrictsArr::isDistrictExistsByName(string name) const
	{
		int size = districts.size();

		for (int i = 0; i < size; i++)
			if (districts[i]->getDistrictName() == name)
				return true;

		return false;
	}

	void addVoteTest(District* dist) {
		District temp;
		temp.addVotesTest(dist);
	}

	void DistrictsArr::addNewPartyToVotesCounters()
	{
		// TODO: implement applyall 
		// districts.applyall(addVotesCountersForNewParty());
		districts.applyAll(addVoteTest);

		//int size = districts.size();

		//for (int i = 0; i < size; i++)
		//	districts[i]->addVotesCountersForNewParty();
	}

	void DistrictsArr::init()
	{
		districts.resize(0);
	}

	void DistrictsArr::save(ostream& out) const
	{
		int type;
		int size = districts.size();
		out.write(rcastcc(&size), sizeof(size));

		for (int i = 0; i < size; i++) {
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
		int size = districts.size();
		int* res = new int[partyNum];

		for (int i = 0; i < partyNum; i++)
			res[i] = 0;

		for (int i = 0; i < partyNum; i++)
			for (int j = 0; j < size; j++)
				res[i] += districts[j]->getVotesInIndex(i);

		return res;
	}


	ostream& operator<<(ostream& os, const DistrictsArr& districtArr)
	{
		int size = districtArr.getLogSize();

		for (int i = 0; i < size; i++)
			cout << districtArr[i];

		return os;
	}
}