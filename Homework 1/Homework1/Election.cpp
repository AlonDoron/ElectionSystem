#include "Election.h"

namespace elections {


	void RegularElection::displayResults()
	{
		//districtsArr.getElectedRepsFromAllDistricts(electorsByDistrict);

		getElectedRepsFromAllDistricts();

	}

	void RegularElection::getElectedRepsFromAllDistricts()
	{
		int distNum = districtsArr.getLogSize();
		District* currDist;
		CitizensArr curr;

		for (int i = 0; i < distNum; i++)
		{
			currDist = &districtsArr[i];
				
			curr = currDist->getElctedReps(&partiesArr);

			cout << curr<<endl;

			electorsByDistrict[i] = curr;
		}

	}

}
