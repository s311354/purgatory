#ifndef PURGATORY_H
#define PURGATORY_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
using namespace std;

// STL Containers
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <set>
#include <stack>
#include <map>

#include <string_view>
#include <climits>
#include <algorithm>
#include <memory>
#include <numeric>
#include <bitset>
#include <cmath>

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

struct Node {
    int val;
    Node *left;
    Node *right;
    Node *next;

    Node() : val(0), left(nullptr), right(nullptr), next(nullptr) {}

    Node(int _val): val(_val), left(nullptr), right(nullptr), next(nullptr) {}

    Node(int _val, Node* _left, Node* _right, Node* _next) : val(_val), left(_left), right(_right), next(_next) {}
};

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x): val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

// Build tree from level-order vector with INT_MIN as null
TreeNode* buildTree(const vector<int>& arr);

// Build node from level-order vector
Node* buildNode(const vector<int>& arr); 

// Build linked list from level-order
ListNode* buildLinkedList(const vector<int>& values, int pos);
ListNode* buildLinkedList(const vector<int>& values);

// Convert connected node into vector
vector<int> serializeWithNext(Node* root);

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

    vector<vector<int>> generate(int numRows);

    void nextPermutation(vector<int> &nums);

    vector<vector<int>> combinationSum2(vector<int>& candidates, int target);

    void solveSudoku(vector<vector<char>>& board);

    string getEncryptedString(string s, int k);

    int arrayPairSum(vector<int> &nums);

    int maxProduct(vector<string> &words);

    vector<int> largestDivisibleSubset(vector<int> &nums);

    int distributeCandies(vector<int> &candyType);

    int maxRotateFunction(vector<int> &nums);

    vector<int> findRightInterval(vector<vector<int>> &intervals);

    string largestNumber(vector<int> &nums);

    int minimumPairRemoval(vector<int> &nums);

    vector<vector<int>> matrixReshape(vector<vector<int>> &mat, int r, int c);

    int arrayNesting(vector<int> &nums);

    int maximumProduct(vector<int>& nums);

    bool isPossbile(vector<int> &nums);

    bool canPartitionKSubsets(vector<int> &nums, int k);

    // hashmap
    bool canConstruct(string ransomNot, string magazine);

    vector<vector<string>> groupAnagrams (vector<string>& strs);

    int longestConsecutive(vector<int> &nums);

    vector<int> findSubstring(string s, vector<string>& words);

    bool containsDuplicate(vector<int>& nums);

    string fractionToDecimal(int numerator, int denominator);

    int firstMissingPositive(vector<int>& nums);

    vector<int> intersection(vector<int>& nums1, vector<int> &nums2);

    vector<int> majorityElement(vector<int> &nums);

    string getHint(string &secret, string &guess);

    int numberOfBoomeranges(vector<vector<int>> &points);

    char findTheDifference(string s, string t);

    vector<int> findAnagrams(string s, string p);

    int subarraySum(vector<int>& nums, int k);

    string longestWord(vector<string> &words);

    int deleteAndEarn(vector<int> &nums);

    int minimumLengthEncoding(vector<string> &words);

    vector<string> wordSubsets(vector<string> &words1, vector<string> &word2);

    vector<int> findErrorNums(vector<int> &nums);

    int longestPalindrome(string s);

    int findMaxLength(vector<int> &nums);

    vector<int> fairCandySwap(vector<int> &aliceSizes, vector<int> &bobSizes);

    bool checkSubarraySum(vector<int> &nums, int k);

    vector<vector<string>> findDuplicate(vector<string> &paths);

    vector<int> findDisappearedNumber(vector<int> &nums);

    int minMoves(vector<int> &nums);

    bool makesquare(vector<int> &matchsticks);

    int findTargetSumWays(vector<int> &nums, int target);

    vector<string> findRestaurant(vector<string> &list1, vector<string> &list2);

    int countPrimes(int n);

    int wiggleMaxLength(vector<int> &nums);

    vector<int> findDuplicates(vector<int> &nums);

    // two pointers
    bool isPalindrome(string s); 
    
    vector<int> twoSum(vector<int> & numbers, int target);

    int maxArea(vector<int> & height);

    int trap(vector<int> & height);

    void reverseString(vector<char>& s);

    void sortColors(vector<int>& nums);

    int compareVersion(string version1, string version2);

    vector<int> maxNumber(vector<int>& nums1, vector<int>& nums2, int k);

    int findContentChildren(vector<int> &g, vector<int> &s);

    int magicalString(int n);

    bool checkInclusion(string s1, string s2);

    bool judgeSquareSum(int c);

    int removePalindromeSub(string s);

    int findRadius(vector<int> &house, vector<int> &heaters);

    bool circularArrayLoop(vector<int> &nums);

    int maxProfitAssignment(vector<int> &difficulty, vector<int> &profit, vector<int> &worker);

    int countBinarySubstrings(string s);

    int countSubstrings(string s);

    int longestMountain(vector<int> &arr);

    string reverseStr(string s, int k);

    vector<int> shortestToChar(string s, char c);

    int rangeSum(vector<int> &nums, int n, int left, int right);

    string addSpaces(string s, vector<int> &spaces);

    long long minimumSteps(string s);

    int getCommon(vector<int> &nums1, vector<int> &nums2);

    int numFriendRequests(vector<int> &ages);

    string reverseOnlyLetters(string s);

    int numRescueBoats(vector<int> &people, int limit);

    int waysToSplit(vector<int> &nums);

    vector<int> applyOperations(vector<int> &nums);


    // sliding window
    bool containsNearbyDuplicate(vector<int>& nums, int k);

    int minSubArrayLen(int target, vector<int>& nums);

    int lengthOfLongestSubstring(string s);

    string longestNiceSubstring(string s);

    int longestSubstring(string s, int k);

    int numberOfArithmeticSlices(vector<int>& nums);

    vector<double> medianSlidingWindow(vector<int>& nums, int k);

    int minimumSumSubarray(vector<int> &nums, int l, int r);

    int numSubarraysWithSum(vector<int> &nums, int goal);

    int maxLength(vector<int> &nums);

    int characterReplacement(string s, int k);

    int numSubarrayProductLessThanK(vector<int> &nums, int k);

    int totalFruit(vector<int> &fruits);

    int numberOfAlternatingGroups(vector<int> &colors);

    int findLength(vector<int> &nums1, vector<int> &nums2);

    int maxSatisfied(vector<int> &customers, vector<int> &grumpy, int minutes);

    int countKConstraintSubstrings(string s, int k);

    int maxTurbulenceSize(vector<int> &arr);

    int numberOfSubarrays(vector<int> &nums, int k);

    int maximumUniqueSubarray(vector<int> &nums);



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

    vector<int> inorderTraversal(TreeNode *root);

    int numTrees(int n);

    vector<int> findFrequentTreeSum(TreeNode *root);

    int maxAncestorDiff(TreeNode *root);

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

    vector<int> nextGreaterElement(vector<int>& nums1, vector<int>& nums2);

    string removeDuplicateLetters(string s);

    int calculateII(string s);

    int longestValidParentheses(string s);

    bool backspaceCompare(string s, string t);

    int findUnsortedSubarray(vector<int>& nums);

    int carFleet(int target, vector<int>& position, vector<int>& speed);

    int sumSubarrayMins(vector<int>& arr);

    string removeOccurrences(string s, string part);

    int maximumGain(string s, int x, int y);

    int addMinimum(string word);

    long long calculateScore(string s);

    int minLengthAfterRemovals(string s);

    int minLength(string s);

    vector<int> exclusiveTime(int n, vector<string> &logs);

    vector<string> buildArray(vector<int> &target, int n);

    long long subArrayRanges(vector<int> &nums);

    string makeGood(string s);

    string reversePrefix(string word, char ch);

    bool checkValidString(string s);

    string removeDuplicates(string s);

    bool find132pattern(vector<int> &nums);

    int maxWidthRamp(vector<int> & nums);

    string clearDigits(string s);

    bool validateStackSequences(vector<int> &pushed, vector<int> &popped);

    string minRemoveToMakeValid(string s);

    int totalSteps(vector<int> &nums);

    int minOperations(vector<string> &logs);

    int scoreOfParentheses(string s);

    int maximumPossibleSize(vector<int> &nums);

    vector<int> preorderTraversal(TreeNode *root);

    int maxBalanceShipments(vector<int> &weight);

    long long bowlSubarrays(vector<int> &nums);

    vector<long long> mergeAdjacent(vector<int> &nums);

    vector<int> postorderTraversal(TreeNode *root);

    string decodeAtIndex(string s, int k);

    bool isValidString(string s);

    // graph bfs
    vector<vector<int>> levelOrderBottom(TreeNode* root); 

    int minDepth(TreeNode *root);

    Node* connect(Node* root);

    vector<string> removeInvalidParentheses(string s);

    int sumOfLeftLeaves(TreeNode* root);

    int numSquares(int n);

    bool canMeasureWater(int x, int y, int target);

    vector<vector<string>> findLadders(string beginWord, string endWord, vector<string>& wordList);

    // graph
    int findJudge(int n, vector<vector<int>>& trust);

    int numIslands(vector<vector<char>>& grid);

    void solve(vector<vector<char>>& board);

    int longestIncreasingPath(vector<vector<int>>& matrix);

    int findCenter(vector<vector<int>>& edges);

    bool isBipartite(vector<vector<int>>& graph);

    int numberOfComponents(vector<vector<int>>& properties, int k);

    // heap
    int lastStoneWeight(vector<int>& stones);
    
    int nthUglyNumber(int n);

    vector<int> topKFrequent(vector<int>& nums, int k);

    vector<int> maxSlidingWindow(vector<int>& nums, int k);

    int maxProduct(vector<int> &nums);

    string frequencySort(string s);

    vector<int> rearrangeBarcodes(vector<int> &barcodes);

    int furthestBuilding(vector<int> &heights, int bricks, int ladders);

    vector<int> assignTasks(vector<int> &servers, vector<int> &tasks);

    vector<int> numberGame(vector<int> &nums);

    int networkDelayTime(vector<vector<int>> &times, int n, int k);

    int minSetSize(vector<int> &arr);

    int deleteGreatestValue(vector<vector<int>> &grid);

    string longestDiverseString(int a, int b, int c);

    int minimumEffortPath(vector<vector<int>> &heights);

    long long pickGifts(vector<int> &gifts, int k);

    vector<int> getOrder(vector<vector<int>> &tasks);

    // intervals
    vector<string> summaryRanges(vector<int>& nums);

    vector<vector<int>> merge(vector<vector<int>> &intervals);

    vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval);

    int findMinArrowShots(vector<vector<int>> & points);

    // dp
    int climbStairs(int n);

    int rob(vector<int>& nums);

    bool wordBreak(string s, vector<string>& wordDict);

    bool isMatch(string s, string p);

    // backtracking
    vector<string> binaryTreePaths(TreeNode* root);

    vector<string> letterCombinations(string digits);

    vector<vector<int>> combine(int n, int k);

    int totalNQueens(int n);

    vector<string> readBinaryWatch(int turnedOn);

    vector<vector<int>> subsets(vector<int>& nums);
 
    vector<int> grayCode(int n);

    bool judgePoint24(vector<int>& cards); 

    vector<vector<int>> findSubsequences(vector<int> &nums);

    // binary search
    int searchInsert(vector<int>& nums, int target);

    bool searchMatric(vector<vector<int>>& matrix, int target);

    int findPeakElement(vector<int>& nums);

    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2);

    int missingNumber(vector<int>& nums);

    int findDuplicate(vector<int>& nums);

    bool search(vector<int>& nums, int target);

    int findMin(vector<int>& nums);

    // linked list
    bool hasCycle(ListNode* head);

    ListNode* addTwoNumber(ListNode* l1, ListNode* l2);

    ListNode* removeNthFromEnd(ListNode* head, int n);

    ListNode* reverseKGroup(ListNode* head, int k);

    bool isPalindromeLinkedList(ListNode *head);

    ListNode *swapPairs(ListNode *head);

    ListNode* reorderList(ListNode *head);

    int numComponents(ListNode *head, vector<int> &nums);

    vector<int> nodesBetweenCriticalPoints(ListNode *head);

    ListNode *removeNodes(ListNode *head);

    ListNode *doubleIt(ListNode *head);

    ListNode *middleNode(ListNode *head);

    ListNode *mergeNodes(ListNode *head);

    ListNode *insertGreatestCommonDivisors(ListNode *head);

    ListNode *deleteDuplicates(ListNode *head);

    ListNode *mergeInBetween(ListNode *list1, int a, int b, ListNode *list2);

    ListNode *modifiedList(vector<int> &nums, ListNode *head);

    vector<int> nextLargerNodes(ListNode *head);

    ListNode *removeElements(ListNode *head, int val);

    ListNode *insertionSortList(ListNode *head);

    int getDecimalValue(ListNode *head);

    ListNode *reverseEvenLengthGroups(ListNode *head);

    // matrix
    int islandPerimeter(vector<vector<int>>& grid);

    int kthSmallest(vector<vector<int>>& matrix, int k);

    int countBattleships(vector<vector<char>>& board);

    int maximalRectangle(vector<vector<char>>& matrix);
};

template <typename E>
int purgatory_main(int argc, char **argv);

} /* namespace purgatory */

#endif /* PURGATORY_H */

