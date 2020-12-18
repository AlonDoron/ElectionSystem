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

		// Dtor
		~CitizensArr();

		// Overload "=" operator
		void operator=(const CitizensArr&);

		// Setters
		void add(Citizen& citizen);
		void add_citizenArr(CitizensArr& other);
		bool setLogSize(int size);
		bool setPhsSize(int size);

		// Getters
		Citizen* getCitizen(long int citizenId);
		const int getLogSize() const;
		Citizen& getCitizenByIndex(int ind);
		CitizensArr* getElectReps(int numOfElected);

		// Print all citizens in CitizensArr
		void printCitizens(void);

	};
}