#pragma once
#pragma once
#include "Citizen.h"

namespace elections {
	class CitizensArr {
	private:
		int logSize, phsSize;
		Citizen* citizens;

		// Resizing citizens arr and updating logSize, phsSize
		void resize(int size);

	public:
		// Ctors
		CitizensArr();
		CitizensArr(int size);
		CitizensArr(const CitizensArr&);

		// Dtor
		~CitizensArr();

		// Overload "=" operator
		void operator=(const CitizensArr&);

		// Setters----------------------------------
		bool setLogSize(int size);
		bool setPhsSize(int size);

		//add one citizen to array
		void add(Citizen& citizen);

		// add an entire citizen's array to exisiting array (at the end)
		void appendCitizensArr(CitizensArr& other);

		// Getters--------------------------------------
		const int getLogSize() const;
		const int getPhsSize() const;

		// return the first "numOfElected" citizens in array
		CitizensArr getCitizensUntillIndex(int numOfElected);

		const bool isCitizenExistsById(long int id) const;
		// return citizen using index
		Citizen& getCitizenByIndex(int ind);

		// Print all citizens in CitizensArr
		void printCitizens(void);

		Citizen& operator[](int index) const;

		Citizen& operator[](long int id) const;

		friend ostream& operator<<(ostream& os, const CitizensArr& citizensArr);
	};
}