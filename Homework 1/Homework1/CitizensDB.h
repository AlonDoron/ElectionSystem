#pragma once
#include "CitizensArr.h"

namespace elections {

	struct Results {
		int winnerPartyId;
		int numOfReps;

		bool operator < (Results& other) {
			return (numOfReps > other.numOfReps);
		}
	};

	class CitizensDB {
	private:
		int logSize, phsSize;
		CitizensArr* citizensByDist;

		// Resizing CitizensDB arr and updating logSize, phsSize
		void resize(int newSize);

	public:
		// Ctors
		CitizensDB();
		CitizensDB(int size);

		// Dtor
		~CitizensDB();

		// Overload "=" operator
		void operator=(const CitizensDB&);

		// Setters---------------------------------------
		// allocate 1 citizensArr to array 
		void add();

		// set citizensByDist[disId] = citizensArr
		void add(CitizensArr& citizensArr, int distId);
		// add citizens to citizensArr in index "districtNum"
		void addCitizen(Citizen& citizen, int districtNum);

		// Getters
		const int getLogSize() const;
		CitizensArr& getCitizensArrByIndex(int ind);

		// Print one rep
		void printRep(void) const;
	};
}