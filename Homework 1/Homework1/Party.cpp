#include <iostream>
#include "Party.h"
#include "Citizen.h"
#include "CitizensArr.h"

using namespace std;

namespace elections {
	Party::Party() : name(nullptr), nameLen(0), id(0), representatives(), voters(0) {}

	Party::Party(char* _name, int _nameLen, long int _id, int numOfDistricts) :
		nameLen(_nameLen), id(_id), representatives(numOfDistricts), voters(numOfDistricts)
	{
		name = new char[_nameLen + 1];

		memcpy(name, _name, nameLen + 1);

		name[_nameLen] = '\0';
	}

	Party::~Party()
	{
		delete[] name;
	}

	const int Party::getVotesInDist(int idx)
	{
		return voters.getVotesByIndex(idx);
	}

	CitizensArr* Party::getRepListByPercent(int distIdx, int numOfElected)
	{
		CitizensArr* electedReps = new CitizensArr();
		CitizensArr allRepsInDist;

		allRepsInDist = representatives.getCitizensArrByIndex(distIdx);
		//electedReps = (allRepsInDist.getCitizensUntillIndex(numOfElected));

		return electedReps;
	}

	const bool Party::isRepAlreadyExists(long int repId)
	{
		for (int i = 0; i < representatives.getLogSize(); i++)
		{
			CitizensArr currCitizensArr;
			currCitizensArr = representatives.getCitizensArrByIndex(i);

			for (int j = 0; j < currCitizensArr.getLogSize(); j++)
				if (currCitizensArr.getCitizenByIndex(j).getId() == repId)
					return true;
		}

		return false;
	}

	const long int Party::getLeaderId() const
	{
		return id;
	}

	void Party::operator=(const Party& other)
	{
		nameLen = other.nameLen;
		id = other.id;
		name = new char[nameLen + 1];

		for (int i = 0; i < other.nameLen; i++)
			name[i] = other.name[i];

		name[nameLen] = '\0';

		representatives = other.representatives;
		voters = other.voters;
	}

	char* Party::getPartyName() const
	{
		return name;
	}

	void Party::printParty(void) const
	{
		cout << "Party's Name: " << name << " | ID of party leader: " << id << endl;
		cout << "Representatives by district: " << endl;
		representatives.printRep();
	}

	void Party::addRepToParty(Citizen& rep, int districtNum)
	{
		representatives.addCitizenToIndex(rep, districtNum);
	}

	void Party::addNewDistrictToRepArr(void)
	{
		representatives.addEmptyCitizensArr();
	}

	void Party::addDistrictToVotersArr()
	{
		voters.addDistrict();
	}

	void Party::addVoteToDistrict(int districtNum)
	{
		voters.addVote(districtNum);
	}
}