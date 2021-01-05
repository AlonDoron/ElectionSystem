#pragma once
#include "CitizensDB.h";
#include "Citizen.h";

namespace elections {
	class Party {
	private:
		string name;
		long int id;
		// Array of representatives organazied by district 
		CitizensDB representatives;

	public:
		// Ctors
		Party();
		Party(string& _name, long int _id, int numOfDistricts = 0);
		Party(const Party&);

		// Dtor
		~Party();

		// Overload "=" operator
		Party& operator=(const Party&);

		// Setters---------------------------------------------------
		void addRepToParty(Citizen&, int districtNum);

		// allocating one more space for votersArr/repArr (when district is added)
		void addEmptyCellToRepArr(void);

		// Getters ----------------------------------------------------
		const string& getPartyName() const;
		const long int getLeaderId() const;
		const CitizensDB& getRepresentatives() const;

		// print all party detailes
		friend ostream& operator<<(ostream& os, const Party& party);

		// returns true if representative with id repId already exists
		const bool isRepAlreadyExists(long int repId);

		//Save and load from BIN file methods.
		void save(ostream& out) const;
		void load(istream& in);
	};
}