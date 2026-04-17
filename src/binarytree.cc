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

    // cache behavior
    result.reserve(64);

    // compiler optimization (abstraction)
    deque<TreeNode*> q;
    q.push_back(root);

    while(!q.empty()) {
        int size = q.size();
	long long sum = 0;

	for (int i = 0; i < size; ++i) {
            TreeNode* node = q.front(); q.pop_front();
	    
	    // register vs memory
	    int val = node->val;
	    sum += val;
	    
             // register vs memory
	    TreeNode *left = node->left;
	    TreeNode *right = node->right;

	    if (left) q.push_back(left);
	    if (right) q.push_back(right);
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

    // cache behavior
    res.reserve(64);

    // compiler optimization (abstraction)
    deque<TreeNode*> q;
    q.push_back(root);

    while(!q.empty()) {
        int size = q.size();
	// branch predication
        TreeNode *lastNode = nullptr;

	for (int i = 0; i < size; ++i) {
            TreeNode* node = q.front(); q.pop_front();

	    lastNode = node;
	    // register vs memory
            TreeNode *left = node->left;
	    TreeNode *right = node->right;

	    if (left) q.push_back(left);
	    if (right) q.push_back(right);
	}
	res.push_back(lastNode->val);
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

    // cache behavior
    res.reserve(64);

    // compiler optimization (abstraction)
    deque<TreeNode*> q;
    q.push_back(root);

    while(!q.empty()) {
        int size = q.size();
	vector<int> level;
	// cache behavior
	level.reserve(size);

	for (int i = 0; i < size ; ++i) {
            TreeNode* node = q.front(); q.pop_front();
            
	    // register vs memory
	    int val = node->val;
	    level.push_back(val);

	    // register vs memory
	    TreeNode *left = node->left;
	    TreeNode *right = node->right;
	    if (left) q.push_back(left);
	    if (right) q.push_back(right);
	}
        
	res.push_back(move(level));
    }

    return res;
}

/*
 *  using DFS here because we can break the problem into each subtree contributes its; local left-leaf sum
 *  T: O(n), S: O(h)
 */
int Purgatory::sumOfLeftLeaves(TreeNode* root) {
    if (!root) return 0;

    int sum = 0;

    // cpu pipeline
    vector<TreeNode *> stack;
    stack.push_back(root);

    while (!stack.empty()) {
	TreeNode *node = stack.back();
	stack.pop_back();

	// register vs memory
        TreeNode *left = node->left;
        TreeNode *right = node->right;

        if (left) {
	    // branch prediction
	    bool isLeaf = (left->left == nullptr) & (left->right == nullptr);
            if (isLeaf)
                sum += left->val;
            else
		stack.push_back(left);
        }    

	if (right)
	    stack.push_back(right);
    }

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

    // branch predication
    vector<int> squares;
    for(int j = 1; j * j <= n ; ++j)
        squares.push_back(j * j);

    for (int i = 1; i <= n; ++i) {
	int best = INT_MAX;

        for (const int sq : squares) {
            if (sq > i) break;

	    // register vs memory
	    int candidate = dp[i - sq] + 1;
            best = (candidate < best) ? candidate : best;
    	}

	dp[i] = best;
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

    // compiler optimization
    return target % std::gcd(x, y) == 0;
}


void findLaddersbfs(const string &beginWord, const string &endWord, unordered_set<string> &dict, unordered_map<string, vector<string>> &parents, unordered_map<string, int> &dist) {

    queue<string> q;
    q.push(beginWord);
    dist[beginWord] = 0;

    while (!q.empty()) {
        string cur = q.front(); q.pop();
	int step = dist[cur];

	// register vs memory
	string next = cur;
	for (int i = 0; i < cur.size(); ++i) {
	    char original = next[i];

	    for (char c = 'a'; c <= 'z' ; ++c) {
		if (c == original) continue;

		next[i] = c;

		if (!dict.count(next)) continue;

		// branch prediction
                auto it = dist.find(next);

		if (it == dist.end()) {
                    dist[next] = step + 1;
		    q.push(next);
		    parents[next].push_back(cur);
		} else if (it->second == step + 1) {
                    parents[next].push_back(cur);
		}
	    }
	    next[i] = original;
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

vector<int> Purgatory::inorderTraversal(TreeNode *root) {
    vector<int> result;

    // cache behavior
    vector<TreeNode *> stack;
    stack.reserve(100);

    TreeNode *current = root;

    while (current || !stack.empty()) {
	// branch predication
        while (current) {
	    stack.push_back(current);
	    current= current->left;
	}

	current = stack.back();
	stack.pop_back();

	result.push_back(current->val);

	current = current->right;
    }

    return result;
}

int Purgatory::numTrees(int n) {
    // cache behavior
    static vector<int> dp = {1};

    // register vs memory
    int start = dp.size();

    if (start > n) return dp[n];

    dp.resize(n + 1);

    for(int nodes = start; nodes <= n; ++nodes) {
        dp[nodes] = 0;

	for (int root = 1; root <= nodes; ++root) {
	    dp[nodes] += dp[root - 1] * dp[nodes - root];
	}
    }

    return dp[n];
}

vector<int> Purgatory::findFrequentTreeSum(TreeNode *root) {

    unordered_map<int, int> freq;
    freq.reserve(10000);

    int maxFreq = 0;

    function<int(TreeNode*)> dfs = [&](TreeNode *node) ->int {
        if (!node) return 0;

	int leftSum = dfs(node->left);
	int rightSum = dfs(node->right);

	int sum = leftSum + rightSum + node->val;

	// register vs memory
	int f = ++freq[sum];

	if (f > maxFreq) maxFreq = f;

	return sum;
    };
    
    dfs(root);

    // cache behavior
    vector<int> result;
    result.reserve(freq.size());

    for (auto &p: freq) {
        if (p.second == maxFreq) {
	    result.push_back(p.first);
	}
    }

    return result;
}

int Purgatory::maxAncestorDiff(TreeNode *root) {
    if (!root) return 0;

    int result = 0;

    // cache behavior
    vector<tuple<TreeNode*, int, int>> st;
    st.emplace_back(root, root->val, root->val);

    while (!st.empty()) {
        auto [node, curMin, curMax] = st.back();
	st.pop_back();

	result = max(result, curMax - curMin);

	// branch prediction
	if (node->left) {
            int mn = min(curMin, node->left->val);
	    int mx = max(curMax, node->left->val);
	    st.emplace_back(node->left, mn, mx);
	}

	// branch prediction
	if (node->right) {
            int mn = min(curMin, node->right->val);
	    int mx = max(curMax, node->right->val);
	    st.emplace_back(node->right, mn, mx);
	}
    }

    return result;
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




