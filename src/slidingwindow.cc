#include "purgatory.h"

namespace purgatory {

/*
 *  using unordered_map to store the last seen index of each value here because this let me check O(1) time whether the current element has appeared within distance k.
 *  T: O(n), S: O(n)
 */
bool Purgatory::containsNearbyDuplicate(vector<int>& nums, int k) {
    unordered_map<int, int> lastIndex;
    // register vs memory
    int n = nums.size();
    // cache behavior
    lastIndex.reserve(n);

    for (int i = 0; i < n; ++i) {
	// register vs memory
	int value = nums[i];
	auto it = lastIndex.find(value);
        if (it != lastIndex.end()) {
	    if (i - it->second <= k)
                return true;
	    it->second = i;
	} else {
	    lastIndex.emplace(value, i);
	}
    }

    return false;
}

/*
 *  using a sliding window approach here because all numbers are positive, ensuring that once the sum exceeds the target, moving left forward will only reduce the sum.
 *  T: O(n), S: O(1)
 */
int Purgatory::minSubArrayLen(int target, vector<int>& nums) {
    int left = 0, sum = 0;
    int minLen = INT_MAX;

    // memory vs register
    int n = nums.size();
    for (int right = 0; right < n; ++right) {
	sum += nums[right];

	// branch prediction
	if (sum >= target) {
	    do {
		// cpu pipeline
		int len = right - left + 1;
		if (len < minLen) minLen = len;
	        sum -= nums[left++];
	    } while (sum >= target);
	}
    }

    return minLen == INT_MAX ? 0 : minLen;
}

/*
 *  using a sliding window with a hash map to track the last scene index of each character here because whenever a duplicate is found within the current window, left jumps past its previous occurrence. This ensure we always have a substring with unique characters.
 *  T: O(n), S: O(n, charset_size)
 */
int Purgatory::lengthOfLongestSubstring(string s) {
    // cache behavior
    int last[256];
    memset(last, -1, sizeof(last));

    int left = 0, maxLen = 0;

    for (int right = 0; right < s.size(); ++right) {
        unsigned char c = s[right];

	// register vs memory
	int prev = last[c];
	left = prev >= left ? prev + 1: left;

	last[c] = right;
	// register vs memory
	int len = right - left + 1;
	maxLen = len > maxLen ? len : maxLen;
    }

    return maxLen;
}

/*
 *  using divide-and-conquer
 *  T: O(n log n), S: O(n)
 */
string solveLongestNiceSubstring(const string &s, int l, int r) {
    if (r - l < 2) return "";

    // cpu pipeline
    int lower = 0, upper = 0;
    for (int i = l; i < r; ++i) {
        if (islower(s[i]))
	    lower |= 1 << (s[i] - 'a');
        else
            upper |= 1 << (s[i] - 'A');
    }  

    int valid = lower & upper;

    for (int i = l; i < r; ++i) {
        char c = s[i];

	// branch prediction
	if (islower(c) && !(valid & (1 << (c - 'a'))) ||
	    islower(c) && !(valid & (1 << (c - 'A')))) {
	    // cache behavior
	    string left = solveLongestNiceSubstring(s, l, i);
	    string right = solveLongestNiceSubstring(s, i + 1, r);
	    return left.size() >= right.size() ? left : right;
	}
    }

    return s.substr(l, r - l);
}

string Purgatory::longestNiceSubstring(string s) {
    return solveLongestNiceSubstring(s, 0, s.size());
}

/*
 *  using frequency-based divide pattern here because we can break the problem into invalid characters as natural boundaries.
 *  T: O(n log n), S: O(n)
 */
int solveLongestSubstring(const string &s, int l, int r, int k) {
    if (r - l < k) return 0;

    // cache behavior
    int freq[26] = {0};

    for (int i = l; i < r; ++i)
        freq[s[i] - 'a']++;

    // cpu pipeline
    for (int i = l; i < r; ++i) {
        if (freq[s[i] - 'a'] < k) {
	    int j = i + 1;

	    while (j < r && freq[s[j] - 'a'] < k)
	        ++j;

	    return max(solveLongestSubstring(s, l, i, k), solveLongestSubstring(s, j, r, k));
	}
    } 

    return r - l;
}

int Purgatory::longestSubstring(string s, int k) {
    return solveLongestSubstring(s, 0, s.size(), k);
}

/*
 *  using recurrence dynamic idea here because we can break the problem into the cumulative native of extending arithmetic subarrays.
 *  T: O(n), S: O(1)
 */
int Purgatory::numberOfArithmeticSlices(vector<int>& nums) {
    if (nums.size() < 3) return 0;

    int count = 0, current = 0;

    // cache behavior
    const int *p = nums.data();
    const int *end = p + nums.size();

    // register vs memory
    int prev = p[0];
    int curr = p[1];
    int prev_diff = curr - prev;

    for (p += 2; p < end; ++p) {
        int next = *p;
	int diff = next - curr;

	// branch prediction
	int same = (diff == prev_diff);
	current = same * (current + 1);
	count += current;

	prev_diff = diff;
	prev = curr;
	curr = next;
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
