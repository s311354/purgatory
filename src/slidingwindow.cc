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

/*
 *  using divide-and-conquer
 *  T: O(n), S: O(n)
 */
string Purgatory::longestNiceSubstring(string s) {
    if (s.size() < 2) return "";
    
    unordered_set<char> seen(s.begin(), s.end());

    for (int i = 0; i < (int) s.size(); ++i) {
        char c = s[i];

	if (seen.count(tolower(c)) && seen.count(toupper(c)))
	    continue;

	string left = longestNiceSubstring(s.substr(0, i));
	string right = longestNiceSubstring(s.substr(i + 1));
	return (left.size() >= right.size() ? left : right);
    }
 
    return s;
}

/*
 *  using frequency-based divide pattern here because we can break the problem into invalid characters as natural boundaries.
 *  T: O(n log n), S: O(n)
 */
int Purgatory::longestSubstring(string s, int k) {
    if (s.empty() || k > s.size()) return 0;

    if (k <= 1) return s.size();

    vector<int> freq(26, 0);

    for (char c: s) freq[c - 'a']++;

    for (int i = 0; i < s.size(); ++i) {
        if (freq[s[i] - 'a'] < k) {
            string left = s.substr(0, i);
	    string right = s.substr(i + 1);

	    return max(longestSubstring(left, k), longestSubstring(right, k));
	}
    }

    return s.size();
}

/*
 *  using recurrence dynamic idea here because we can break the problem into the cumulative native of extending arithmetic subarrays.
 *  T: O(n), S: O(1)
 */
int Purgatory::numberOfArithmeticSlices(vector<int>& nums) {
    if (nums.size() < 3) return 0;

    int count = 0, curr = 0;

    for (int i = 2; i < (int) nums.size(); ++i) {
        if (nums[i] - nums[i - 1] == nums[i - 1] - nums[i - 2]) {
            curr += 1;
	    count += curr;
	} else {
	    curr = 0;
	}
    }

    return count;
}

/*
 *  using multiset median-tracking approach here because we can break the problem into median partitioning
 *  T: O(n log k), S: O(k)
 */
vector<double> Purgatory::medianSlidingWindow(vector<int>& nums, int k) {
    vector<double> res;
    multiset<int> window(nums.begin(), nums.begin() + k);

    auto mid = next(window.begin(), k/2);

    for (int i = k;; ++i) {
        if (k % 2 == 1)
	    res.push_back(*mid);
	else
	    res.push_back(((double) * mid + *prev(mid))/ 2.0);

	if (i == nums.size()) break;

	window.insert(nums[i]);
	if (nums[i] < *mid)
	    mid--;

	if (nums[i - k] <= *mid)
	    mid++;
	window.erase(window.lower_bound(nums[i - k]));
    }

    return res;
}

}
