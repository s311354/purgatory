#ifndef PURGATORY_H
#define PURGATORY_H

#include <iostream>
using namespace std;

// STL Containers
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>

#include <string_view>
#include <climits>
#include <algorithm>

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
};

template <typename E>
int purgatory_main(int argc, char **argv);

} /* namespace purgatory */

#endif /* PURGATORY_H */
