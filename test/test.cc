#include <gtest/gtest.h>
#include "purgatory.h"
#include "query.h"

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

ListNode* buildLinkedList(const vector<int>& values, int pos) {
    if (values.empty())
        return nullptr;

    ListNode dummy(0);
    ListNode* head = &dummy;

    ListNode* cycleNode = nullptr;

    for (int i = 0; i < values.size(); ++i) {
        head->next = new ListNode(values[i]);
	head = head->next;

	if (i == pos)
	    cycleNode = head;
    }

    if (pos >= 0)
        head->next = cycleNode;

    return dummy.next;
}

ListNode* buildLinkedList(const vector<int>& values) {
    if (values.empty())
        return nullptr;

    ListNode dummy(0);
    ListNode* head = &dummy;

    for (int x : values) {
        head->next = new ListNode(x);
	head = head->next;
    }

    return dummy.next;
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

// Convert connected Linked List node into vector
vector<int> toVector(ListNode* head) {
    vector<int> result;

    for (ListNode* curr = head; curr != nullptr; curr = curr->next) {
        result.push_back(curr->val);
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

    s = "(]";

    expected = false;

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

TEST(X86_64Test, nextGreaterElementCheck) {
    purgatory::Purgatory solutions;

    // Basic Case:
    vector<int> nums1 = {4, 1, 2}, nums2 = {1, 3, 4, 2};

    vector<int> expected = {-1, 3, -1};

    EXPECT_EQ(expected, solutions.nextGreaterElement(nums1, nums2));

    // Edge Case:
    nums1 = {2, 4}; nums2 = {4, 3, 2, 1};

    expected = {-1, -1};

    EXPECT_EQ(expected, solutions.nextGreaterElement(nums1, nums2));
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

TEST(X86_64Test, removeDuplicateLettersCheck) {
    purgatory::Purgatory solutions;

    // Basic Case: 
    string s = "bcabc";

    string expected = "abc";

    EXPECT_EQ(expected, solutions.removeDuplicateLetters(s));

    // Edge Case:
    s = "a";

    expected = "a";

    EXPECT_EQ(expected, solutions.removeDuplicateLetters(s));
}

TEST(X86_64Test, calculateIICheck) {
    purgatory::Purgatory solutions;

    // Basic Case:
    string s = "3+2*2";

    int expected = 7;

    EXPECT_EQ(expected, solutions.calculateII(s));

    // Edge Case:
    s = "3/2";
    
    expected = 1;

    EXPECT_EQ(expected, solutions.calculateII(s));
}

TEST(X86_64Test, longestValidParenthesesCheck) {
    purgatory::Purgatory solutions;
    
    // Basic Case:
    string s = "(()";

    int expected = 2;

    EXPECT_EQ(expected, solutions.longestValidParentheses(s));

    // Edge Case:
    s = "";

    expected = 0;

    EXPECT_EQ(expected, solutions.longestValidParentheses(s));
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

TEST(X86_64Test, lastStoneWeightCheck) {
    purgatory::Purgatory solutions;

    // Basic Case:
    vector<int> stones = {2, 7, 4, 1, 8, 1};

    int expected = 1;

    EXPECT_EQ(expected, solutions.lastStoneWeight(stones));

    // Edge Case:
    stones = {};

    expected = 0;

    EXPECT_EQ(expected, solutions.lastStoneWeight(stones));
}

TEST(X86_64Test, nthUglyNumberCheck) {
    purgatory::Purgatory solutions;

    // Basic Case:
    int n = 10;

    int expected = 12;

    EXPECT_EQ(expected, solutions.nthUglyNumber(n));

    // Edge Case:
    n = 1;

    expected = 1;

    EXPECT_EQ(expected, solutions.nthUglyNumber(n));
}

TEST(X86_64Test, topKFrequentCheck) {
    purgatory::Purgatory solutions;

    // Basic Case:
    vector<int> nums = {1, 1, 1, 2, 2, 3};

    int k = 2;

    vector<int> expected = {2, 1};

    EXPECT_EQ(expected, solutions.topKFrequent(nums, k));

    // Edge Case:
    nums = {1}; k = 1;

    expected = {1};

    EXPECT_EQ(expected, solutions.topKFrequent(nums, k));
}

TEST(X86_64Test, maxSlidingWindowCheck) {
    purgatory::Purgatory solutions;

    // Basic Case:
    vector<int> nums = {1, 3, -1, -3, 5, 3, 6, 7};

    int k = 3;

    vector<int> expected = {3, 3, 5, 5, 6, 7};

    EXPECT_EQ(expected, solutions.maxSlidingWindow(nums, k));

    // Edge Case:
    nums = {}; k = 0;

    expected = {};

    EXPECT_EQ(expected, solutions.maxSlidingWindow(nums, k));

}

TEST(X86_64Test, summaryRangesCheck) {
    purgatory::Purgatory solutions;

    // Basic Case:
    vector<int> nums = {0, 1, 2, 4, 5, 7};

    vector<string> expected = {"0->2", "4->5", "7"};

    EXPECT_EQ(expected, solutions.summaryRanges(nums));

    // Edge Case:
    nums = {};

    expected = {};
    
    EXPECT_EQ(expected, solutions.summaryRanges(nums));
}

TEST(X86_64Test, mergeIntervalsCheck) {
    purgatory::Purgatory solutions;

    // Basic Case:
    vector<vector<int>> intervals = {{1, 3}, {2, 6}, {8, 10}, {15, 18}};

    vector<vector<int>> expected = {{1,6}, {8, 10}, {15, 18}};

    EXPECT_EQ(expected, solutions.merge(intervals));

    // Edge Case:
    intervals = {};

    expected = {};

    EXPECT_EQ(expected, solutions.merge(intervals));
}

TEST(X86_64Test, insertCheck) {
    purgatory::Purgatory solutions;

    // Basic Case:
    vector<vector<int>> intervals = {{1, 3}, {6, 9}};

    vector<int> newInterval = {2, 5};

    vector<vector<int>> expected = {{1, 5}, {6, 9}};

    EXPECT_EQ(expected, solutions.insert(intervals, newInterval));

    // Edge  Case:
    intervals = {}; newInterval = {5, 7};

    expected = {{5, 7}};

    EXPECT_EQ(expected, solutions.insert(intervals, newInterval));
}

TEST(X86_64Test, findMinArrowShotsCheck) {
    purgatory::Purgatory solutions;

    // Basic Case:
    vector<vector<int>> points = {{10, 16}, {2, 8}, {1, 6}, {7, 12}};

    int expected = 2;

    EXPECT_EQ(expected, solutions.findMinArrowShots(points));

    // Edge Case:
    points = {{1, 2}, {3, 4}, {5, 6}};

    expected = 3;

    EXPECT_EQ(expected, solutions.findMinArrowShots(points));
}

TEST(X86_64Test, climbStairsCheck) {
    purgatory::Purgatory solutions;

    // Basic Case:
    int n = 2;

    int expected = 2;

    EXPECT_EQ(expected, solutions.climbStairs(n));

    // Edge Case:
    n = 1;

    expected = 1;

    EXPECT_EQ(expected, solutions.climbStairs(n));
}

TEST(X86_64Test, robCheck) {
    purgatory::Purgatory solutions;

    // Basic Case:
    vector<int> nums = {1, 2, 3, 1};

    int expected = 4;

    EXPECT_EQ(expected, solutions.rob(nums));

    // Edge Case:
    nums = {};

    expected = 0;

    EXPECT_EQ(expected, solutions.rob(nums));
}

TEST(X86_64Test, wordBreakCheck) {
    purgatory::Purgatory solutions;

    // Basic Case:
    string s = "leetcode";

    vector<string> wordDict = {"leet", "code"};

    bool expected = true;

    EXPECT_EQ(expected, solutions.wordBreak(s, wordDict));

    // Edge Case:
    s = "";

    wordDict = {};

    expected = true;

    EXPECT_EQ(expected, solutions.wordBreak(s, wordDict));
}

TEST(X86_64Test, isMatchCheck) {
    purgatory::Purgatory solutions;

    // Basic Case:
    string s = "aa", p = "a";

    bool expected = false;

    EXPECT_EQ(expected, solutions.isMatch(s, p));

    // Edge Case:
    s = "ab", p = ".*";

    expected = true;

    EXPECT_EQ(expected, solutions.isMatch(s, p));
}

TEST(X86_64Test, binaryTreePathsCheck) {
    purgatory::Purgatory solutions;

    // Basic Case:
    vector<int> nums = {1, 2, 3, -1, 5};

    vector<string> expected = {"1->2->5", "1->3"};

    EXPECT_EQ(expected, solutions.binaryTreePaths(purgatory::buildTree(nums)));

    // Edge Case:
    nums = {-1};

    expected = {"-1"};

    EXPECT_EQ(expected, solutions.binaryTreePaths(purgatory::buildTree(nums)));
}


TEST(X86_64Test, letterCombinationsCheck) {
    purgatory::Purgatory solutions;

    // Basic Case:
    string digits = "23";

    vector<string> expected = {"ad", "ae", "af", "bd", "be", "bf", "cd", "ce", "cf"};

    EXPECT_EQ(expected, solutions.letterCombinations(digits));

    // Edge Case:
    digits = "";

    expected = {};

    EXPECT_EQ(expected, solutions.letterCombinations(digits));
}

TEST(X86_64Test, combineCheck) {
    purgatory::Purgatory solutions;

    // Basic Case:
    int n = 4, k = 2;

    vector<vector<int>> expected = {{1, 2}, {1, 3}, {1, 4}, {2, 3}, {2, 4}, {3, 4}};

    EXPECT_EQ(expected, solutions.combine(n, k));

    // Edge Case:
    n = 0; k = 0;

    expected = {{}};

    EXPECT_EQ(expected, solutions.combine(n, k));
}

TEST(X86_64Test, totalNQueensCheck) {
    purgatory::Purgatory solutions;

    // Basic Case:
    int n = 4;

    int expected = 2;

    EXPECT_EQ(expected, solutions.totalNQueens(n));

    // Edge Case:
    n = 1;

    expected = 1;

    EXPECT_EQ(expected, solutions.totalNQueens(n));
}

TEST(X86_64Test, searchInsertCheck) {
    purgatory::Purgatory solutions;

    // Basic Case:
    vector<int> nums = {1, 3, 5, 6};

    int target = 5;

    int expected = 2;

    EXPECT_EQ(expected, solutions.searchInsert(nums, target));

    // Edge Case:
    nums = {5}; target = 5;

    expected = 0;

    EXPECT_EQ(expected, solutions.searchInsert(nums, target));
}

TEST(X86_64Test, searchMatricCheck) {
    purgatory::Purgatory solutions;

    // Basic Case:
    vector<vector<int>> matrix = {{1, 3, 5, 7}, {10, 11, 16, 20}, {23, 30, 34, 60}};

    int target = 3;

    bool expected = true;
    
    EXPECT_EQ(expected, solutions.searchMatric(matrix, target));

    // Edge Case:
    matrix = {{1, 2, 3, 4}}; target = 4;

    expected = true;

    EXPECT_EQ(expected, solutions.searchMatric(matrix, target));
}

TEST(X86_64Test, findPeakElementCheck) {
    purgatory::Purgatory solutions;

    // Basic Case:
    vector<int> nums = {1, 2, 3, 1};

    int expected = 2;

    EXPECT_EQ(expected, solutions.findPeakElement(nums));

    // Edge Case:
    nums = {1};

    expected = 0;

    EXPECT_EQ(expected, solutions.findPeakElement(nums));
}

TEST(X86_64Test, findMedianSortedArraysCheck) {
    purgatory::Purgatory solutions;

    // Basic Case:
    vector<int> nums1 = {1, 3}, nums2 = {2};

    double expected = 2;

    EXPECT_EQ(expected, solutions.findMedianSortedArrays(nums1, nums2));

    // Edge Case:
    nums1 = {}; nums2 = {1};

    expected = 1;

    EXPECT_EQ(expected, solutions.findMedianSortedArrays(nums1, nums2));
}

TEST(X86_64Test, generateCheck) {
    purgatory::Purgatory solutions;

    // Basic Case:
    int numRows = 3;

    vector<vector<int>> expected = {{1}, {1, 1}, {1, 2, 1}};

    EXPECT_EQ(expected, solutions.generate(numRows));

    // Edge Case:
    numRows = 0;

    expected = {};

    EXPECT_EQ(expected, solutions.generate(numRows));   
}

TEST(X86_64Test, nextPermutationCheck) {
    purgatory::Purgatory solutions;

    // Basic Case:
    vector<int> nums = {1, 2, 3};
    solutions.nextPermutation(nums);

    vector<int> expected = {1, 3, 2};

    EXPECT_EQ(expected, nums);

    // Edge Case:
    nums = {1};

    solutions.nextPermutation(nums);

    expected = {1};

    EXPECT_EQ(expected, nums);
}

TEST(X86_64Test, combinationSum2Check) {
    purgatory::Purgatory solutions;

    // Basic Case:
    vector<int> candidates = {10, 1, 2, 7, 6, 1, 5};

    int target = 8;

    vector<vector<int>> expected = {{1, 1, 6}, {1, 2, 5}, {1, 7}, {2, 6}};

    EXPECT_EQ(expected, solutions.combinationSum2(candidates, target));

    // Edge Case:
    candidates = {};

    target = 0;

    expected = {{}};

    EXPECT_EQ(expected, solutions.combinationSum2(candidates, target));
}

TEST(X86_64Test, solveSudokuCheck) {
    purgatory::Purgatory solutions;

    // Basic Case:
    vector<vector<char>> board = {{'5', '3', '.', '.', '7', '.', '.', '.', '.'}, 
	    {'6', '.', '.', '1', '9', '5', '.', '.', '.'},
            {'.', '9', '8', '.', '.', '.', '.', '6', '.'},
            {'8', '.', '.', '.', '6', '.', '.', '.', '3'},
	    {'4', '.', '.', '8', '.', '3', '.', '.', '1'},
            {'7', '.', '.', '.', '2', '.', '.', '.', '6'},
	    {'.', '6', '.', '.', '.', '.', '2', '8', '.'},
	    {'.', '.', '.', '4', '1', '9', '.', '.', '5'},
	    {'.', '.', '.', '.', '8', '.', '.', '7', '9'}};

    vector<vector<char>> expected = {{'5', '3', '4', '6', '7', '8', '9', '1', '2'}, 
	    {'6', '7', '2', '1', '9', '5', '3', '4', '8'},
            {'1', '9', '8', '3', '4', '2', '5', '6', '7'},
            {'8', '5', '9', '7', '6', '1', '4', '2', '3'},
	    {'4', '2', '6', '8', '5', '3', '7', '9', '1'},
            {'7', '1', '3', '9', '2', '4', '8', '5', '6'},
	    {'9', '6', '1', '5', '3', '7', '2', '8', '4'},
	    {'2', '8', '7', '4', '1', '9', '6', '3', '5'},
	    {'3', '4', '5', '2', '8', '6', '1', '7', '9'}};

    solutions.solveSudoku(board);

    EXPECT_EQ(expected, board);

}

TEST(X86_64Test, getEncryptedStringCheck) {
    purgatory::Purgatory solutions;

    // Basic Case:
    string s = "zyxw";

    string expected = "wxyz";

    EXPECT_EQ(expected, solutions.getEncryptedString(s));

    // Edge Case:
    s = "vgxgpu";

    expected = "ggpuxv";

    EXPECT_EQ(expected, solutions.getEncryptedString(s));
}

TEST(X86_64Test, hasCycleCheck) {
    purgatory::Purgatory solutions;

    // Basic Case:
    vector<int> head = {3, 2, 0, -4};
    int pos = 1;

    bool expected = true;

    EXPECT_EQ(expected, solutions.hasCycle(purgatory::buildLinkedList(head, pos)));

    // Edge Case:
    head = {1};
    pos = -1;

    expected = false;

    EXPECT_EQ(expected, solutions.hasCycle(purgatory::buildLinkedList(head, pos)));
}

TEST(X86_64Test, addTwoNumberCheck) {
    purgatory::Purgatory solutions;

    // Basic Case:
    vector<int> l1 = {2, 4, 3}, l2 = {5, 6, 4};

    vector<int> result = purgatory::toVector(solutions.addTwoNumber(purgatory::buildLinkedList(l1), purgatory::buildLinkedList(l2)));

    vector<int> expected = {7, 0, 8};

    EXPECT_EQ(expected, result);

    // Edge Case:
    l1 = {0}, l2 = {0};

    result = purgatory::toVector(solutions.addTwoNumber(purgatory::buildLinkedList(l1), purgatory::buildLinkedList(l2)));

    expected = {0};

    EXPECT_EQ(expected, result);
}

TEST(X86_64Test, removeNthFromEndCheck) {
    purgatory::Purgatory solutions;

    // Basic Case:
    vector<int> head = {1, 2, 3, 4, 5};
    int n = 2;

    vector<int> result = purgatory::toVector(solutions.removeNthFromEnd(purgatory::buildLinkedList(head), n));

    vector<int> expected = {1, 2, 3, 5};

    EXPECT_EQ(expected, result);

    // Edge Case:
    head = {1, 2}; n = 1;

    result = purgatory::toVector(solutions.removeNthFromEnd(purgatory::buildLinkedList(head), n));

    expected = {1};
   
    EXPECT_EQ(expected, result);
}

TEST(X86_64Test, reverseKGroupCheck) {
    purgatory::Purgatory solutions;

    // Basic Case:
    vector<int> head = {1, 2, 3, 4, 5};
    int k = 2;

    vector<int> result = purgatory::toVector(solutions.reverseKGroup(purgatory::buildLinkedList(head), k)); 

    vector<int> expected = {2, 1, 4, 3, 5};

    EXPECT_EQ(expected, result);

    // Edge Case:
    head = {1}; k = 1;

    result = purgatory::toVector(solutions.reverseKGroup(purgatory::buildLinkedList(head), k)); 

    expected = {1};

    EXPECT_EQ(expected, result);
}

#elif PURGATORY_ARM64LE

TEST(ARM64LETest, BasicCheck) {
	EXPECT_EQ(1 + 1, 2);
}

TEST(ARM64LETest, TextQueryCheck) {
    using namespace query;

    ifstream fin("test.txt");
    TextQuery text(fin);

    Query q = Query("hair") & Query("Alice");

    QueryResult result = q.eval(text);

    string expected = "(hair & Alice) occurs 1 time\n\t(line 1) Alice Emma has long flowing red hair.\n";

    EXPECT_EQ(expected, printToString(result));
}

#elif PURGATORY_I386

TEST(I386Test, BasicCheck) {
	EXPECT_EQ(1 + 1, 2);
}
#endif
