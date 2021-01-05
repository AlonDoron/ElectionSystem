#pragma once
#include "CitizensArr.h"

#define rcastcc reinterpret_cast<const char*>
#define rcastc reinterpret_cast<char*>

namespace elections {
	class CitizensDB {
	private:
		int logSize, phsSize;
		CitizensArr* citizensByDist;

		// Resizing CitizensDB arr and updating logSize, phsSize
		void resize(int newSize);

	public:
		// Ctors
		CitizensDB();
		CitizensDB(int size);
		CitizensDB(const CitizensDB&);

		// Dtor
		~CitizensDB();

		// Overload "=" operator
		CitizensDB& operator=(const CitizensDB&);

		// Setters---------------------------------------
		bool setLogSize(int size);
		bool setPhsSize(int size);

		// allocate 1 citizensArr to array 
		void addEmptyCitizensArr();

		const bool isCitizenExistsById(long int id) const;
		// add citizens to citizensArr in index "districtNum"
		void addCitizenToIndex(Citizen& citizen, int index);

		// Getters
		const int getLogSize() const;
		const int getPhsSize() const;
		CitizensArr& getCitizensArrByIndex(int ind);

		CitizensArr& operator[](int index) const;
		Citizen& operator[](long int id)const;
		
		//Save and load from BIN file methods.
		void save(ostream& out) const;
		void load(istream& in);

		friend ostream& operator<<(ostream& os, const CitizensDB& citizensDB);
	};
}

