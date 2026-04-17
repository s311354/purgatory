#include "purgatory.h"

namespace purgatory {

void dfsBinaryTreePaths(TreeNode* node, string& path, vector<string>& result) {
    if (!node) return;

    // cache behavior
    int len = path.size();

    if (!path.empty()) path += "->";

    path += to_string(node->val);

    if (!node->left && !node->right) {
        result.push_back(path);
    } else {
        dfsBinaryTreePaths(node->left, path, result);
        dfsBinaryTreePaths(node->right, path, result);
    }

    path.resize(len);
}

/*
 *  using DFS recursion here because the problem is naturally recursive
 */
vector<string> Purgatory::binaryTreePaths(TreeNode* root) {
    vector<string> result;

    if (!root) return result;

    // cache behavior
    string path;
    path.reserve(256);

    dfsBinaryTreePaths(root, path, result);

    return result;
}

/*
 *  using backtracking here because the problem is naturally recursive
 */
vector<string> Purgatory::letterCombinations(string digits) {
    if (digits.empty()) return {};

    // cache behavior
    static const string mapping[10] = {"", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};

    vector<string> result;
    // cache behavior
    int n = digits.size();
    result.reserve(1 << n);

    string path(n, ' ');

    // cpu pipeline
    function<void(int)> dfs = [&](int index) {
        if (index == n) {
            result.push_back(path);
	    return;
	}

	const string &letters = mapping[digits[index] - '0'];

	// cache behavior
	for (char c : letters) {
            path[index] = c;
	    dfs(index + 1);
	}
    };

    dfs(0);
    return result;
}

/*
 *  using backtracking here because the problem is about combinatorial generation. We define the recursion state (start, path), and stop once path size == k
 */
void dfsCombine(int start, int depth, int n, int k, vector<int> &path, vector<vector<int>> &result) {
    if (depth == k) {
        result.push_back(path);
	return;
    }

    // branch prediction
    for (int i = start; i <= n - (k - depth) + 1; ++i) {
        path[depth] = i;
	dfsCombine(i + 1, depth + 1, n, k, path, result);
    }
}

vector<vector<int>> Purgatory::combine(int n, int k) {
    vector<vector<int>> result;
    // cache behavior
    vector<int> path(k);

    // cpu pipeline
    dfsCombine(1, 0, n, k, path, result);
    return result;
}

/*
 *  using backtracking with pruning here because the state is (row, occupied cols, diagonals, anti-diagonals). At each row, we explore possible placements.
 */
int Purgatory::totalNQueens(int n) {
    int count = 0;

    // cpu pipeline
    function<void(int, int, int, int)> dfs = [&](int row, int cols, int diag, int antiDiag) {
        if (row == n) {
            count++;
	    return;
	}

	// register vs memory
	int available = ((1 << n) - 1) & ~(cols | diag | antiDiag);

        while (available) {
	    int pos = available & -available;

	    available &= (available - 1);

	    dfs(row + 1, cols | pos, (diag | pos) << 1, (antiDiag | pos) >> 1);
	}
    };

    dfs(0, 0, 0 , 0);
    return count;
}

/*
 *  using a bit counting abstraction here because we can break the problem into bit combinatorics
 *  T: O(1), S: O(K)
 */
vector<string> Purgatory::readBinaryWatch(int turnedOn) {
    vector<string> result;
    // cache behavior
    result.reserve(128);

    // register vs memory
    int hourBits[12], minuteBits[60];

    for(int i = 0; i < 12; ++i)
        hourBits[i] = __builtin_popcount(i);
    for(int i = 0; i < 60; ++i)
	minuteBits[i] = __builtin_popcount(i);

    vector<string> minuteStr(60);
    for(int i = 0; i < 60; ++i) {
	// branch prediction
        if (i < 10)
	    minuteStr[i] = "0" + to_string(i);
	else
	    minuteStr[i] = to_string(i);
    }

    for (int h = 0; h < 12; ++h) {
        for(int m = 0; m < 60; ++m) {
            if (hourBits[h] + minuteBits[m] == turnedOn)
                result.emplace_back(to_string(h) + ":" + minuteStr[m]);
	}
    }

    return result;
}

/*
 *  using recursion here because we can break the problem into the state space of subsets.
 *  T: O(n*2^n), S:O(n*2^n)
 */
void dfsSubsets(int start, int n, vector<int> &nums, vector<int> &current, vector<vector<int>> &result) {
    // cache behavior
    result.emplace_back(current);

    for (int i = start; i < n; ++i) {
        current.push_back(nums[i]);
	dfsSubsets(i + 1, n, nums, current, result);
	current.pop_back();
    }
}

vector<vector<int>> Purgatory::subsets(vector<int>& nums) {
    int n = nums.size();
    vector<vector<int>> result;
    // cache behavior
    result.reserve(1 << n);
    vector<int> current;
    current.reserve(n);

    // cpu pipeline 
    dfsSubsets(0, n, nums, current, result);
    return result;
}

/*
 *  using built by reflection here because we can break the problem into reflection + bit prefixing
 *  T: O(2^n), S:O(2^n)
 */
vector<int> Purgatory::grayCode(int n) {
    int size = 1 << n;
    // cache behavior
    vector<int> result(size);

    // cpu pipeline
    for (int i = 0; i < size; ++i) {
        result[i] = i ^ (i >> 1);
    }
    return result;
}

static constexpr double EPS = 1e-6;

bool dfsJudgePoint(vector<double>& nums) {
    int n = nums.size();

    if (n == 1)
        return fabs(nums[0] - 24.0) < EPS;

    // cpu pipeline
    for (int i = 0; i < n; ++i) {
	// branch prediction
        for (int j = i + 1; j < n; ++j) {

            // register vs memory
	    double a = nums[i], b = nums[j];

	    // cache hebavior
	    vector<double> next;
	    next.reserve(n - 1);

	    for (int k = 0; k < n; ++k)
                if (k != i && k != j)
	            next.push_back(nums[k]);

            vector<double> candidates = {
	        a + b,
		a - b,
		b - a,
		a * b
	    };

	    if (fabs(b) > EPS) candidates.push_back(a / b);
	    if (fabs(a) > EPS) candidates.push_back(b / a);

	    for (double val : candidates) {
                next.push_back(val);

		if (dfsJudgePoint(next))
		    return true;

	        next.pop_back();
	    }
	}
    }

    return false;
}

bool Purgatory::judgePoint24(vector<int>& cards) {
    vector<double> nums(cards.begin(), cards.end());
    return dfsJudgePoint(nums);
}

}
