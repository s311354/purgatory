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

    vector<string> mapping = {"", "", "abc", "def", "ghi", "jkl", "mno", "pqr", "tuv", "wxyz"};

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


}
