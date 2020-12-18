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

		// Setters
		void add();
		void add(CitizensArr& citizensArr, int distId);
		void addRep(Citizen& rep, int districtNum);

		// Getters
		const int getLogSize() const;
		CitizensArr& getCitizensArrByIndex(int ind);

		// Print one rep
		void printRep(void) const;
	};
}