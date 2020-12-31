#include "Election.h"
#include <iostream>
#include <algorithm>

using namespace std;

namespace elections {
	void Election::displayResults()
	{	
		int partyNum = partiesArr.getLogSize();

		// create a general voting result structre array for future use
		Result* result = new Result[partyNum];

		// display result relating to districts of both types + filling electorsByParty with electors 
		districtsArr.getElectedRepsFromAllDistricts(&electorsByParty, &partiesArr, &citizensDB);

		// getting counters from each district
		int* totalVotesByParty = districtsArr.getTotalVotingCounters(partyNum);

		// setting results array with collected data
		for (int i = 0; i < partiesArr.getLogSize(); i++)
		{
			result[i].partyNum = i;
			result[i].votes = totalVotesByParty[i];
		}
		// sorting the array by number of votes to show results from top down
		sort(result, result + partyNum, [](const Result& res1, const Result& res2) {
			return (res1.votes > res2.votes);
			});

		// displaying results following project intructions
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
