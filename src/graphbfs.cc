#include "purgatory.h"

namespace purgatory {

/*
 *  using BFS level order traversal here because we can break the problem into layers. The trick is: instead of reversing at the end, we insert each new level at the begining of the result vector.
 */
vector<vector<int>> Purgatory::levelOrderBottom(TreeNode *root) {
    if (!root) return {};

    vector<vector<int>> result;
    queue<TreeNode*> q;
    q.push(root);

    while (!q.empty()) {
        vector<int> level;
	int size = q.size();

	for (int i = 0; i < size; ++i) {
            TreeNode* node = q.front(); q.pop();

	    level.push_back(node->val);

	    if (node->left) q.push(node->left);
	    if (node->right) q.push(node->right);
	} 

	result.insert(result.begin(), level);
    }

    return result;
}

/*
 *  using BFS here because we can break the problem into levels.
 */
int Purgatory::minDepth(TreeNode *root) {
    if (!root) return 0;

    queue<pair<TreeNode*, int>> q;
    q.push({root, 1});

    while(!q.empty()) {
        auto [node, depth] = q.front(); q.pop();

	if (!node->left && !node->right) return depth;

	if (node->left) q.push({node->left, depth + 1});
	if (node->right) q.push({node->right, depth + 1});
    }

    return 0;
}

/*
 *  using a constant space solution by exploiting the perfect binary tree property here because next pointers already built to traverse levels
 */
Node* Purgatory::connect(Node* root) {
    if (!root) return nullptr;

    Node *leftmode = root;

    while(leftmode->left) {
        Node *head = leftmode;

	while (head) {
            head->left->next = head->right;

	    if (head->next) head->right->next = head->next->left;

	    head = head->next;
	}

	leftmode = leftmode->left;
    }

    return root;
}

bool isValid(const string &s) {
    int count = 0;

    for (char c: s) {
        if (c == '(') count++;
	else if (c == ')') {
            count--;
	    if (count < 0) return false;
	}
    }

    return count == 0;
}

/*
 *  using BFS here because it naturally guarantees minimum removals, once we find valid strings, we don't need to go deeper.
 */
vector<string> Purgatory::removeInvalidParentheses(string s) {
    vector<string> result;

    if (s.empty()) return {""};

    unordered_set<string> visited;
    queue<string> q;
    bool found = false;

    q.push(s);
    visited.insert(s);

    while(!q.empty()) {
        string cur = q.front(); q.pop();

	if (isValid(cur)) {
            result.push_back(cur);
	    found = true;
	}

	if (found) continue;

	for(int i = 0; i < cur.size(); ++i) {
             if (cur[i] != '(' && cur[i] != ')') continue;

	     string next = cur.substr(0, i) + cur.substr(i + 1);

	     if (!visited.count(next)) {
                 visited.insert(next);
		 q.push(next);
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

bool Purgatory::isBipartite(vector<vector<int>>& graph) {
    int n = graph.size();

    vector<int> color(n, -1);

    for (int i = 0; i < n; ++i) {
        if (color[i] != -1)
	    continue;

	queue<int> q;
	q.push(i);
	color[i] = 0;

	while (!q.empty()) {
            int node = q.front(); q.pop();

	    for (int nei: graph[node]) {
                if (color[nei] == -1) {
		    color[nei] = 1 - color[node];
		    q.push(nei);
		} else if (color[nei] == color[node]) {
                    return false;
		}
	    }
	}
    }

    return true;
}

int Purgatory::numberOfComponents(vector<vector<int>>& properties, int k) {
    int n = properties.size();
    vector<unordered_set<int>> sets(n);

    for (int i = 0; i < n; ++i) {
        for (int x: properties[i])
	    sets[i].insert(x);
    }

    vector<int> parent(n);
    iota(parent.begin(), parent.end(), 0);

    function<int (int)> find = [&](int x) {
        return parent[x] == x ? x : parent[x] = find(parent[x]);
    };

    auto unit = [&](int a, int b) {
        a = find(a); b = find(b);
	if (a != b) parent[a] = b;
    };

    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
	    int cnt = 0;
	    for (int val : sets[i]) {
                if (sets[j].count(val))
		    if (++cnt >= k) {
		        unit(i, j);
			break;
		    }
	    }
	}
    }

    unordered_set<int> roots;

    for (int i = 0; i < n; ++i) {
        roots.insert(find(i));
    }

    return roots.size();
}

}

