#include "VotesCounter.h"
#include "CitizensArr.h"

#define rcastcc reinterpret_cast<const char*>
#define rcastc reinterpret_cast<char*>

namespace elections {
	VotesCounter::VotesCounter() : logSize(0), phsSize(0), votesByParty(nullptr),
		winningPartyID(0), electedReps(nullptr), votesPerc(nullptr), votingNumber(0) {}

	VotesCounter::VotesCounter(int size)
		: phsSize(size), logSize(size), winningPartyID(0), electedReps(nullptr), votesByParty(nullptr),
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
		delete electedReps;
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

		if (electedReps != nullptr)
		{
			electedReps = new CitizensArr[other.electedReps->getLogSize()];
			*electedReps = *(other.electedReps);
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

	const CitizensArr* VotesCounter::getElectedReps() const
	{
		return electedReps;
	}

	void VotesCounter::updatePercentage()
	{
		for (int i = 0; i < logSize; i++)
			votesPerc[i] = ((float)((float)votesByParty[i] / (float)votingNumber)) * 100;

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

	int& VotesCounter::operator[](int index) const
	{
		return votesByParty[index];
	}

	void VotesCounter::save(ostream& out) const
	{
		out.write(rcastcc(&logSize), sizeof(logSize));
		out.write(rcastcc(&phsSize), sizeof(phsSize));
		out.write(rcastcc(votesByParty), sizeof(logSize));
	}

	void VotesCounter::load(istream& in)
	{
		in.read(rcastc(&logSize), sizeof(logSize));
		in.read(rcastc(&phsSize), sizeof(phsSize));
		in.read(rcastc(votesByParty), sizeof(votesByParty));
	}
}
