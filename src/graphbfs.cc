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




}

