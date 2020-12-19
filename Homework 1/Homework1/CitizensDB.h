#pragma once
#include "CitizensArr.h"

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
		void operator=(const CitizensDB&);

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

		// Print one rep
		void printRep(void) const;

		CitizensArr& operator[](int index) const;
		CitizensArr& operator[](long int id) const;

		friend ostream& operator<<(ostream& os, const CitizensDB& citizensDB);
	};
}