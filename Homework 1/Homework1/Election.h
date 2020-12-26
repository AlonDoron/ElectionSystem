#pragma once
#include "CitizensDB.h"
#include "PartiesArr.h"
#include "DistrictsArr.h"

using namespace std;

namespace elections {
	
	struct Date {int day, month, year;};

	class Election {
	protected:	

		DistrictsArr districtsArr;
		CitizensDB citizensDB;
		PartiesArr partiesArr;
		CitizensDB electorsByDistrict;
		Date date;
	public:
		Election() {}
		Election(Date& _date, DistrictsArr& _districtsArr, PartiesArr& _partiesArr, CitizensDB& _citizensDB) :
			date(_date), districtsArr(_districtsArr), partiesArr(_partiesArr), citizensDB(_citizensDB)
			, electorsByDistrict(_districtsArr.getLogSize()) {}

		virtual void displayResults() = 0;
		~Election() {}
	};

	class RegularElection : public Election {
	private:

	public:
		RegularElection(Date& _date, DistrictsArr& _districtsArr, PartiesArr& _partiesArr, CitizensDB& _citizensDB)
			: Election(_date, _districtsArr, _partiesArr, _citizensDB)	{}

		virtual void displayResults();
		void getElectedRepsFromAllDistricts();
		~RegularElection();

	};


	class SimpleElection : public Election {
	private:

	public:
		SimpleElection(Date& _date, DistrictsArr& _districtsArr, PartiesArr& _partiesArr, CitizensDB& _citizensDB)
			: Election(_date, _districtsArr, _partiesArr, _citizensDB) {}

		virtual void displayResults() {};
		~SimpleElection();

	};




}