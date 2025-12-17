#include "purgatory.h"

namespace purgatory {

/*
 *  using BFS here because it naturally breaks the problem into levels, by keeping track and count per level, we compute averages efficiently in O(N) time
 */
vector<double> Purgatory::averageOfLevels(TreeNode* root) {
    vector<double> result;

    if (!root) return result;

    queue<TreeNode*> q;
    q.push(root);

    while(!q.empty()) {
        int size = q.size();

	long long sum = 0;

	for (int i = 0; i < size; ++i) {
            TreeNode* node = q.front(); q.pop();
	    sum += node->val;
	    if (node->left) q.push(node->left);
	    if (node->right) q.push(node->right);
	}

	result.push_back((double) sum/size);
    }

    return result;
}

/*
 *  using BFS here because it cleanly captures the last node at each level
 */
vector<int> Purgatory::rightSideView(TreeNode* root) {
    vector<int> res;

    if (!root) return res;

    queue<TreeNode*> q;
    q.push(root);

    while(!q.empty()) {
        int size = q.size();

	for (int i = 0; i < size; ++i) {
            TreeNode* node = q.front(); q.pop();

	    if (i == size - 1) res.push_back(node->val);

	    if (node->left) q.push(node->left);
	    if (node->right) q.push(node->right);
	}
    }
    return res;
}

/*
 *  using BFS here because the problem naturally maps to level-order traversal
 */
vector<vector<int>> Purgatory::levelOrder(TreeNode* root) {
    vector<vector<int>> res;

    if (!root) return res;

    queue<TreeNode*> q;
    q.push(root);

    while(!q.empty()) {
        int size = q.size();
	vector<int> level;

	for (int i = 0; i < size ; ++i) {
            TreeNode* node = q.front(); q.pop();

	    level.push_back(node->val);

	    if (node->left) q.push(node->left);
	    if (node->right) q.push(node->right);
	}
        res.push_back(level);
    }

    return res;
}

/*
 *  using DFS here because we can break the problem into each subtree contributes its; local left-leaf sum
 *  T: O(n), S: O(h)
 */
int Purgatory::sumOfLeftLeaves(TreeNode* root) {
    if (!root)
        return 0;

    int sum = 0;

    if (root->left && !root->left->left && !root->left->right) 
        sum += root->left->val;

    sum += sumOfLeftLeaves(root->left);
    sum += sumOfLeftLeaves(root->right);

    return sum;
}

/*
 *  using dynamic programming here becuase we can break the problem into smaller subproblems, relying only on already computed smaller states.
 *  T: O(n), S: O(n)
 */
int Purgatory::numSquares(int n) {
    vector<int> dp(n + 1, INT_MAX);
    dp[0] = 0;

    vector<int> squares;

    for (int i = 1; i*i <= n; ++i)
        squares.push_back(i * i);

    for (int i = 1; i <= n; ++i) {
        for (int sq : squares) {
	    if (sq > i)
                break;

	    dp[i] = min(dp[i], dp[i - sq] + 1);
	}
    }

    return dp[n];
}

/*
 *  using Bezout's identity here because we can break the problem into multiple of gcd
 *  T: O(n), S: O(1)
 */
bool Purgatory::canMeasureWater(int x, int y, int target) {
    if (target > x + y)
        return false;

    if (target == 0)
        return true;

    int g = gcd(x, y);

    return (target % g == 0);
}

void backtrackFindLadders(string& word, string& beginWord, unordered_map<string, vector<string>>& parents, vector<string>& path, vector<vector<string>>& res) {
    if (word == beginWord) {
        reverse(path.begin(), path.end());
	res.push_back(path);
	reverse(path.begin(), path.end());
	return;
    }

    for (auto& p: parents[word]) {
        path.push_back(p);
	backtrackFindLadders(p, beginWord, parents, path, res);
	path.pop_back();
    }
}

/*
 *  using BFS and DFS reconstructs the structure of shortest paths.
 *  T: O(N * L^2), S: O(N * L)
 */
vector<vector<string>> Purgatory::findLadders(string beginWord, string endWord, vector<string>& wordList) {
    unordered_set<string> dict(wordList.begin(), wordList.end());
    vector<vector<string>> res;

    if (!dict.count(endWord))
        return res;

    unordered_map<string, vector<string>> parents;
    unordered_set<string> current, next;
    current.insert(beginWord);

    bool found = false;

    while (!current.empty() && !found) {
        for (auto& w: current)
	    dict.erase(w);

	for (auto& w: current) {
            string word = w;
	    for (int j = 0; j < word.size(); ++j) {
                char old = word[j];

		for (char c = 'a'; c <= 'z'; ++c) {
                    if (c == old)
		        continue;

		    word[j] = c;

		    if (dict.count(word)) {
			if (word == endWord)
		            found = true;

			next.insert(word);
			parents[word].push_back(w);
		    }
		}
		word[j] = old;
	    }
	}

	current.swap(next);
	next.clear();
    }

    if (found) {
        vector<string> path = {endWord};
	backtrackFindLadders(endWord, beginWord, parents, path, res);
    }

    return res;
}

/*
 *  using preorder DFS here because it's symmetrical and ensures that serialization and deserialization mirror each other
 */
string Purgatory::Codec::serialize(TreeNode* root) {
    if (!root) return "null,";

    return to_string(root->val) + "," + serialize(root->left) + serialize(root->right);
}

TreeNode* Purgatory::Codec::deserialize(string data) {
    vector<string> tokens = split(data, ',');
    int idx = 0;
    return build(tokens, idx);
}

vector<string> Purgatory::Codec::split(const string& s, char delim) {
    vector<string> tokens;
    string token;
    stringstream ss(s);

    while(getline(ss, token, delim)) {
        while(!token.empty() && isspace(token.back())) token.pop_back();
	while(!token.empty() && isspace(token.front())) token.erase(token.begin());

	if (!token.empty()) tokens.push_back(token);
    }
    return tokens;
}

TreeNode* Purgatory::Codec::build(const vector<string>& tokens, int& idx) {
    if (idx >= (int)tokens.size() || tokens[idx] == "null") {
	idx++;
	return nullptr;
    }

    TreeNode* node = new TreeNode(stoi(tokens[idx++]));

    node->left = build(tokens, idx);
    node->right = build(tokens, idx);

    return node;
}

}




