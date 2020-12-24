#include "DividedDistrict.h"



namespace elections {

	DividedDistrict::DividedDistrict() : District() {};

	DividedDistrict::DividedDistrict(char* _name, int _nameLen, int _numOfRep, int _districtNum)
		: District(_name, _nameLen, _numOfRep, _districtNum) {}
	CitizensArr DividedDistrict::getElctedReps(PartiesArr* partiesAr)
	{
		//int currRepsNum;
		//int partyNum = _partiesArr->getLogSize();
		CitizensArr res, curr, RepsInPartyi;
		//int* votesPerc = votesCounter.getPercentageVotes();
		//PartiesArr partiesArr = *_partiesArr;
		//Party currParty;
		//CitizensDB currDB;

		//int winningParty = votesCounter.getWinningPartID();

		//for (int i = 0; i < partyNum; i++)
		//{	// calculate how many reps from each party
		//	currParty = partiesArr[i];
		//	currDB = currParty.getRepresentatives();
		//	RepsInPartyi = currDB[districtNum];
		//	currRepsNum = (votesPerc[i] * numOfRep) / 100;
		//	curr = RepsInPartyi.getCitizensUntillIndex(currRepsNum);
		//	res.appendCitizensArr(curr);
		//}

		return res;
	}
	;


}