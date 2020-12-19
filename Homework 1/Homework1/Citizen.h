#pragma once
#include "District.h"

using namespace std;

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
		Citizen(const Citizen&);

		// Dtor
		~Citizen();

		// Overload "=" operator
		void operator=(const Citizen&);

		// Setters-----------------------------
		const bool setVoted(bool val);
		const bool setId(long int _id);
		const bool setName(char* _name, int _nameLen);
		const bool setDistrict(District* _district);
		const bool setYear(int _year);

		// Getters----------------------------
		const bool getVoted() const;
		const int getDistrictNum() const;
		const long int getId(void) const;
		const int getYear(void) const;
		const char* getName() const;

		// Print one citizen
		void printCitizen(void);

		friend ostream& operator<<(ostream& os, const Citizen& citizen);
	};
}