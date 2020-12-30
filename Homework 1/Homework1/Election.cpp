#include "Election.h"
#include <iostream>
#include <algorithm>

using namespace std;

namespace elections {


	void Election::displayResults()
	{


		int partyNum = partiesArr.getLogSize();

		Result* result = new Result[partyNum];

		// display result relatin to districts of both types
		districtsArr.getElectedRepsFromAllDistricts(&electorsByParty, &partiesArr, &citizensDB);

		int* totalVotesByParty = districtsArr.getTotalVotingCounters(partyNum);

		for (int i = 0; i < partiesArr.getLogSize(); i++)
		{
			result[i].partyNum = i;
			result[i].votes = totalVotesByParty[i];
		}

		sort(result, result + partyNum, [](const Result& res1, const Result& res2) {
			return (res1.votes > res2.votes);
			});

		for (int i = 0; i < partyNum; i++)
		{
			int currPartyNum = result[i].partyNum;
			long int currLeaderID = partiesArr[currPartyNum].getLeaderId();
			Citizen currLeader = citizensDB[currLeaderID];

			cout << "The leader " << currLeader.getName() << " got "
				<< electorsByParty[currPartyNum].getLogSize()
				<< " representatives, and Total votes of: " << result[i].votes << endl;

		}



	}
}
