#include "purgatory.h"

namespace purgatory {

void dfsBinaryTreePaths(TreeNode* node, string path, vector<string>& result) {
    if (!node) return;

    if (!path.empty()) path += "->";

    path += to_string(node->val);

    if (!node->left && !node->right) {
        result.push_back(path);
	return;
    }

    dfsBinaryTreePaths(node->left, path, result);
    dfsBinaryTreePaths(node->right, path, result);
}

/*
 *  using DFS recursion here because the problem is naturally recursive
 */
vector<string> Purgatory::binaryTreePaths(TreeNode* root) {
    vector<string> result;

    if (!root) return result;

    string path;
    dfsBinaryTreePaths(root, path, result);

    return result;
}

/*
 *  using backtracking here because the problem is naturally recursive
 */
vector<string> Purgatory::letterCombinations(string digits) {
    if (digits.empty()) return {};

    vector<string> mapping = {"", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};

    vector<string> result;
    string path;

    function<void(int)> backtrack = [&](int index) {
        if (index == digits.size()) {
            result.push_back(path);
	    return;
	}

	int d = digits[index] - '0';

	for (char c : mapping[d]) {
            path.push_back(c);
	    backtrack(index + 1);
	    path.pop_back();
	}
    };

    backtrack(0);
    return result;
}

/*
 *  using backtracking here because the problem is about combinatorial generation. We define the recursion state (start, path), and stop once path size == k
 */
vector<vector<int>> Purgatory::combine(int n, int k) {
    vector<vector<int>> result;
    vector<int> path;

    function<void(int)> dfs = [&](int start) {
        if ( path.size() == k) {
            result.push_back(path);
	    return;
	}
	
	for (int i = start; i <= n; ++i) {
            path.push_back(i);
	    dfs(i + 1);
	    path.pop_back();
	}
    };

    dfs(1);
    return result;
}

/*
 *  using backtracking with pruning here because the state is (row, occupied cols, diagonals, anti-diagonals). At each row, we explore possible placements.
 */
int Purgatory::totalNQueens(int n) {
    int count = 0;

    unordered_set<int> cols;
    unordered_set<int> diag;
    unordered_set<int> antiDiag;

    function<void(int)> backtrack = [&](int row) {
        if (row == n) {
            count++;
	    return;
	}

	for (int col = 0; col < n; ++col) {
            if (cols.count(col) || diag.count(row - col) || antiDiag.count(row + col)) continue;

	    cols.insert(col);
	    diag.insert(row - col);
	    antiDiag.insert(row + col);

	    backtrack(row + 1);

	    cols.erase(col);
	    diag.erase(row - col);
	    antiDiag.erase(row + col);
	}
    };

    backtrack(0);
    return count;
}

/*
 *  using a bit counting abstraction here because we can break the problem into bit combinatorics
 *  T: O(1), S: O(K)
 */
vector<string> Purgatory::readBinaryWatch(int turnedOn) {
    vector<string> result;

    for (int hour = 0; hour < 12; ++hour) {
        for (int minute = 0; minute < 60; ++minute) {
	    int bits = __builtin_popcount(hour) + __builtin_popcount(minute);

	    if (bits == turnedOn) {
	        string time = to_string(hour) + ":" + (minute < 10 ? "0" + to_string(minute) : to_string(minute));
      	        result.push_back(time);
	    }
	}
    }

    return result;
}

/*
 *  using recursion here because we can break the problem into the state space of subsets.
 *  T: O(n*2^n), S:O(n*2^n)
 */
vector<vector<int>> Purgatory::subsets(vector<int>& nums) {
    vector<vector<int>> result;
    vector<int> current;

    function<void(int)> backtrack = [&](int start) {
        result.push_back(current);

	for (int i = start; i < nums.size(); ++i) {
	    current.push_back(nums[i]);
	    backtrack(i + 1);
	    current.pop_back();
	}
    };

    backtrack(0);
    return result;
}

/*
 *  using built by reflection here because we can break the problem into reflection + bit prefixing
 *  T: O(2^n), S:O(2^n)
 */
vector<int> Purgatory::grayCode(int n) {
    vector<int> result = {0};

    for (int i = 0; i < n; ++i) {
        int prefix = 1 << i;

	for (int j = result.size() - 1; j >= 0; --j) {
	    result.push_back(result[j] + prefix);
	}
    }
    return result;
}


vector<double> computeJudgePoint(double a, double b) {
    vector<double> results = {a + b, a - b, b - a, a*b};

    if (fabs(b) > 1e-6) results.push_back(a/b);
    if (fabs(a) > 1e-6) results.push_back(b/a);

    return results;
}

bool dfsJudgePoint(vector<double> nums) {
    if (nums.size() == 1)
        return fabs(nums[0] - 24.0) < 1e-6;

    for (int i = 0; i < nums.size(); ++i) {
        for (int j = 0; j < nums.size(); ++j) {
            if (i == j) continue;

	    vector<double> next;

	    for (int k = 0; k < nums.size(); ++k)
                if (k != i && k != j)
	            next.push_back(nums[k]);


	    for (double val : computeJudgePoint(nums[i], nums[j])) {
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
