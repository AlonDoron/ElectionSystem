#include "FilesHandler.h"

#define rcastcc reinterpret_cast<const char*>
#define rcastc reinterpret_cast<char*>

using namespace std;

namespace elections {
	FilesHandler::FilesHandler(string _fileName) : fileName(_fileName) {}

	void FilesHandler::saveToFile(DistrictsArr& districtsArr, CitizensDB& citizensDB,
		PartiesArr& partiesArr, int electionType)
	{
		ofstream outfile(fileName, ios::binary);

		outfile.write(rcastcc(&electionType), sizeof(electionType));
		districtsArr.save(outfile);
		citizensDB.save(outfile);
		partiesArr.save(outfile);

		outfile.close();
	}

	void FilesHandler::loadFromFile(DistrictsArr& districtsArr, CitizensDB& citizensDB,
		PartiesArr& partiesArr, int& electionType)
	{
		ifstream infile(fileName, ios::binary);

		infile.read(rcastc(&electionType), sizeof(electionType));

		districtsArr.load(infile);
		citizensDB.load(infile);
		partiesArr.load(infile);

		infile.close();
	}
}