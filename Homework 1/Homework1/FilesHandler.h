#pragma once
#include <fstream>
#include "DistrictsArr.h"
#include "CitizensDB.h"
#include "PartiesArr.h"

namespace elections {
	class FilesHandler {
	private:
		char* fileName;
		int fileNameLen;

	public:
		FilesHandler(char* _fileName, int _fileNameLen);
		void saveToFile(DistrictsArr& districtsArr, CitizensDB& citizensDB,
			PartiesArr& partiesArr, int electionType);
		void loadFromFile(DistrictsArr& districtsArr, CitizensDB& citizensDB,
			PartiesArr& partiesArr, int& electionType);
	};
}