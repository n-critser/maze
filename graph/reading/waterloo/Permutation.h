#ifndef CA_UWATERLOO_ALUMNI_DWHARDER_PERMUTATION
#define CA_UWATERLOO_ALUMNI_DWHARDER_PERMUTATION

#include <cassert>
#include <cstdlib>
// Author:  Douglas Wilhelm Harder
// Copyright (c) 2009 by Douglas Wilhelm Harder.  All rights reserved.

namespace Data_structures {
	class Permutation {
		private:
			int capacity;
			int *bound;
			int *array;

		public:
			Permutation( int );
			~Permutation();
			int next();
			void reset();
	};

	Permutation::Permutation( int n ):
	capacity( n ),
	bound( new int( capacity ) ),
	array( new int[capacity] ) {
		for ( int i = 0; i < capacity; ++i ) {
			array[i] = i;
		}
	}

	Permutation::~Permutation() {
		delete bound;
		delete [] array;
	}

	int Permutation::next() {
		if ( *bound == 0 ) {
			return 0;
		}

		int index = rand() % *bound;
		int result = array[index];

		--*bound;
		array[index] = array[*bound];

		return result;
	}

	void Permutation::reset() {
		for ( int i = 0; i < capacity; ++i ) {
			array[i] = i;
		}

		*bound = capacity;
	}
}

#endif
