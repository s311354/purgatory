#include "purgatory.h"

namespace purgatory {

/*
 *  using BFS level order traversal here because we can break the problem into layers. The trick is: instead of reversing at the end, we insert each new level at the begining of the result vector.
 *  T: O(n), S: O(n)
 */
vector<vector<int>> Purgatory::levelOrderBottom(TreeNode *root) {
    if (!root) return {};

    vector<vector<int>> result;
    queue<TreeNode*> q;
    q.push(root);

    while (!q.empty()) {
        vector<int> level;
	int size = q.size();
        level.reserve(size);

	for (int i = 0; i < size; ++i) {
            TreeNode* node = q.front(); q.pop();

	    level.push_back(node->val);

	    if (node->left) q.push(node->left);
	    if (node->right) q.push(node->right);
	} 
        // register vs memory
	result.push_back(std::move(level));
    }

    reverse(result.begin(), result.end());

    return result;
}

/*
 *  using BFS here because we can break the problem into levels.
 *  T: O(n), S: O(w)
 */
int Purgatory::minDepth(TreeNode *root) {
    if (!root) return 0;

    // cache behavior
    vector<TreeNode *> q;
    q.reserve(1024);
    q.push_back(root);

    int depth = 1;
    int head = 0;

    while (head < q.size()) {
        int size = q.size() - head;

	for (int i = size; i > 0; --i) {
	    TreeNode *node = q[head++];

	    // register vs memory
	    TreeNode *left = node->left;
	    TreeNode *right = node->right;

	    // branch prediction
	    if (left == nullptr)
                if (right == nullptr)
	            return depth;

	    if (left) q.push_back(left);
	    if (right) q.push_back(right);
	}

	depth++;
    }

    return depth;
}

/*
 *  using a constant space solution by exploiting the perfect binary tree property here because next pointers already built to traverse levels
 *  T: O(n), S: O(1)
 */
Node* Purgatory::connect(Node* root) {
    if (!root) return nullptr;

    Node *level_start = root;

    while(true) {
	// register vs memory
	Node *next_level = level_start->left;
	if (!next_level)
	    break;

        Node *current = level_start;

	while (current) {
	    // register vs memory
	    Node *left = current->left;
	    Node *right = current->right;
	    Node *next = current->next;

            left->next = right;

	    if (next)
                right->next = next->left;

	    current = next;
	}

	level_start = next_level;
    }

    return root;
}

bool isValid(const string &s) {
    int count = 0;

    // register vs memory
    for (int i = 0, n = s.size(); i < n; ++i) {
   	char c = s[i];

        if (c == '(')
            count++;
	else if (c == ')') {
            count--;
	    if (count < 0) return false;
	}
    }

    return count == 0;
}

/*
 *  using BFS here because it naturally guarantees minimum removals, once we find valid strings, we don't need to go deeper.
 *  T: O(n * 2 ^n), S: O(n * 2^n)
 */
vector<string> Purgatory::removeInvalidParentheses(string s) {
    vector<string> result;

    if (s.empty()) return {""};

    // memory allocation
    unordered_set<string> visited;
    visited.reserve(10000);

    // cache behavior
    vector<string> q;
    q.push_back(s);
    int head = 0;

    bool found = false;

    visited.insert(s);

    while(head < q.size()) {
        string cur = std::move(q[head++]);

	if (isValid(cur)) {
            result.push_back(cur);
	    found = true;
	}

	if (found) continue;

	for(int i = 0; i < cur.size(); ++i) {
             if (cur[i] != '(' && cur[i] != ')') continue;


	     string next;
	     next.reserve(cur.size() - 1);
             // cache behavior
	     for (int j = 0; j < cur.size(); ++j)
                 if (j != i)
                     next.push_back(cur[j]);

	     if (!visited.count(next)) {
                 visited.insert(next);
		 q.push_back(std::move(next));
	     }
	}
    }
    return result;
}

int Purgatory::findCenter(vector<vector<int>>& edges) {
    int a = edges[0][0], b = edges[0][1];
    int c = edges[1][0], d = edges[1][1];

    if (a == c || a == d) return a;

    return b;
}

/*
 * using BFS 
 *  T: O(n + v), S: O(n)
 */
bool Purgatory::isBipartite(vector<vector<int>>& graph) {
    int n = graph.size();

    vector<int> color(n, -1);

    for (int i = 0; i < n; ++i) {
        if (color[i] != -1)
	    continue;

	// cache behavior
	vector<int> q;
	int head = 0;
	q.push_back(i);
	color[i] = 0;

	while (head < q.size()) {
            int node = q[head++];

	    // register vs memory
	    int currColor = color[node];
	    int nextColor = 1 - currColor;

	    for (int &nei: graph[node]) {
                if (color[nei] == -1) {
		    color[nei] = nextColor;
		    q.push_back(nei);
		} else if (color[nei] != nextColor) {
                    return false;
		}
	    }
	}
    }

    return true;
}

int Purgatory::numberOfComponents(vector<vector<int>>& properties, int k) {
    int n = properties.size();

    vector<int> parent(n), rank(n, 0);

    for (int i = 0; i < n; ++i)
        parent[i] = i;

    // branch prediction
    auto find = [&](auto&& slef, int x) -> int {
        while (x != parent[x]) {
	    parent[x] = parent[parent[x]];
	    x = parent[x];
	}

	return x;
    };

    // cache behavior
    auto unite = [&](int a, int b) {
        int pa = find(find, a);
	int pb = find(find, b);

	if (pa == pb) return;

	if (rank[pa] < rank[pb])
	    parent[pa] = pb;
	else if (rank[pa] > rank[pb])
	    parent[pb] = pa;
	else {
	    parent[pb] = pa;
	    rank[pa]++;
	}
    };

    // cache behavior
    vector<bitset<101>> bits(n);

    for (int i = 0; i < n; ++i) {
        for (int v : properties[i])
	    bits[i].set(v);
    }

    for (int i = 0; i < n ; ++i) {
        for (int j = i + 1; j < n; ++j) {
	    if ((bits[i] & bits[j]).count() >= k)
	        unite(i, j);
	}
    }

    int components = 0;

    for (int i = 0; i < n; ++i) {
        if (find(find, i) == i)
	    components++;
    }

    return components;
}

}

