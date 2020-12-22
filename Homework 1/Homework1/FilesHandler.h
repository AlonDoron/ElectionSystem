#pragma once
#include <fstream>
#include "DistrictsArr.h"
#include "CitizensDB.h"
#include "partiesArr.h"

namespace elections {
	class FilesHandler {
	private:
		char* fileName;
		int fileNameLen;

	public:
		FilesHandler(char* _fileName, int _fileNameLen);
		void saveToFile(DistrictsArr& districtsArr, CitizensDB& citizensDB, PartiesArr& partiesArr);
		void loadFromFile(DistrictsArr& districtsArr, CitizensDB& citizensDB, PartiesArr& partiesArr);
	};
}