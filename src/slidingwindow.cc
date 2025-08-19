#include "purgatory.h"

namespace purgatory {

/*
 *  using unordered_map to store the last seen index of each value here because this let me check O(1) time whether the current element has appeared within distance k.
 */
bool Purgatory::containsNearbyDuplicate(vector<int>& nums, int k) {
    unordered_map<int, int> lastIndex;

    for (int i = 0; i < nums.size(); ++i) {
        if (lastIndex.find(nums[i]) != lastIndex.end()) {
             int prev = lastIndex[nums[i]];

	     if (i - prev <= k) return true;
	}
	lastIndex[nums[i]] = i;
    }

    return false;
}

/*
 *  using a sliding window approach here because all numbers are positive, ensuring that once the sum exceeds the target, moving left forward will only reduce the sum.
 */
int Purgatory::minSubArrayLen(int target, vector<int>& nums) {
    int left = 0, sum = 0;
    int minLen = INT_MAX;

    for (int right = 0; right < nums.size(); ++right) {
        sum += nums[right];

	while (sum >= target) {
            minLen = min(minLen, right - left + 1);

	    sum -= nums[left++];
	}
    }

    return minLen == INT_MAX ? 0 : minLen;
}

/*
 *  using a sliding window with a hash map to track the last scene index of each character here because whenever a duplicate is found within the current window, left jumps past its previous occurrence. This ensure we always have a substring with unique characters.
 */
int Purgatory::lengthOfLongestSubstring(string s) {
    unordered_map<char, int> charIndex;
    int left = 0, maxLen = 0;

    for (int right = 0; right < s.size(); ++right) {
        char c = s[right];

	if (charIndex.count(c) && charIndex[c] >= left) {
            left = charIndex[c] + 1;
	}

	charIndex[c] = right;
	maxLen = max(maxLen, right - left + 1);
    }

    return maxLen;
}

}
