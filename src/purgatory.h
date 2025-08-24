#ifndef PURGATORY_H
#define PURGATORY_H

#include <iostream>
using namespace std;

// STL Containers
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <set>
#include <stack>

#include <string_view>
#include <climits>
#include <algorithm>
#include <sstream>

namespace purgatory {

struct X86_64 {
    static constexpr std::string_view name = "x86_64";
};

struct I386 {
    static constexpr std::string_view name = "i386";
};

struct ARM64LE {
    static constexpr std::string_view name = "arm64";
};

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x): val(x), left(nullptr), right(nullptr) {}
};

// Build tree from level-order vector with INT_MIN as null
TreeNode* buildTree(const vector<int>& arr);

class Purgatory {

public:

    Purgatory();
    Purgatory(istream& s);

    virtual ~Purgatory();

    // array/string
    bool increasingTriplet(vector<int>& nums);

    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n);

    int removeDuplicates(vector<int>& nums);

    void rotate(vector<int>& nums, int k);

    int candy(vector<int>& ratings);

    int removeElemet(vector<int>& nums, int val);

    bool canJump(vector<int>& nums);

    vector<int> productExceptSelf(vector<int>& nums);

    vector<string> fullJustify(vector<string>& words, int maxWidth);

    // hashmap
    bool canConstruct(string ransomNot, string magazine);

    vector<vector<string>> groupAnagrams (vector<string>& strs);

    int longestConsecutive(vector<int> &nums);

    vector<int> findSubstring(string s, vector<string>& words);

    // two pointers
    bool isPalindrome(string s); 
    
    vector<int> twoSum(vector<int> & numbers, int target);

    int maxArea(vector<int> & height);

    int trap(vector<int> & height);

    // sliding window
    bool containsNearbyDuplicate(vector<int>& nums, int k);

    int minSubArrayLen(int target, vector<int>& nums);

    int lengthOfLongestSubstring(string s);

    // prefix sum
    class NumArray {
    private:
	vector<int> prefix; // store prefix sums
    public:
        NumArray(vector<int>& nums);
        int sumRanges(int left, int right);
    };

    class NumMatrix {
    private:
	vector<vector<int>> prefix;

    public:
	NumMatrix(vector<vector<int>>& matrix);
	int sumRegion(int row1, int col1, int row2, int col2);
    };

    int maxSumSubmatrix(vector<vector<int>>& matrix, int k);

    // binary tree DFS
    vector<double> averageOfLevels(TreeNode* root);

    vector<int> rightSideView(TreeNode* root);

    vector<vector<int>> levelOrder(TreeNode* root);

    class Codec {
    public:
	string serialize(TreeNode* root);
	TreeNode* deserialize(string data);

    private:
	vector<string> split(const string& s, char delim);
	TreeNode* build(const vector<string>& tokens, int& idx);
    };

    // stack
    bool isValid(string s); 

    string simplifyPath(string path);

    int evalRPN(vector<string>& tokens);

    int calculate(string s);
};

template <typename E>
int purgatory_main(int argc, char **argv);

} /* namespace purgatory */

#endif /* PURGATORY_H */

