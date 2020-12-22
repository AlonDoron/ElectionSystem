#include <iostream>
#include "FilesHandler.h"

#define rcastcc reinterpret_cast<const char*>
#define rcastc reinterpret_cast<char*>

using namespace std;

namespace elections {
	FilesHandler::FilesHandler(char* _fileName, int _fileNameLen)
	{
		fileNameLen = _fileNameLen;
		fileName = new char[fileNameLen + 1];
		memcpy(fileName, _fileName, fileNameLen + 1);
		fileName[fileNameLen] = '\0';
	}

	void FilesHandler::saveToFile(DistrictsArr& districtsArr, CitizensDB& citizensDB, PartiesArr& partiesArr)
	{
		// TODO : SAVE WITH SERIALIZATION

		const int districtsSize = districtsArr.getLogSize();
		District* inDists = new District[districtsSize];

		// First - save all Districts, Then - save all citizens, Then - save all parties.
		ofstream outfile(fileName, ios::binary);
		District* districts = districtsArr.getAllDistricts();

		outfile.write(rcastcc(districts), sizeof(districtsSize));
		outfile.close();

		ifstream infile(fileName, ios::binary);
		infile.read(rcastc(inDists), sizeof(districtsSize));
		infile.close();

		for (int i = 0; i < districtsSize; i++)
			cout << inDists[i];
	}

	void FilesHandler::loadFromFile(DistrictsArr& districtsArr, CitizensDB& citizensDB, PartiesArr& partiesArr)
	{
		// TODO : LOAD WITH SERIALIZATION
	}
}