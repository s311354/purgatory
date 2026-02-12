#include "purgatory.h"

namespace purgatory {

/*
 *  using BFS here because it naturally breaks the problem into levels, by keeping track and count per level, 
 *  we compute averages efficiently in O(N) time
 *  T: O(n), S: O(n)
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
 *  T: O(n), S: O(n)
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
 *  T: O(n), S: O(n)
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

    if (root->left) {
        if (!root->left->left && !root->left->right)
            sum += root->left->val;
        else
	    sum += sumOfLeftLeaves(root->left);
    }    

    sum += sumOfLeftLeaves(root->right);

    return sum;
}

/*
 *  using dynamic programming here becuase we can break the problem into smaller subproblems, 
 *  relying only on already computed smaller states.
 *  T: O(n), S: O(n)
 */
int Purgatory::numSquares(int n) {
    vector<int> dp(n + 1, INT_MAX);
    dp[0] = 0;

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j*j <= i; ++j) {
            dp[i] = min(dp[i], dp[i - j * j] + 1);
    	}
    }

    return dp[n];
}


int gcdCanMeasureWater(int a, int b) {
    while (b != 0) {
        int r = a % b;
	a = b;
	b = r;
    }
    return a;
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

    return target % gcdCanMeasureWater(x, y) == 0;
}


void findLaddersbfs(const string &beginWord, const string &endWord, unordered_set<string> &dict, unordered_map<string, vector<string>> &parents, unordered_map<string, int> &dist) {

    queue<string> q;
    q.push(beginWord);
    dist[beginWord] = 0;

    while (!q.empty()) {
        string cur = q.front(); q.pop();
	int step = dist[cur];

	for (int i = 0; i < cur.size(); ++i) {
	    string next = cur;

	    for (char c = 'a'; c <= 'z' ; ++c) {
                next[i] = c;

		if (!dict.count(next)) continue;

		if (!dist.count(next)) {
                    dist[next] = step + 1;
		    q.push(next);
		    parents[next].push_back(cur);
		} else if (dist[next] == step + 1) {
                    parents[next].push_back(cur);
		}
	    }
	}
    }
}

void backtrackFindLadders(string& word, string& beginWord, unordered_map<string, vector<string>>& parents, vector<string>& path, vector<vector<string>>& res) {
    if (word == beginWord) {
        res.push_back(vector<string>(path.rbegin(), path.rend()));
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
    unordered_map<string, int> dist;

    findLaddersbfs(beginWord, endWord, dict, parents, dist);
    
    vector<string> path = {endWord};
    backtrackFindLadders(endWord, beginWord, parents, path, res);

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




