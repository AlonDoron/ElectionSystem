#pragma once

namespace elections {
	class VotersArr {
	private:
		int logSize = 0, phsSize = 0;
		int* votersByDistrict;

		// Resizing votersByDistrict arr and updating logSize, phsSize
		void resize(int newSize);

	public:
		// Ctors
		VotersArr();
		VotersArr(int size);

		// Dtor
		~VotersArr();
		
		// Overload "=" operator
		void operator=(const VotersArr&);

		// Setters----------------------------------------
		// allocating one more space when district is added
		void addDistrict();

		// add one vote to in index "districtNum"
		void addVote(int districtNum);

		// Getters------------------------------------------
		// return the number of votes in district "idx"
		const int getVotesByIndex(int idx) const;
	};
}