#include "Election.h"

namespace elections {


	void RegularElection::displayResults()
	{
		int partyNum = partiesArr.getLogSize();

		Result* result = new Result[partyNum];

		// display result relatin to districts of both types
		districtsArr.getElectedRepsFromAllDistricts(&electorsByParty, &partiesArr,&citizensDB);
		
		int* totalVotesByParty = districtsArr.getTotalVotingCounters(partyNum);

		for (int i = 0; i < partiesArr.getLogSize(); i++)
		{
			result[i].partyNum = i;
			result[i].votes = totalVotesByParty[i];
		}


		for (int i = 0; i < partyNum; i++)
		{
			long int currLeaderID = partiesArr[i].getLeaderId();
			Citizen currLeader = citizensDB[currLeaderID];

			cout << "The leader " << currLeader.getName() << " got " << electorsByParty[i].getLogSize()
				<< " representatives, and Total votes of: " << result[i].votes << endl;

		}

		

	}

	void RegularElection::getElectedRepsFromAllDistricts()
	{
		//int distNum = districtsArr.getLogSize();
		//District* currDist;
		//CitizensArr curr;

		//for (int i = 0; i < distNum; i++)
		//{
		//	currDist = &districtsArr[i];
		//		
		//	curr = currDist->getElctedReps(&partiesArr);

		//	cout << curr<<endl;

		//	electorsByDistrict[i] = curr;
		//}

	}

}
