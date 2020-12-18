#pragma once
#include "CitizensDB.h";
#include "Citizen.h";
#include "VotersArr.h"

namespace elections {
	class Party {
	private:
		char* name;
		int nameLen;
		long int id;
		CitizensDB representatives;
		VotersArr voters;

	public:
		// Ctors
		Party();
		Party(char* _name, int _nameLen, long int _id, int numOfDistricts = 0);

		// Dtor
		~Party();

		// Overload "=" operator
		void operator=(const Party&);

		// Setters
		void addRepToParty(Citizen&, int districtNum);
		void addNewDistrictToRepArr(void);
		void addDistrictToVotersArr();
		void addVoteToDistrict(int districtNum);

		// Getters
		char* getPartyName() const;
		void printParty(void) const;
		const int getVotesInDist(int idx);
		CitizensArr* getRepListByPercent(int distIdx, int numOfElected);
		const long int getLeaderId() const;

		// returns true if representative with id repId already exists
		const bool isRepAlreadyExists(long int repId);
	};
}