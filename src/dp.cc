#include "purgatory.h"

namespace purgatory {

/*
 *  using Fibonacci recurrence here
 */
int Purgatory::climbStairs(int n) {
    if (n == 1) return 1;
    if (n == 2) return 2;

    int prev1 = 1;
    int prev2 = 2;
    int curr = 0;

    for (int i = 3; i <= n; ++i) {
        curr = prev1 + prev2;
	prev1 = prev2;
	prev2 = curr;
    }
    return curr;
}

/*
 *  using DP recurrence here because at each house, the choice is rob it or skip it
 */
int Purgatory::rob(vector<int>& nums) {
    int n = nums.size();

    if (n == 0) return 0;
    if (n == 1) return nums[0];

    int prev2 = nums[0];
    int prev1 = max(nums[0], nums[1]);

    for (int i = 2; i < n; ++i) {
        int curr = max(prev1, prev2 + nums[i]);
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
    unordered_set<string> dict(wordDict.begin(), wordDict.end());
    int n = s.size();
    vector<bool> dp(n+1, false);

    dp[0] = true;

    for(int i = 1; i <= n; ++i) {
        for (int j = 0; j < i; ++j) {
            if(dp[j] && dict.count(s.substr(j, i - j))) {
	        dp[i] = true;
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
    vector<vector<bool>> dp(m + 1, vector<bool>(n + 1, false));

    dp[0][0] = true;

    for (int j = 2; j <= n; ++j) {
        if (p[j - 1] == '*') dp[0][j] = dp[0][j-2];
    }

    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (p[j - 1] == '.' || p[j - 1] == s[i - 1]) {
	        dp[i][j] = dp[i-1][j-1];
	    } else if (p[j-1] == '*') {
                dp[i][j] = dp[i][j - 2];

		if (p[j-2] == '.' || p[j - 2] == s[i - 1])
		    dp[i][j] = dp[i][j] || dp[i - 1][j];
  
	    }
	}
    }
    return dp[m][n];
}

}
