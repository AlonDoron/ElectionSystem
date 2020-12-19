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

		// Setters----------------------------------
		//add one citizen to array
		void add(Citizen& citizen);

		// add an entire citizen's array to exisiting array (at the end)
		void add_citizenArr(CitizensArr& other);
		bool setLogSize(int size);
		bool setPhsSize(int size);

		// Getters--------------------------------------
		// return citizen using ID
		Citizen* getCitizen(long int citizenId);
		const int getLogSize() const;

		// return citizen using index
		Citizen& getCitizenByIndex(int ind);

		// return the first "numOfElected" citizens in array
		CitizensArr* getElectReps(int numOfElected);

		// Print all citizens in CitizensArr
		void printCitizens(void);

	};
}