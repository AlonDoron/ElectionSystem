#pragma once
#include "CitizensArr.h"

#define rcastcc reinterpret_cast<const char*>
#define rcastc reinterpret_cast<char*>

namespace elections {
	class CitizensDB {
	private:
		vector<CitizensArr> citizensByDist;
	public:

		CitizensDB();
		CitizensDB(int size);

		void addEmptyCitizensArr();
		const int getLogSize() const;
		const bool isCitizenExistsById(long int id) const;
		void addCitizenToIndex(Citizen& citizen, int index);

		CitizensArr& operator[](int index);
		Citizen& operator[](long int id);
		
		//Save and load from BIN file methods.
		void save(ostream& out) const;
		void load(istream& in);

		friend ostream& operator<<(ostream& os, CitizensDB& citizensDB);
	};
}

