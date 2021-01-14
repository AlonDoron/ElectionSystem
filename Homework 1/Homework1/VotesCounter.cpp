#include "VotesCounter.h"
#include "CitizensArr.h"
#include "PartiesArr.h"

#define rcastcc reinterpret_cast<const char*>
#define rcastc reinterpret_cast<char*>

namespace elections {
	VotesCounter::VotesCounter() : votesByParty(),
		winningPartyID(0), votesPerc(), votingNumber(0) {}

	VotesCounter::VotesCounter(int size)
		: winningPartyID(0), votesByParty(size),
		votesPerc(size), votingNumber(0) {

		fill(votesByParty.begin(), votesByParty.end(), 0);
		fill(votesPerc.begin(), votesPerc.end(), 0);

	}

	VotesCounter::VotesCounter(const VotesCounter& other)
	{
		*this = other;
	}

	VotesCounter::~VotesCounter() {}

	/*void VotesCounter::resize(int newSize)
	{
		int* tempVotesByParty = new int[newSize];
		int* tempVotesPerc = new int[newSize];

		for (int i = 0; i < newSize; ++i)
		{
			tempVotesByParty[i] = 0;
			tempVotesPerc[i] = 0;
		}

		for (int i = 0; i < logSize; ++i)
		{
			tempVotesByParty[i] = votesByParty[i];
			tempVotesPerc[i] = votesPerc[i];

		}

		if (logSize >= 1)
		{
			delete[] votesByParty;
			delete[] votesPerc;

		}

		votesByParty = tempVotesByParty;
		votesPerc = tempVotesPerc;
		phsSize = newSize;
	}*/

	VotesCounter& VotesCounter::operator=(const VotesCounter& other)
	{

		winningPartyID = winningPartyID;
		votingNumber = other.votingNumber;

		votesByParty = other.votesByParty;
		votesPerc = other.votesPerc;

		return *this;
	}

	void VotesCounter::addEmptyCounter()
	{
		int currSize = votesByParty.size();

		votesByParty.resize(currSize + 1);

		votesPerc.resize(currSize + 1);
	}

	void VotesCounter::addVote(int partyNum)
	{
		votesByParty[partyNum]++;
		votingNumber++;
	}

	const int VotesCounter::getWinningPartID()
	{
		return winningPartyID;
	}


	void VotesCounter::updatePercentage()
	{
		for (int i = 0; i < votesPerc.size(); i++)
			votesPerc[i] = ((float)((float)votesByParty[i] / (float)votingNumber)) * 100;

	}

	void VotesCounter::updateWinner()
	{
		int winningParty = 0;

		for (int i = 1; i < votesByParty.size(); i++)
		{
			if (votesByParty[i] > votesByParty[winningParty])
				winningParty = i;
		}

		winningPartyID = winningParty;
	}

	const int VotesCounter::getVotingNumberInDistrict() const
	{
		return votingNumber;
	}

	vector <int> VotesCounter::getVotesByParty()
	{
		return votesByParty;
	}

	vector <int> VotesCounter::getPercentageVotes()
	{
		return votesPerc;
	}

	void VotesCounter::printVotingStatictic(PartiesArr* partiesArr, int citizensNum)
	{
		cout << "Voting statictics: " << endl;
		for (int i = 0; i < partiesArr->getLogSize(); i++)
		{
			if (votesByParty.size() > i)
				cout << (*partiesArr)[i].getPartyName() << " got " << votesByParty[i] << " votes "
				<< "which are " << votesPerc[i] << "%" << " of all votes" << endl;
			else
				cout << (*partiesArr)[i].getPartyName() << " got " << 0 << " votes "
				<< "which are " << 0 << "%" << " of all votes" << endl;
		}
		if (votesByParty.size() > 0)
			cout << "General turnout in the district is: " <<
			((float)((float)votingNumber / (float)citizensNum)) * 100
			<< "%" << endl
			<< "______________________________________________________________"
			<< endl << endl;
		else
			cout << "General turnout in the district is: " <<
			"0%" << endl
			<< "______________________________________________________________"
			<< endl << endl;

	}

	const int VotesCounter::operator[](int index) const
	{
		if (votesByParty.size() == 0)
			return 0;
		else
			return votesByParty[index];
	}

	void VotesCounter::save(ostream& out) const
	{
		int size = votesByParty.size();

		if (votesByParty.size() > 0) {
			out.write(rcastcc(&size), sizeof(int));
			out.write(rcastcc(&votesByParty[0]), votesByParty.size() * sizeof(int));
			out.write(rcastcc(&votesPerc[0]), votesPerc.size() * sizeof(int));
		}
	}

	void VotesCounter::load(istream& in)
	{
		// We need to reset logSize and phsSize, because we save a whole object, 
		// and when we load data to votesByParty and votesPerc we need resize to work with the new size.
		int size;
		in.read(rcastc(&size), sizeof(size));

		if (size > 0) {
			votesByParty.resize(size);
			votesPerc.resize(size);

			in.read(rcastc(&votesByParty[0]), size * sizeof(int));
			in.read(rcastc(&votesPerc[0]), size * sizeof(int));
		}
	}
}
