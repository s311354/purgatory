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




