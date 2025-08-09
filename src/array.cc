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

/*
 *  using reverse two-pointer merge here because we can break the problem into
 *  - comparing elements from the back
 *  - inserting in-place from the end of nums1
 *  - only copying remaining nums2 if needed
 */
void Purgatory::merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
    int p1 = m - 1, p2 = n - 1, p = m + n - 1;

    while ( p1 >= 0 && p2 >= 0 ) {
        if (nums1[p1] > nums2[p2]) {
	    nums1[p] = nums1[p1];
	    --p1;
	} else {
	    nums1[p] = nums2[p2];
	    --p2;
	}
	--p;
    }

    while ( p2 >= 0 ) {
        nums1[p] = nums2[p2];
	--p;--p2;
    }
}

/*
 *  using two pointer technique here because we can break the problem into
 *  1. one pointer to read each element, read
 *  2. one pointer to write valid entries, write
 */
int Purgatory::removeDuplicates(vector<int>& nums) {
    if (nums.size() < 2) return nums.size();

    int write = 2;

    for (int read = 2; read < nums.size(); ++read) {
        if (nums[read] != nums[write - 2]) {
	    nums[write] = nums[read];
	    ++write;
	}
    }

    return write;
}

/*
 *  using reverse-in-place trick here because we can break the problem into 
 *  - reverse full array
 *  - reverse prefix
 *  - reverse suffix
 */
void Purgatory::rotate(vector<int> & nums, int k) {
    int n = nums.size();

    k = k % n;

    reverse(nums.begin(), nums.end());
    reverse(nums.begin(), nums.begin() + k);
    reverse(nums.begin() + k, nums.end());
}

int Purgatory::candy(vector<int>& ratings) {

    int n = ratings.size();

    vector<int> candies(n, 1);

    for (int i = 1; i < n; ++i) {
        if (ratings[i] > ratings[i - 1]) {
	    candies[i] = candies[i - 1] + 1;
	}
    }

    for (int i = n - 2; i >= 0; --i) {
        if (ratings[i] > ratings[i + 1]) {
	    candies[i] = max(candies[i], candies[i + 1] + 1);
	}
    }

    int total = 0;

    for(auto c : candies) {
        total += c;
    }

    return total;
}

/*
 *  using two pointers here because it helps us process the array in-place without needing extra memory.
 */
int Purgatory::removeElemet(vector<int>& nums, int val) {
    int write = 0;

    for (int read = 0; read < nums.size(); ++read) {
        if ( nums[read] != val ) {
	    nums[write] = nums[read];
	    ++write;
	}
    }

    return write;

}

/*
 *  using a greedy strategy here because each step we only care about the farthest we can reach from all previous positions
 */
bool Purgatory::canJump(vector<int>& nums) {
    int maxReach = 0;

    for ( int i = 0; i < nums.size(); ++i ) {
        if ( i > maxReach ) return false;
    
	maxReach = max(maxReach, i + nums[i]);
    }

    return true;
}

/*
 *  using two-pass scan strategy
 */
vector<int> Purgatory::productExceptSelf(vector<int>& nums) {
    int n = nums.size();
    vector<int> answer(n, 1);

    for ( int i = 1; i < n; ++i ) {
        answer[i] = answer[i - 1] * nums[i - 1];
    }

    int right = 1;
    for ( int i = n - 1; i >=0 ; --i ) {
        answer[i] *= right;
	right *= nums[i];
    }

    return answer;
}

/*
 *  using greedy approach + space counting here because we can break the problem into lines one by one
 */
vector<string> Purgatory::fullJustify(vector<string>& words, int maxWidth) {
    
    vector<string> result;
    int i = 0, n = words.size();

    while ( i < n ) {
        int lineLen = words[i].length();
	int j = i + 1;

	while ( j < n && (lineLen + 1 + words[j].length() <= maxWidth) ) {
	    lineLen += 1 + words[j].length();
	    ++j;
	}

        int wordCount = j - i;
	int totalSpace = maxWidth - (lineLen - (wordCount - 1));

	string line;
        
	if ( j == n || wordCount == 1) {
            for (int k = i; k < j; ++k) {
	        line += words[k];

		if (k < j - 1) line += " ";
	    }

	    line += string(maxWidth - line.size(), ' ');
	} else {
	    int spaceBetween = totalSpace / (wordCount - 1);
	    int extraSpace = totalSpace % (wordCount - 1);

	    for (int k = i; k < j; ++k) {
		line += words[k];
		
		if (k < j - 1) {
	            int spaces = spaceBetween + (extraSpace-- > 0 ? 1 : 0);
		    line += string(spaces, ' ');
		}
	    }
	
	}

        result.push_back(line);
	i = j;

    }

    return result;
}

}
