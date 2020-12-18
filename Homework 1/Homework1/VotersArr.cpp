#include "VotersArr.h"

namespace elections {
	VotersArr::VotersArr() : votersByDistrict(nullptr) {}

	VotersArr::VotersArr(int size)
		: phsSize(size), logSize(size) {
		votersByDistrict = new int[size];

		for (int i = 0; i < size; i++)
			votersByDistrict[i] = 0;
	}

	VotersArr::~VotersArr()
	{
		delete[] votersByDistrict;
	}

	void VotersArr::resize(int newSize)
	{
		int* temp = new int[newSize];

		for (int i = 0; i < newSize; ++i)
			temp[i] = 0;

		for (int i = 0; i < logSize; ++i)
			temp[i] = votersByDistrict[i];

		if (logSize >= 1)
			delete[] votersByDistrict;

		votersByDistrict = temp;
		phsSize = newSize;
	}

	void VotersArr::operator=(const VotersArr& other)
	{
		logSize = other.logSize;
		phsSize = other.phsSize;
		votersByDistrict = new int[phsSize];

		for (int i = 0; i < logSize; i++)
			votersByDistrict[i] = other.votersByDistrict[i];
	}

	void VotersArr::addDistrict()
	{
		if (logSize == phsSize)
			resize(phsSize * 2 + 1);

		++logSize;
	}

	void VotersArr::addVote(int districtNum)
	{
		votersByDistrict[districtNum]++;
	}
	const int VotersArr::getVotesByIndex(int idx) const
	{
		return votersByDistrict[idx];
	}
}
