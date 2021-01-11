#include <iostream>
#include <string>
#include "District.h"
#include "PartiesArr.h"

using namespace std;

namespace elections {
	District::District() : name(), numOfRep(0), districtNum(0), citizensNum(0) {}

	District::District(string& _name, int _numOfRep, int _districtNum) {
		if (_numOfRep < 0)
			throw "number of reps is out of range !! ";
		else if (_name.length() == 0)
			throw "name can't be empty !! ";


		name = _name;
		numOfRep = _numOfRep;
		districtNum = _districtNum;
		citizensNum = 0;

	}

	const int District::getDistrictNum(void) const
	{
		return districtNum;
	}

	const string& District::getDistrictName() const
	{
		return name;
	}
	const int District::getNumOfRep() const
	{
		return numOfRep;
	}
	const int District::getCitizensNum() const
	{
		return citizensNum;
	}
	const VotesCounter& District::getVotesCounter()
	{
		return votesCounter;
	}
	void District::addVotesCountersForNewParty()
	{
		votesCounter.addEmptyCounter();
	}
	void District::addVoteToVotesCountersInIdx(int partyNum)
	{
		votesCounter.addVote(partyNum);
		votesCounter.updatePercentage();
		votesCounter.updateWinner();
	}
	const int District::getVotesInIndex(int idx) const
	{
		return votesCounter[idx];
	}

	void District::addOneCitizen()
	{
		citizensNum++;
	}

	void District::setElected(PartiesArr* _partiesArr, CitizensDB* _electorsByParty, CitizensDB* _citizensDB)
	{
		int currRepsNum;
		int partyNum = _partiesArr->getLogSize();
		CitizensArr res, curr, RepsInPartyi;
		vector<int> votesPerc = votesCounter.getPercentageVotes();
		PartiesArr partiesArr = *_partiesArr;
		Party currParty;
		CitizensDB currDB;
		int partyWin = votesCounter.getWinningPartID();

		printResultElectionInDist(_partiesArr, _citizensDB);

		for (int i = 0; i < partyNum; i++)
		{	// calculate how many reps from each party
			currParty = partiesArr[i];

			currDB = currParty.getRepresentatives();

			RepsInPartyi = currDB[districtNum];

			currRepsNum = (votesPerc[i] * numOfRep) / 100;

			curr = RepsInPartyi.getCitizensUntillIndex(currRepsNum);

			res.appendCitizensArr(curr);

		}
		cout << res;
		cout << endl;

		(*_electorsByParty)[partyWin].appendCitizensArr(res);


	}

	void District::printResultElectionInDist(PartiesArr* _partiesArr, CitizensDB* _citizensDB)
	{
		int partyWinID = votesCounter.getWinningPartID();
		long int leaderID = (*_partiesArr)[partyWinID].getLeaderId();
		Citizen leader;
		leader = (*_citizensDB)[leaderID];

		cout << endl;
		cout << "     ***** District " << name << " (united system) *****     " << endl
			<< "the district is giving all the following representative "
			<< numOfRep << "to " << leader.getName() << ":" << endl;
		cout << endl;

	}


	void District::save(ostream& out) const
	{
		//out.write(rcastcc(this), sizeof(*this));
		out.write(rcastcc(&numOfRep), sizeof(numOfRep));
		out.write(rcastcc(&districtNum), sizeof(districtNum));
		out.write(rcastcc(&citizensNum), sizeof(citizensNum));
		out.write(name.c_str(), name.size() + 1);

		votesCounter.save(out);
	}

	void District::load(istream& in)
	{
		/*in.read(rcastc(this), sizeof(*this));*/
		in.read(rcastc(&numOfRep), sizeof(numOfRep));
		in.read(rcastc(&districtNum), sizeof(districtNum));
		in.read(rcastc(&citizensNum), sizeof(citizensNum));
		getline(in, name, '\0');

		votesCounter.load(in);
	}

	ostream& operator<<(ostream& os, const District& district)
	{
		cout << "District Number: " << district.getDistrictNum()
			<< " | Name: " << district.getDistrictName() << " | Number of representative: "
			<< district.getNumOfRep() << " | Number of citizens: " << district.getCitizensNum() << endl;

		return os;
	}
}

