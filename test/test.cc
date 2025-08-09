#include <gtest/gtest.h>
#include "purgatory.h"

#ifdef PURGATORY_X86_64

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

#elif PURGATORY_ARM64LE

TEST(ARM64LETest, BasicCheck) {
	EXPECT_EQ(1 + 1, 2);
}
#elif PURGATORY_I386

TEST(I386Test, BasicCheck) {
	EXPECT_EQ(1 + 1, 2);
}
#endif
