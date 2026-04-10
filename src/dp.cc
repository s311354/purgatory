#include "purgatory.h"

namespace purgatory {

/*
 *  using Fibonacci recurrence here
 */
int Purgatory::climbStairs(int n) {
    // branch prediction
    if (n <= 2) return n;

    // register vs memory
    int a = 1, b = 2;
    int i = 3;

    // loop unrolling
    for (; i + 1<= n; i += 2)  {
        a = a + b;
	b = a + b;
    }

    if (i == n) {
        a = a + b;
	return a;
    }

    return b;
}

/*
 *  using DP recurrence here because at each house, the choice is rob it or skip it
 */
int Purgatory::rob(vector<int>& nums) {
    int n = nums.size();

    if (n == 0) return 0;
    if (n == 1) return nums[0];

    int prev2 = nums[0];
    // function call
    int prev1 = nums[0] > nums[1] ? nums[0] : nums[1];

    for (int i = 2; i < n; ++i) {
	// register vs memory
	int val = nums[i];
	int take = prev2 + val;
	int skip = prev1;

        int curr = take > skip ? take : skip;
	prev2 = prev1;
	prev1 = curr;
    }

    return prev1;
}

/*
 *  using dynamic programming here because we can break the problem into smaller subproblems
 *  - each dp[i] depends on whether there's a valid split at j
 *  - the hash set look up ensures substring membership is O(1)
 */
bool Purgatory::wordBreak(string s, vector<string>& wordDict) {
    // cache behavoir
    unordered_set<string> dict;
    dict.reserve(wordDict.size() * 2);
    int maxLen = 0;
    for (auto &w: wordDict) {
        dict.insert(w);

	if (w.size() > maxLen) maxLen = w.size();
    }

    int n = s.size();
    const char *data = s.data();

    vector<bool> dp(n+1, false);
    dp[0] = true;

    // branch prediction
    vector<int> trueIndices;
    trueIndices.reserve(n);
    trueIndices.push_back(0);

    for(int i = 1; i <= n; ++i) {
        for (int j : trueIndices) {
	    // branch prediction
            if (i - j > maxLen) continue;

	    // register vs memory
            if(dict.find(string(data + j, i - j)) != dict.end()) {
	        dp[i] = true;
		trueIndices.push_back(i);
		break;
	    }
	}
    }
    return dp[n];
}

/*
 *  using DP here because regex matching has overlapping subproblems. We break it into status (i, j) where i is string length, j is pattern length
 */
bool Purgatory::isMatch(string s, string p) {
    int m = s.size(), n = p.size();

    // cache behavior
    vector<bool> dp(n + 1, false);
    dp[0] = true;

    // register vs memory
    const char *ps = s.c_str();
    const char *pp = p.c_str();

    for (int j = 2; j <= n; ++j) {
        if (pp[j - 1] == '*')
	    dp[j] = dp[j-2];
    }

    for (int i = 1; i <= m; ++i) {
	// register vs memory
        bool prev = dp[0];
	dp[0] = false;

        for (int j = 1; j <= n; ++j) {
	    // register vs memory
	    bool temp = dp[j];
            char sc = ps[i - 1];
            char pc = pp[j - 1];

	    // branch prediction
            if (pc != '*') {
	        dp[j] = prev & (pc == '.' || pc == sc);
	    } else {
	        dp[j] = dp[j - 2] |
			((pp[j - 2] == '.' || pp[j - 2] == sc) & dp[j]);
	    }

	    prev = temp;
	}
    }
    return dp[n];
}

}
