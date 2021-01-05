#include "DividedDistrict.h"
#include "PartiesArr.h"



namespace elections {

	DividedDistrict::DividedDistrict() : District() {};

	DividedDistrict::DividedDistrict(string _name, int _numOfRep, int _districtNum)
		: District(_name,  _numOfRep, _districtNum) {}


	void DividedDistrict::setElected(PartiesArr* _partiesArr, CitizensDB* _electorsByParty, CitizensDB* _citizensDB)
	{
		int currRepsNum;
		int partyNum = _partiesArr->getLogSize();
		CitizensArr curr, RepsInPartyi;
		int* votesPerc = votesCounter.getPercentageVotes();
		PartiesArr partiesArr = *_partiesArr;
		Party currParty;
		CitizensDB currDB;
		int partyWin = votesCounter.getWinningPartID();

		cout << "     ***** District " << name << " (divided system) *****     " << endl;;

		for (int i = 0; i < partyNum; i++)
		{	// calculate how many reps from each party
			long int leaderID = (*_partiesArr)[i].getLeaderId();
			Citizen leader;
			leader = (*_citizensDB)[leaderID];

			CitizensArr currRes;

			currParty = partiesArr[i];

			currDB = currParty.getRepresentatives();

			RepsInPartyi = currDB[districtNum];

			currRepsNum = (votesPerc[i] * numOfRep) / 100;

			curr = RepsInPartyi.getCitizensUntillIndex(currRepsNum);

			currRes.appendCitizensArr(curr);

			cout << "The district is giving the following " << currRepsNum << " representatives "
				<< "to " << leader.getName() << ":" <<endl<< currRes << endl;

			(*_electorsByParty)[i].appendCitizensArr(currRes);

		}

	}



}