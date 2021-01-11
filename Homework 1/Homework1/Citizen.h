#pragma once
#include "District.h"


using namespace std;

#define rcastcc reinterpret_cast<const char*>
#define rcastc reinterpret_cast<char*>

namespace elections {
	class Citizen {
	private:
		string name;
		int year;
		long int id;
		District* district;
		bool voted;

	public:
		// Ctors
		Citizen();
		Citizen(string& _name, long int _id, int _year, District* _district, int currYear);

		// Dtor
		~Citizen();


		// Setters-----------------------------
		const bool setVoted(bool val);
		const bool setId(long int _id);
		const bool setName(string& _name);
		const bool setDistrict(District* _district);
		const bool setYear(int _year);

		// Getters----------------------------
		const bool getVoted() const;
		const int getDistrictNum() const;
		const long int getId(void) const;
		const int getYear(void) const;
		const string& getName() const;

		// Printer operator
		friend ostream& operator<<(ostream& os, const Citizen& citizen);

		//Save and load from BIN file methods.
		void save(ostream& out) const;
		void load(istream& in);
	};
}