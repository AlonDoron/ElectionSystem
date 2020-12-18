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

		// Setters
		void addDistrict();
		void addVote(int districtNum);

		// Getters
		const int getVotesByIndex(int idx) const;
	};
}