#pragma once
#include "District.h"
#include "CitizensArr.h"


namespace elections {
	class CitizensArr;

class DividedDistrict : public District {

public:
	DividedDistrict();
	DividedDistrict(string _name, int _numOfRep, int _districtNum);


	virtual void setElected(PartiesArr* _partiesArr, CitizensDB* _electorsByParty, CitizensDB* _citizensDB);

};

}