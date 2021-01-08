#pragma once
#include "Citizen.h"
#include "DynamicArray.h"

#define rcastcc reinterpret_cast<const char*>
#define rcastc reinterpret_cast<char*>

namespace elections {
	class CitizensArr {
	private:
		DynamicArray<Citizen> citizens;

	public:
		// Ctors
		CitizensArr() {}
		CitizensArr(int size);

		// Getters
		int getLogSize();

		//add one citizen to array
		void add(Citizen& citizen);

		// add an entire citizen's array to exisiting array (at the end)
		void appendCitizensArr(CitizensArr& other);

		// return the first "numOfElected" citizens in array
		CitizensArr getCitizensUntillIndex(int numOfElected);

		const bool isCitizenExistsById(long int id) const;

		DynamicArray<Citizen>& getCitizens();

		const Citizen& operator[](int index) const;

		const Citizen& operator[](long int id) const;

		friend ostream& operator<<(ostream& os, CitizensArr& citizensArr);

		//Save and load from BIN file methods.
		void save(ostream& out) const;
		void load(istream& in);
	};
}