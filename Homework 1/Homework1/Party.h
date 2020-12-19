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
		// Array of representatives organazied by district 
		CitizensDB representatives;
		// A voting data of each party
		VotersArr voters;

	public:
		// Ctors
		Party();
		Party(char* _name, int _nameLen, long int _id, int numOfDistricts = 0);

		// Dtor
		~Party();

		// Overload "=" operator
		void operator=(const Party&);

		// Setters---------------------------------------------------
		void addRepToParty(Citizen&, int districtNum);

		// allocating one more space for votersArr/repArr (when district is added)
		void addNewDistrictToRepArr(void);
		void addDistrictToVotersArr();

		// adding when one vote when voting to party (at the relevant dist index)
		void addVoteToDistrict(int districtNum);


		// Getters ----------------------------------------------------
		char* getPartyName() const;
		
		// print all party detailes
		void printParty(void) const; 		
		
		// return the number of votes for party in district "idx"
		const int getVotesInDist(int idx); 
		
		// return the number of reps using percentage (in distIdx)
		CitizensArr* getRepListByPercent(int distIdx, int numOfElected);


		const long int getLeaderId() const;
		


		// returns true if representative with id repId already exists
		const bool isRepAlreadyExists(long int repId);
	};
}