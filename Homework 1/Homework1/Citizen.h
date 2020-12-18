#pragma once
#include "District.h"

namespace elections {
	class Citizen {
	private:
		char* name;
		int nameLen, year;
		long int id;
		District* district;
		bool voted;

	public:
		// Ctors
		Citizen();
		Citizen(char* _name, int _nameLen, long int _id, int _year, District* _district);

		// Dtor
		~Citizen();

		// Overload "=" operator
		void operator=(const Citizen&);

		// Setters
		const bool setVoted(bool val);

		// Getters
		const bool getVoted() const;
		const int getDistrictNum() const;
		const long int getId(void) const;
		char* getName();

		// Print one citizen
		void printCitizen(void);
	};
}