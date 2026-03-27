#include "purgatory.h"

namespace purgatory {

/*
 *  using two-pointer method here becuase
 *  - we can skip non-alphanumeric characters in-place without building a new filtered string
 *  - this reduce extra memory usage to O(1)
 *  T: O(n), S: O(1)
 */

// function call & branch prediction
inline bool isAlnum(char c) {
    return (c >= 'a' && c <= 'z') ||
	   (c >= 'A' && c <= 'Z') ||
	   (c >= '0' && c <= '9');
}

inline char toLower(char c) {
    return (c >= 'A' && c <= 'Z') ? c + 32 : c;
}

bool Purgatory::isPalindrome(string s) {
    int left = 0, right = s.size() - 1;

    while (left < right) {
	// register vs memory
        while (left < right) {
	    char l = s[left];
	    if (isAlnum(l))
	        break;
	    ++left;
	}

	while (left < right) {
	    char r = s[right];
	    if (isAlnum(r))
	        break;
	    right--;
	}

	// register vs memory
	char l = toLower(s[left]), r = toLower(s[right]);

	if (l != r) return false;

	left++; right--;
    }

    return true;
}

/*
 *  using two pointers here because the input is sorted
 *  T: O(n), S: O(n)
 */
vector<int> Purgatory::twoSum(vector<int>& numbers, int target) {
    // register vs memory
    int n = numbers.size();
    unordered_map<int, int> seen;
    // cache behavior
    seen.reserve(n);

    for (int i = 0; i < n; ++i) {
	// register vs memory
	int num = numbers[i];
        int complement = target - num;

	// branch prediction
	auto it = seen.find(complement);
	if (it != seen.end()) {
	    return {it->second, i};
	}

	seen[num] = i;
    }
    
    return {};
}

/*
 *  using two pointers here because we can break the problme into repeatedly eliminating impossible pairs. We always move the pointer at the shorter height inward because that's the only way to potentially increase area.
 *  T: O(n), S: O(1)
 */
int Purgatory::maxArea(vector<int> &height) {
    int left = 0, right = height.size() - 1;
    int maxWater = 0;

    while (left < right) {
	// register vs memory
	int hl = height[left];
	int hr = height[right];

	int width = right - left;
	int area = (hl < hr ? hl : hr) * width;
        
	// function call
	if (area > maxWater) maxWater = area;

	// branch prediction
	if (hl < hr)
	    ++left;
        else
	    --right;
    }

    return maxWater;
}

/*
 *  using two pointers here becuase we can break the problem into continuously shrinking the search space from both ends, while keeping track of the max heights seen so far.
 *  T: O(n), S: O(1)
 */
int Purgatory::trap(vector<int> & height) {
    int left = 0, right = height.size() - 1;
    int leftMax = 0, rightMax = 0;
    int water = 0;

    while (left < right) {
	// register vs memory
        int hl = height[left], hr = height[right];
        if (hl < hr) {
	    // function call
	    if (hl > leftMax)
	        leftMax = hl;

            water += leftMax - hl;
	    left++;
	} else {
	    if (hr > rightMax)
	        rightMax = hr;

	    water += rightMax - hr;
	    right--;
	}
    }

    return water;
}

/*
 *  using symmetry-based in-place here because we can break the problem into pairwise swapping from both ends
 *  T: O(n), S: O(1)
 */
void Purgatory::reverseString(vector<char>& s) {
    // register vs memory
    char *l = &s[0];
    char *r = &s[s.size() - 1];

    // cache behavior
    while (l < r) {
	char temp = *l;
	*l++ = *r;
	*r-- = temp;
    }
}

/*
 * using the dutch national flag algorithm here because we can break the problem into three regions
 * T: O(n), S: O(1)
 */
void Purgatory::sortColors(vector<int>& nums) {
    int low = 0, mid = 0;
    int high = nums.size() - 1;

    while (mid <= high) {
        if (nums[mid] == 0) {
            swap(nums[low], nums[mid]);
	    low++; mid++;
	} else if (nums[mid] == 1) {
            mid++;
	} else {
	    swap(nums[mid], nums[high]);
	    high--;
	}
    }
}

/*
 *  using two-pointer parsing method here because we can break the problem into small numeric segments without splitting strings
 *  T: O(n + m), S: O(1)
 */
int Purgatory::compareVersion(string version1, string version2) {
    int i = 0, j = 0;
    int n = version1.size(), m = version2.size();

    while (i < n || j < m) {
        long num1 = 0, num2 = 0;

	while (i < n && version1[i] != '.') {
            num1 = num1*10 + (version1[i] - '0');
	    i++;
	}

	while (j < m && version2[j] != '.') {
             num2 = num2*10 + (version2[j] - '0');
	     j++;
	}


	if (num1 > num2) return 1;
	if (num1 < num2) return -1;

	i++; j++;
    }

    return 0;
}

vector<int> maxSubsequence(vector<int>& nums, int k) {
    vector<int> st;

    int drop = nums.size() - k;

    for (int num : nums) {
        while (!st.empty() && drop > 0 && st.back() < num) {
            st.pop_back();
	    drop--;
	}

	st.push_back(num);
    } 

    st.resize(k);
    return st;
}

vector<int> mergeMaxNumber(vector<int>& a, vector<int>& b) {
    vector<int> result;

    while (!a.empty() || !b.empty()) {
        if ( a > b) {
            result.push_back(a.front());
	    a.erase(a.begin());
	} else {
            result.push_back(b.front());
	    b.erase(b.begin());
	}
    }

    return result;
}

/*
 *  using greedy monotonic stack + lexicographic merge hear because we can break the problem into 
 *  - selecting best subsequence from each array
 *  - merging them optimally
 *  - trying all possible divisons
 *  T:((M + N)^2), S:O(K)
 */
vector<int> Purgatory::maxNumber(vector<int>& nums1, vector<int>& nums2, int k) {
    vector<int> best;

    int m = nums1.size(), n = nums2.size();

    for (int i = max(0, k - n); i <= min(k, m); ++i) {
        vector<int> part1 = maxSubsequence(nums1, i);
	vector<int> part2 = maxSubsequence(nums2, k - i);

	vector<int> candidate = mergeMaxNumber(part1, part2);

	best = max(best, candidate);
    }

    return best;
}

}
