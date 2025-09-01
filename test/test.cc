#include <gtest/gtest.h>
#include "purgatory.h"

#ifdef PURGATORY_X86_64

namespace purgatory {
// Build tree from level-order vector with INT_MIN as null
TreeNode* buildTree(const vector<int>& arr) {
    if (arr.empty() || arr[0] == INT_MIN) return nullptr;

    TreeNode* root = new TreeNode(arr[0]);
    queue<TreeNode*> q;
    q.push(root);

    int i = 1;

    while (!q.empty() && i < arr.size()) {
        TreeNode* node = q.front(); q.pop();

	if (i < arr.size() && arr[i] != INT_MIN) {
	    if(arr[i] != -1) 
            	node->left = new TreeNode(arr[i]);
	    else
		node->left = nullptr;
	    q.push(node->left);
	}
	i++;

	if (i < arr.size() && arr[i] != INT_MIN) {
	    if(arr[i] != -1)
                node->right = new TreeNode(arr[i]);
	    else
		node->right = nullptr;
	    q.push(node->right);
	}
	i++;
    }

    return root;
}

// Build node from level-order vector 
Node* buildNode(const vector<int>& arr) {
    if (arr.empty()) return nullptr;

    vector<Node*> nodes(arr.size(), nullptr);

    // Create nodes
    for (int i = 0; i < arr.size(); ++i) {
	if (arr[i] == -1) return nullptr;

        nodes[i] = new Node(arr[i]);
    }

    // Link children
    for (int i = 0; i < arr.size(); ++i) {
        int leftIdx = 2 * i + 1;
	int rightIdx = 2 * i + 2;

	if (leftIdx < arr.size()) nodes[i]->left = nodes[leftIdx];

	if (rightIdx < arr.size()) nodes[i]->right = nodes[rightIdx];
    }

    return nodes[0]; // root
}

// Convert connected node into vector
vector<int> serializeWithNext(Node* root) {
    vector<int> result;

    if (!root) return result;

    Node* leftmost = root;

    while(leftmost) {
        Node* cur = leftmost;

	while (cur) {
	    result.push_back(cur->val);
	    cur = cur->next;
	}

	result.push_back(-1);
	leftmost = leftmost->left;
    }

    return result;
}


}

TEST(X86_64Test, BasicCheck) {
	EXPECT_EQ(1 + 1, 2);
}

TEST(X86_64Test, increasingTripletCheck) {

    purgatory::Purgatory solutions;

    // Basic Case:
    vector<int> nums = {1, 2, 3, 4, 5};

    bool output = solutions.increasingTriplet(nums);

    bool expected = true;

    EXPECT_EQ(output, expected);
}

TEST(X86_64Test, mergeCheck) {

    purgatory::Purgatory solutions;

    // Basic Case:
    vector<int> nums1 = {1, 2, 3, 0, 0, 0};
    vector<int> nums2 = {2, 5, 6};
    int m = 3, n = 3;

    solutions.merge(nums1, m, nums2, n);

    vector<int> expected = {1, 2, 2, 3, 5 ,6};

    EXPECT_EQ(expected, nums1);

    // Edge Case:
    nums1 = {1, 0}; nums2 = {2}; m = 1; n = 1;
	
    solutions.merge(nums1, m, nums2, n);

    expected = {1, 2};

    EXPECT_EQ(expected, nums1);
}

TEST(X86_64Test, removeDuplicatesCheck) {
	purgatory::Purgatory solutions;

    // Basic Case:
    vector<int> nums = {1, 1, 1, 2, 2, 3};
    int k = solutions.removeDuplicates(nums);

    int expected = 5;

    EXPECT_EQ(expected, k);

    // Edge Case:
    nums = {1, 1, 1};
    k = solutions.removeDuplicates(nums);

    expected = 2;

    EXPECT_EQ(expected, k);
}

TEST(X86_64Test, rotateCheck) {
    purgatory::Purgatory solutions;

    // Basic Case:
    vector<int> nums = {1, 2, 3, 4, 5, 6, 7};
    int k = 3;

    solutions.rotate(nums, k);

    vector<int> expected = {5, 6, 7, 1, 2, 3, 4};

    EXPECT_EQ(expected, nums);

    // Edge Case:
    nums = {1, 2}; k = 1;

    solutions.rotate(nums, k);

    expected = {2, 1};

    EXPECT_EQ(expected, nums);
}

TEST(X86_64Test, candyCheck) { 
    purgatory::Purgatory solutions;

    // Basic Case:
    vector<int> ratings = {1, 0, 2};

    int expected = 5;

    EXPECT_EQ(expected, solutions.candy(ratings));

    // Edge Case:
    ratings = {1, 2, 2};

    expected = 4;

    EXPECT_EQ(expected, solutions.candy(ratings));
}


TEST(X86_64Test, removeElemetCheck) {
    purgatory::Purgatory solutions;

    // Basic Case:
    vector<int> nums = {3, 2, 2, 3};
    int val = 3;
        
    int k = solutions.removeElemet(nums, val);

    int expected = 2;

    EXPECT_EQ(expected, k);

    // Edge Case:
    nums = {0, 1, 2, 2, 3, 0, 4, 2}; val = 2;

    k = solutions.removeElemet(nums, val);

    expected = 5;

    EXPECT_EQ(expected, k);
}

TEST(X86_64Test, canJumpCheck) {
    purgatory::Purgatory solutions;

    // Basic Case:
    vector<int> nums = {2, 3, 1, 1, 4};

    bool expected = true;

    EXPECT_EQ(expected, solutions.canJump(nums));

    // Edge Case:
    nums = {3, 2, 1, 0, 4};

    expected = false;

    EXPECT_EQ(expected, solutions.canJump(nums));
}

TEST(X86_64Test, productExceptSelfCheck) {
    purgatory::Purgatory solutions;

    // Basic Case: 
    vector<int> nums = {1, 2, 3, 4};
    
    vector<int> result = solutions.productExceptSelf(nums);

    vector<int> expected = {24, 12, 8, 6};

    EXPECT_EQ(expected, result);

    // Edge Case:
    nums = {2, 3, 4, 5};

    result = solutions.productExceptSelf(nums);

    expected = {60, 40, 30, 24};

    EXPECT_EQ(expected, result);
}

TEST(X86_64Test, fullJustifyCheck) {
    purgatory::Purgatory solutions;

    // Basic Case:
    vector<string> words = {"This", "is", "an", "example", "of", "text", "justification."};

    int maxWidth = 16;

    vector<string> result = solutions.fullJustify(words, maxWidth);

    vector<string> expected = {"This    is    an", "example  of text", "justification.  "};

    EXPECT_EQ(expected, result);

    // Edge Case:
    words = {""}; maxWidth = 1;

    result = solutions.fullJustify(words, maxWidth);

    expected = {" "};

    EXPECT_EQ(expected, result);
}

TEST(X86_64Test, canConstructChecl) {
    purgatory::Purgatory solutions;

    // Basic Case:
    string ransomNot = "a", magazine = "b";

    bool expected = false;

    EXPECT_EQ(expected, solutions.canConstruct(ransomNot, magazine));

    // Edge Case:
    ransomNot = "aa"; magazine = "aab";

    expected = true;

    EXPECT_EQ(expected, solutions.canConstruct(ransomNot, magazine));
}

TEST(X86_64Test, groupAnagramsCheck) {
    purgatory::Purgatory solutions;

    // Basic Case:
    vector<string> strs = {"eat", "tea", "tan", "ate", "nat", "bat"};

    vector<vector<string>> result = solutions.groupAnagrams(strs);

    vector<vector<string>> expected = {{"bat"}, {"tan", "nat"}, {"eat", "tea", "ate"}};

    EXPECT_EQ(expected, result);

    // Edge Case:
    strs = {"", ""};

    result = solutions.groupAnagrams(strs);

    expected = {{"", ""}};

    EXPECT_EQ(expected, result);
}

TEST(X86_64Test, longestConsecutiveCheck) {
    purgatory::Purgatory solutions;

    // Basic Case:
    vector<int> nums = {100, 4, 200, 1, 3, 2};

    int expected = 4;

    EXPECT_EQ(expected, solutions.longestConsecutive(nums));

    // Edge Case:
    nums = {0, 3, 7, 2, 5, 8, 4, 6, 0, 1};

    expected = 9;

    EXPECT_EQ(expected, solutions.longestConsecutive(nums));
}

TEST(X86_64Test, findSubstringCheck) {
    purgatory::Purgatory solutions;

    // Basic Case:
    string s = "barfoothefoobarman";

    vector<string> words = {"foo", "bar"};

    vector<int> expected = {0, 9};

    EXPECT_EQ(expected, solutions.findSubstring(s, words));

    // Edge Case:
    s = "wordgoodgoodgoodbestword"; words = {"word", "good", "best", "word"};

    expected = {};

    EXPECT_EQ(expected, solutions.findSubstring(s, words));
}

TEST(X86_64Test, isPalindromeCheck) {
    purgatory::Purgatory solutions;

    // Basic Case:
    string s = "A man, a plan, a canal: Panama";

    bool expected = true;

    EXPECT_EQ(expected, solutions.isPalindrome(s));

    // Edge Case:
    s = "";

    expected = true;

    EXPECT_EQ(expected, solutions.isPalindrome(s));
}

TEST(X86_64Test, twoSumCheck) {
    purgatory::Purgatory solutions;

    // Basic Case:
    vector<int> numbers = {2, 7, 11, 15};

    int target = 9;

    vector<int> expected = {1, 2};

    EXPECT_EQ(expected, solutions.twoSum(numbers, target));

    // Edge Case:
    numbers = {2, 3, 4}; target = 6;

    expected = {1, 3};

    EXPECT_EQ(expected, solutions.twoSum(numbers, target));
}

TEST(X86_64Test, maxAreaCheck) {
    purgatory::Purgatory solutions;

    // Basic Case:
    vector<int> height = {1, 8, 6, 2, 5, 4, 8, 3, 7};

    int expected = 49;

    EXPECT_EQ(expected, solutions.maxArea(height));

    // Edge Case:
    height = {1, 1};

    expected = 1;

    EXPECT_EQ(expected, solutions.maxArea(height));
}

TEST(X86_64Test, trapCheck) {
    purgatory::Purgatory solutions;

    // Basic Case:
    vector<int> height = {0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1};

    int expected = 6;

    EXPECT_EQ(expected, solutions.trap(height));

    // Edge Case:
    height = {};

    expected = 0;

    EXPECT_EQ(expected, solutions.trap(height));
}


TEST(X86_64Test, containsNearbyDuplicateCheck) {
    purgatory::Purgatory solutions;

    // Basic Case:
    vector<int> nums = {1, 2, 3, 1};

    int k = 3;

    bool expected = true;

    EXPECT_EQ(expected, solutions.containsNearbyDuplicate(nums, k));

    // Edge Case:
    nums = {1, 2, 3, 1, 2, 3}; k = 0;

    expected = false;

    EXPECT_EQ(expected, solutions.containsNearbyDuplicate(nums, k));
}

TEST(X86_64Test, minSubArrayLenCheck) {
    purgatory::Purgatory solutions;

    // Basic Case:
    vector<int> nums = {2, 3, 1, 2, 4, 3};

    int target = 7;

    int expected = 2;

    EXPECT_EQ(expected, solutions.minSubArrayLen(target, nums));

    // Edge Case:
    nums = {}; target = 4;

    expected = 0;

    EXPECT_EQ(expected, solutions.minSubArrayLen(target, nums));
}

TEST(X86_64Test, lengthOfLongestSubstringCheck) {
    purgatory::Purgatory solutions;

    // Basic Case:
    string s = "abcabcbb";

    int expected = 3;

    EXPECT_EQ(expected, solutions.lengthOfLongestSubstring(s));

    // Edge Case:
    s = "bbbb";

    expected = 1;

    EXPECT_EQ(expected, solutions.lengthOfLongestSubstring(s));
}

TEST(X86_64Test, NumArrayCheck) {

    vector<int> nums = {-2, 0, 3, -5, 2, -1};

    // Basic Case:
    int left = 0, right = 2;

    int expected = 1;

    purgatory::Purgatory::NumArray numarray(nums);

    EXPECT_EQ(expected, numarray.sumRanges(left, right));

    // Edge Case:
    left = 0; right = 5;

    expected = -3;

    EXPECT_EQ(expected, numarray.sumRanges(left, right));
}

TEST(X86_64Test, NumMatrixCheck) {

    // Basic Case:
    vector<vector<int>> matrix = {{3, 0, 1, 4, 2}, {5, 6, 3, 2, 1}, {1, 2, 0, 1, 5}, {4, 1, 0, 1, 7}, {1, 0, 3, 0, 5}};
    int row1 = 2, col1 = 1, row2 = 4, col2 = 3;

    int expected = 8;

    purgatory::Purgatory::NumMatrix nummatrix(matrix);

    EXPECT_EQ(expected, nummatrix.sumRegion(row1, col1, row2, col2));

    // Edge Case:
    row1 = 1; col1 = 2; row2 = 2; col2 = 4;

    expected = 12;

    EXPECT_EQ(expected, nummatrix.sumRegion(row1, col1, row2, col2));
}

TEST(X86_64Test, maxSumSubmatrixCheck) {
    purgatory::Purgatory solutions;

    // Basic Case:
    vector<vector<int>> matrix = {{1, 0, 1}, {0, -2, 3}};
    int k = 2;

    int expected = 2;

    EXPECT_EQ(expected, solutions.maxSumSubmatrix(matrix, k));

    // Edge Case:
    matrix = {{2, 2, -1}}; k = 3;

    expected = 3;

    EXPECT_EQ(expected, solutions.maxSumSubmatrix(matrix, k));
}

TEST(X86_64Test, averageOfLevelsCheck) {
    purgatory::Purgatory solutions;

    // Basic Case:
    vector<int> nums = {3, 9, 20, -1, -1, 15, 7}; // -1 represents "null"

    vector<double> expected = {3, 14.5, 11};

    EXPECT_EQ(expected, solutions.averageOfLevels(purgatory::buildTree(nums)));

    // Edge Case:
    nums = {};

    expected = {};

    EXPECT_EQ(expected, solutions.averageOfLevels(purgatory::buildTree(nums)));
}

TEST(X86_64Test, rightSideViewCheck) {
    purgatory::Purgatory solutions;

    // Basic Case:
    vector<int> nums = {1, 2, 3, -1, 5, -1, 4};

    vector<int> expected = {1, 3, 4};

    EXPECT_EQ(expected, solutions.rightSideView(purgatory::buildTree(nums)));

    // Edge Case:
    nums = {};

    expected = {};

    EXPECT_EQ(expected, solutions.rightSideView(purgatory::buildTree(nums)));
}

TEST(X86_64Test, levelOrderCheck) {
    purgatory::Purgatory solutions;

    // Basic Case:
    vector<int> nums = {3, 9, 20, -1, -1, 15, 7};

    vector<vector<int>> expected = {{3}, {9, 20}, {15, 7}};

    EXPECT_EQ(expected, solutions.levelOrder(purgatory::buildTree(nums)));

    // Edge Case:
    nums = {};

    expected = {};

    EXPECT_EQ(expected, solutions.levelOrder(purgatory::buildTree(nums)));
}

TEST(X86_64Test, serializeCheck) {

    // Basic Case:
    vector<int> nums = {1, 2, 3, -1, -1, 4, 5};

    string expected = "1,2,null,null,3,4,null,null,5,null,null,";

    purgatory::Purgatory::Codec codec;

    EXPECT_EQ(expected, codec.serialize(purgatory::buildTree(nums)));

    // Edge Case:
    nums = {};

    expected = "null,";

    EXPECT_EQ(expected, codec.serialize(purgatory::buildTree(nums)));
}

TEST(X86_64Test, isValidCheck) {
    purgatory::Purgatory solutions;

    // Basic Case:
    string s = "()";

    bool expected = true;

    EXPECT_EQ(expected, solutions.isValid(s));

    // Edge Case:
    s = "";

    expected = true;

    EXPECT_EQ(expected, solutions.isValid(s));
}

TEST(X86_64Test, simplifyPathCheck) {
    purgatory::Purgatory solutions;

    // Basic Case:
    string path = "/home/";

    string expected = "/home";

    EXPECT_EQ(expected, solutions.simplifyPath(path));

    // Edge Case:
    path = "/../";

    expected = "/";

    EXPECT_EQ(expected, solutions.simplifyPath(path));
}

TEST(X86_64Test, evalRPNCheck) {
    purgatory::Purgatory solutions;

    // Basic Case:
    vector<string> tokens = {"2", "1", "+", "3", "*"};

    int expected = 9;

    EXPECT_EQ(expected, solutions.evalRPN(tokens));

    // Edge Case:
    tokens = {"4", "13", "5", "/", "+"};

    expected = 6;

    EXPECT_EQ(expected, solutions.evalRPN(tokens));
}

TEST(X86_64Test, calculateCheck) {
    purgatory::Purgatory solutions;

    // Basic Case:
    string s = "1 + (2 - 3)";

    int expected = 0;

    EXPECT_EQ(expected, solutions.calculate(s));

    // Edge Case:
    s = "0-5";

    expected = -5;

    EXPECT_EQ(expected, solutions.calculate(s));
}

TEST(X86_64Test, levelOrderBottomCheck) {
    purgatory::Purgatory solutions;

    // Basic Case:
    vector<int> nums = {3, 9, 20, -1, -1, 15, 7};

    vector<vector<int>> expected = {{15, 7}, {9, 20}, {3}};

    EXPECT_EQ(expected, solutions.levelOrderBottom(purgatory::buildTree(nums)));

    // Edge Case:
    nums = {};

    expected = {};

    EXPECT_EQ(expected, solutions.levelOrderBottom(purgatory::buildTree(nums)));
}

TEST(X86_64Test, minDepthCheck) {
    purgatory::Purgatory solutions;

    // Basic Case:
    vector<int> nums = {1, 2, 3, 4, -1, -1, -1};

    int expected = 2;

    EXPECT_EQ(expected, solutions.minDepth(purgatory::buildTree(nums)));

    // Edge Case:
    nums = {};

    expected = 0;

    EXPECT_EQ(expected, solutions.minDepth(purgatory::buildTree(nums)));
}

TEST(X86_64Test, connectCheck) {
    purgatory::Purgatory solutions;

    // Basic Case:
    vector<int> nums = {1, 2, 3, 4, 5, 6, 7};

    vector<int> expected = {1, -1, 2, 3, -1, 4, 5, 6, 7, -1};

    EXPECT_EQ(expected, purgatory::serializeWithNext(solutions.connect(purgatory::buildNode(nums))));

    // Edge Case:
    nums = {};

    expected = {};

    EXPECT_EQ(expected, purgatory::serializeWithNext((solutions.connect(purgatory::buildNode(nums)))));
}

TEST(X86_64Test, removevalidParenthesesCheck) {
    purgatory::Purgatory solutions;

    // Basic Case:
    string s = "()())()";

    vector<string> expected = {"(())()", "()()()"};

    EXPECT_EQ(expected, solutions.removevalidParentheses(s));

    // Edge Case:
    s = ")(";

    expected = {""};

    EXPECT_EQ(expected, solutions.removevalidParentheses(s));
}

TEST(X86_64Test, findJudgeCheck) {
    purgatory::Purgatory solutions;

    // Basic Case:
    int n = 2;

    vector<vector<int>> trust = {{1, 2}};

    int expected = 2;

    EXPECT_EQ(expected, solutions.findJudge(n, trust));

    // Edge Case:
    n = 3; trust = {{1, 3}, {2, 3}, {3, 1}};

    expected = -1;

    EXPECT_EQ(expected, solutions.findJudge(n, trust));
}

TEST(X86_64Test, numIslandsCheck) {
    purgatory::Purgatory solutions;

    // Basic Case:
    vector<vector<char>> grid = {{'1', '1', '1', '1', '0'}, {'1', '1', '0', '1', '0'}, {'1', '1', '0', '0', '0'}, {'0', '0', '0', '0', '0'}};

    int expected = 1;

    EXPECT_EQ(expected, solutions.numIslands(grid));

    // Edge Case:
    grid = {{'0', '0'}, {'0', '0'}};

    expected = 0;

    EXPECT_EQ(expected, solutions.numIslands(grid));
}

TEST(X86_64Test, solveCheck) {
    purgatory::Purgatory solutions;

    // Basic Case:
    vector<vector<char>> board = {{'X', 'X', 'X', 'X'}, {'X', 'O', 'O', 'X'}, {'X', 'X', 'O', 'X'}, {'X', 'O', 'X', 'X'}};
    vector<vector<char>> expected = {{'X', 'X', 'X', 'X'}, {'X', 'X', 'X', 'X'}, {'X', 'X', 'X', 'X'}, {'X', 'O', 'X', 'X'}};

    solutions.solve(board);

    EXPECT_EQ(expected, board);

    // Edge Case:
    board = {{'O', 'O'}, {'O', 'O'}};

    expected = {{'O', 'O'}, {'O', 'O'}};

    solutions.solve(board);

    EXPECT_EQ(expected, board);
}

TEST(X86_64Test, longestIncreasingPathCheck) {
    purgatory::Purgatory solutions;

    // Basic Case:
    vector<vector<int>> matrix = {{9, 9, 4}, {6, 6, 8}, {2, 1, 1}};

    int expected = 4;

    EXPECT_EQ(expected, solutions.longestIncreasingPath(matrix));

    // Edge Case:
    matrix = {{1}};

    expected = 1;

    EXPECT_EQ(expected, solutions.longestIncreasingPath(matrix));
}


#elif PURGATORY_ARM64LE

TEST(ARM64LETest, BasicCheck) {
	EXPECT_EQ(1 + 1, 2);
}
#elif PURGATORY_I386

TEST(I386Test, BasicCheck) {
	EXPECT_EQ(1 + 1, 2);
}
#endif
