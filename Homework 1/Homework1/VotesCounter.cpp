#include "VotesCounter.h"
#include "CitizensArr.h"
#include "PartiesArr.h"

#define rcastcc reinterpret_cast<const char*>
#define rcastc reinterpret_cast<char*>

namespace elections {
	VotesCounter::VotesCounter() : logSize(0), phsSize(0), votesByParty(nullptr),
		winningPartyID(0), votesPerc(nullptr), votingNumber(0) {}

	VotesCounter::VotesCounter(int size)
		: phsSize(size), logSize(size), winningPartyID(0), votesByParty(nullptr),
		votesPerc(nullptr), votingNumber(0) {
		votesByParty = new int[size];
		votesPerc = new int[size];

		for (int i = 0; i < size; i++)
		{
			votesByParty[i] = 0;
			votesPerc[i] = 0;
		}
	}

	VotesCounter::VotesCounter(const VotesCounter& other)
	{
		*this = other;
	}

	VotesCounter::~VotesCounter()
	{
		delete[] votesByParty;
		delete[] votesPerc;
	}

	void VotesCounter::resize(int newSize)
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
	}

	void VotesCounter::operator=(const VotesCounter& other)
	{
		logSize = other.logSize;
		phsSize = other.phsSize;
		winningPartyID = winningPartyID;
		votingNumber = other.votingNumber;

		votesByParty = new int[phsSize];
		votesPerc = new int[phsSize];

		for (int i = 0; i < logSize; i++)
		{
			votesByParty[i] = other.votesByParty[i];
			votesPerc[i] = other.votesPerc[i];
		}


	}

	void VotesCounter::addEmptyCounter()
	{
		if (logSize == phsSize)
			resize(phsSize * 2 + 1);

		++logSize;
	}

	void VotesCounter::addVote(int partyNum)
	{
		votesByParty[partyNum]++;
		votingNumber++;
	}
	const int VotesCounter::getLogSize() const
	{
		return logSize;
	}
	const int VotesCounter::getPhiSize() const
	{
		return phsSize;
	}

	const int VotesCounter::getWinningPartID()
	{
		return winningPartyID;
	}


	void VotesCounter::updatePercentage()
	{
		for (int i = 0; i < logSize; i++)
			votesPerc[i] = ((float)((float)votesByParty[i] / (float)votingNumber)) * 100;

	}

	void VotesCounter::updateWinner()
	{
		int winningParty = 0;

		for (int i = 1; i < logSize; i++)
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

	int* VotesCounter::getVotesByParty()
	{
		return votesByParty;
	}

	int* VotesCounter::getPercentageVotes()
	{
		return votesPerc;
	}

	void VotesCounter::printVotingStatictic(PartiesArr* partiesArr, int citizensNum)
	{
		cout << "Voting statictics: " << endl;
		for (int i = 0; i < logSize; i++)
		{
			cout << (*partiesArr)[i].getPartyName() << " got " << votesByParty[i] << " votes "
				<< "which are " << votesPerc[i] << "%" << " of all votes" << endl;
		}
		cout << "General turnout in the district is: " <<
			((float)((float)votingNumber / (float)citizensNum)) * 100
			<< "%" << endl
			<< "______________________________________________________________"
			<< endl << endl;

	}

	int& VotesCounter::operator[](int index) const
	{
		return votesByParty[index];
	}

	void VotesCounter::save(ostream& out) const
	{
		if (logSize > 0) {
			out.write(rcastcc(&logSize), sizeof(logSize));
			out.write(rcastcc(votesByParty), sizeof(votesByParty));
			out.write(rcastcc(votesPerc), sizeof(votesPerc));
		}
	}

	void VotesCounter::load(istream& in)
	{
		int newLogSize = 0;
		// We need to reset logSize and phsSize, because we save a whole object, 
		// and when we load data to votesByParty and votesPerc we need resize to work with the new size.
		logSize = 0, phsSize = 0;
		in.read(rcastc(&newLogSize), sizeof(newLogSize));
		if (newLogSize > 0) {
			resize(newLogSize);
			logSize = newLogSize;
			in.read(rcastc(votesByParty), sizeof(votesByParty));
			in.read(rcastc(votesPerc), sizeof(votesPerc));
		}
	}
}
