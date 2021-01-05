#pragma once
#include <fstream>
#include "DistrictsArr.h"
#include "CitizensDB.h"
#include "PartiesArr.h"

namespace elections {
	class FilesHandler {
	private:
		string fileName;

	public:
		// Ctor that gets a file name and file name length and constructs a FilesHandler object.
		FilesHandler(string _fileName);

		// This function gets districtsArr, citizensDB and partiesArr and electionType,
		// and saves it's data to bin file.
		void saveToFile(DistrictsArr& districtsArr, CitizensDB& citizensDB,
			PartiesArr& partiesArr, int electionType);

		// This function gets districtsArr, citizensDB and partiesArr and electionType,
		// and loading data into them from bin file.
		void loadFromFile(DistrictsArr& districtsArr, CitizensDB& citizensDB,
			PartiesArr& partiesArr, int& electionType);
	};
}