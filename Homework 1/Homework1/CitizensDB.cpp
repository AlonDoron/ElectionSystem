#include <iostream>
#include "CitizensDB.h"

using namespace std;

namespace elections {
	CitizensDB::CitizensDB() {}

	CitizensDB::CitizensDB(int size) : citizensByDist(size) {}

	void CitizensDB::addEmptyCitizensArr()
	{
		int newSize = citizensByDist.size() + 1;

		citizensByDist.resize(newSize);
	}

	void CitizensDB::addCitizenToIndex(Citizen& citizen, int index)
	{
		citizensByDist[index].add(citizen);
	}

	void CitizensDB::save(ostream& out) const
	{
		int size = citizensByDist.size();

		out.write(rcastcc(&size), sizeof(size));

		for (int i = 0; i < size; i++)
			citizensByDist[i].save(out);
	}

	void CitizensDB::load(istream& in)
	{
		int newLogSize;
		in.read(rcastc(&newLogSize), sizeof(newLogSize));

		for (int i = 0; i < newLogSize; i++)
		{
			CitizensArr temp;
			temp.load(in);

			addEmptyCitizensArr();
			citizensByDist[i] = temp;
		}
	}

	void CitizensDB::isCitizenExistsById(long int id) const {

		for (int i = 0; i < citizensByDist.size(); i++)
			if (citizensByDist[i].isCitizenExistsById(id))
				throw ("The citizen with this ID already exists!!");
	}

	CitizensArr& CitizensDB::operator[](int index)
	{
		return citizensByDist[index];
	}

	const Citizen& CitizensDB::operator[](long int id)
	{
		for (int i = 0; i < citizensByDist.max_size(); i++)
			if (citizensByDist[i].isCitizenExistsById(id))
				return (citizensByDist[i])[id];
	}

	const int CitizensDB::getLogSize() const { return citizensByDist.size(); }

	ostream& operator<<(ostream& os, CitizensDB& citizensDB)
	{
		for (int i = 0; i < citizensDB.getLogSize(); i++)
		{
			cout << citizensDB[i];
			cout << endl;
		}

		return os;
	}
}
