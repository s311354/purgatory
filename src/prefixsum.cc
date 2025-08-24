#include "purgatory.h"

namespace purgatory {


/*
 *  using prefix sums here because we can break the problem into pre computation O(n) + query O(1)
 */
Purgatory::NumArray::NumArray(vector<int>& nums) {
    int n = nums.size();
    prefix.resize(n + 1, 0);

    for (int i = 0; i < n; ++i) {
        prefix[i + 1] = prefix[i] + nums[i];
    }
}

int Purgatory::NumArray::sumRanges(int left, int right) {
    return prefix[right + 1] - prefix[left];
}

/*
 *  using 2D prefix sums here because we can break the problem into preprocessing O(m * n) + queries O(1)
 */
Purgatory::NumMatrix::NumMatrix(vector<vector<int>>& matrix) {
    int m = matrix.size();
    int n = m > 0 ? matrix[0].size() : 0;

    prefix.assign(m + 1, vector<int>(n + 1, 0));

    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            prefix[i][j] = matrix[i-1][j-1] + prefix[i-1][j] + prefix[i][j-1] - prefix[i-1][j-1];
	}
    }
}

int Purgatory::NumMatrix::sumRegion(int row1, int col1, int row2, int col2) {
    row1++; col1++; row2++; col2++;

    return prefix[row2][col2] - prefix[row1 - 1][col2] - prefix[row2][col1 - 1] + prefix[row1 - 1][col1 - 1];
}

/*
 * using a row compression + 1D max subarray <= k here because 
 * - by fixing row boundaries, we reduce to a known problem
 * - using prefix sums + BST we can query in O( log n)
 */
int Purgatory::maxSumSubmatrix(vector<vector<int>>& matrix, int k) {
    int m = matrix.size(), n = matrix[0].size();
    int ans = INT_MIN;

    for (int top = 0; top < m ; ++top) {
        vector<int> colSum(n, 0);

	for (int bottom = top; bottom < m; ++bottom) {
            for (int c = 0; c < n; ++c) {
                colSum[c] += matrix[bottom][c];
	    }


	    set<int> prefix;
	    prefix.insert(0);
	    int curSum = 0;

	    for (int x : colSum) {
                curSum += x;

		auto it = prefix.lower_bound(curSum - k);

		if (it != prefix.end()) {
                   ans = max(ans, curSum - *it);
		}

		prefix.insert(curSum);
	    }
	}
    }

    return ans;

}




}
