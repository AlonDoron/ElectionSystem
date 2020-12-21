#pragma once
#include "CitizensDB.h"
#include "PartiesArr.h"
#include "DistrictsArr.h"

using namespace std;

namespace elections {
	class SimpleElection {
		struct Date {int day, month, year;};
	private:	
		DistrictsArr districtsArr;
		CitizensDB citizensArr;
		PartiesArr partiesArr;
		Date date;

	public:
		SimpleElection() {	}
		SimpleElection(Date _date) {	
			date.day = _date.day;
			date.month = _date.month;
			date.year = _date.year;
		}

		void addDistrict(District& district);
	};

	class RegElection : public SimpleElection {
	public:
		// TODO: Getters, Setters, Ctors, Dtors, CopyCtors, operator=, operator<<

	};


	






	void SimpleElection::addDistrict(District& district)
	{
		districtsArr.add(district);
	}




}