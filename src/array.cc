#include "purgatory.h"

namespace purgatory {

Purgatory::Purgatory() {};
Purgatory::Purgatory(istream& s) {};
Purgatory::~Purgatory() {};

/*
 *  we are using a two-pointer approach with variables first and second to track
 *  potential increasing subsequence candidates. It lets us break the problem
 *  into three candidates:
 *  - update first to smallest
 *  - update second if it's larger than first
 *  - if a third number is larger than second, we're done
 */
bool Purgatory::increasingTriplet(vector<int>& nums) {
    // initalize: first and second 
    int first = INT_MAX, second = INT_MAX;

    for (int num : nums) {
	// update first
        if (num <= first) first = num;
	// update second
	else if (num <= second) second = num;
	// a < b < c
	else return true;
    }

    return false;
}

}


