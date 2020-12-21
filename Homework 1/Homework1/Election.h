#pragma once
#include "CitizensDB.h"
#include "PartiesArr.h"
#include "DistrictsArr.h"

using namespace std;

namespace elections {
	class Election : public CitizensDB, public PartiesArr {
		struct Date
		{
			int day, month, year;
		};

	protected:
		CitizensDB citizensArr;
		PartiesArr partiesArr;
		Date date;

	public:
		// TODO: Getters, Setters, Ctors, Dtors, CopyCtors, operator=, operator<<

	};

	class RegularElection : public Election {
	private:
		DistrictsArr districtArr;

	public:

	};

	class SimpleElection : public Election {
	private:
		District district;


	public:
		SimpleElection(District& _district) {
			district = _district;
		}

		District getDistrict(void) { return district; };
	};
}