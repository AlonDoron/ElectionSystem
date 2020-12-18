#include <iostream>


class VotersArr {
private:
	int logSize = 0;
	int phsSize = 0;
	int* votersByDistrict;

	void resize(int newSize);

public:
	void add();
	void addRep(Citizen& rep, int districtNum);
	void printRep(void) const;
};


void VotersArr::resize(int newSize)
{
	CitizensArr* temp = new CitizensArr[newSize];

	for (int i = 0; i < logSize; ++i)
		temp[i] = representatives[i];

	if (logSize >= 1)
		delete[] representatives;

	representatives = temp;
	phsSize = newSize;
}

void VotersArr::add()
{
	CitizensArr newCitizensArr;

	if (logSize == phsSize)
		resize(phsSize * 2 + 1);

	representatives[logSize] = newCitizensArr;
	++logSize;
}

void VotersArr::addRep(Citizen& rep, int districtNum)
{
	representatives[districtNum].add(rep);
}

void VotersArr::printRep(void) const
{
	for (int i = 0; i < logSize; i++)
	{
		representatives[i].printCitizens();
	}
}