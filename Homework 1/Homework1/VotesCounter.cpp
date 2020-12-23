#include "VotesCounter.h"

#define rcastcc reinterpret_cast<const char*>
#define rcastc reinterpret_cast<char*>

namespace elections {
	VotesCounter::VotesCounter() : logSize(0), phsSize(0), votesByParty(nullptr) {}

	VotesCounter::VotesCounter(int size)
		: phsSize(size), logSize(size) {
		votesByParty = new int[size];

		for (int i = 0; i < size; i++)
			votesByParty[i] = 0;
	}

	VotesCounter::VotesCounter(const VotesCounter& other)
	{
		*this = other;
	}

	VotesCounter::~VotesCounter()
	{
		delete[] votesByParty;
	}

	void VotesCounter::resize(int newSize)
	{
		int* temp = new int[newSize];

		for (int i = 0; i < newSize; ++i)
			temp[i] = 0;

		for (int i = 0; i < logSize; ++i)
			temp[i] = votesByParty[i];

		if (logSize >= 1)
			delete[] votesByParty;

		votesByParty = temp;
		phsSize = newSize;
	}

	void VotesCounter::operator=(const VotesCounter& other)
	{
		logSize = other.logSize;
		phsSize = other.phsSize;

		if (votesByParty)
			delete[] votesByParty;

		votesByParty = new int[phsSize];

		for (int i = 0; i < logSize; i++)
			votesByParty[i] = other.votesByParty[i];
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
	}
	const int VotesCounter::getLogSize() const
	{
		return logSize;
	}
	const int VotesCounter::getPhiSize() const
	{
		return phsSize;
	}

	int& VotesCounter::operator[](int index) const
	{
		return votesByParty[index];
	}

	const int VotesCounter::getVotesByIndex(int idx) const
	{
		return votesByParty[idx];
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
