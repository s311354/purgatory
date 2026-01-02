#include "purgatory.h"

namespace purgatory {

/*
 *  using frequency array here because we can break the problem into how many times each letter is available
 *  T: O(n), S: O(1)
 */
bool Purgatory::canConstruct(string rasomNote, string magazine) {
    int count[26] = {0};

    for (char c : magazine) {
        ++count[c - 'a'];
    }

    for (char c : rasomNote) {
        if(--count[c - 'a'] < 0) return false;
    }

    return true;
}

/*
 *  using hash map + sorting approach here because we can break the problem into
 *  - find a way to identify anagram groups -> use sorted string as group key
 *  - use a hash table to accumulate groups efficiently
 *  T: O(N * k log k), S: O(N*k)
 */
vector<vector<string>> Purgatory::groupAnagrams(vector<string> & strs) {
    unordered_map<string, vector<string>> groups;
    vector<vector<string>> result;

    for (string s : strs) {
        string key = s;
	sort(key.begin(), key.end());
	groups[key].push_back(s);
    }

    for (auto & entry: groups) {
        result.push_back(entry.second);
    }

    return result;
}

/*
 *  using hashSet-based algorithm here because we want 
 *  - constant-time lookup
 *  - skip unnecessary checks by only starting from smallest elements
 *  T: O(n), S: O(n)
 */
int Purgatory::longestConsecutive(vector<int> & nums) {
    unordered_set<int> numSet(nums.begin(), nums.end());
    int longest = 0;

    for (int num : numSet) {
        if (!numSet.count(num - 1)) {
            int currentNum = num;
	    int currentSteak = 1;

	    while (numSet.count(currentNum + 1)) {
                currentNum += 1;
		currentSteak += 1;
	    }

	    longest = max(longest, currentSteak);
	}
    }

    return longest;
}

/*
 *  using sliding window here because we can break the problem into checking fixed-length segments
 *  T: O(n), S: O(m)
 */
vector<int> Purgatory::findSubstring(string s, vector<string>& words) {
    vector<int> result;

    if (words.empty() || s.empty()) return result;

    unordered_map<string, int> wordCount;
    int wordLen = words[0].size();
    int numWords = words.size();

    for(string & word : words) ++wordCount[word];

    for (int i = 0; i < wordLen; ++i) {
        int left = i, count = 0;
	unordered_map<string, int> seen;

        for (int j = i; j + wordLen <= s.size(); j+= wordLen) {
            string word = s.substr(j, wordLen);

	    if (wordCount.count(word)) {
                ++seen[word];
		++count;

		while(seen[word] > wordCount[word]) {
		    string leftWord = s.substr(left, wordLen);
		    --seen[leftWord];
		    --count;
		    left += wordLen;

		}
	    
		if ( count == numWords )
		    result.push_back(left);

	    } else {
		    seen.clear();
                    count = 0;
		    left = j + wordLen;
	    }
	}
    }

    return result;
}

/*
 *  using a hash-set approach here because we can break the problem into a membership detection.
 *  T: O(n), S: O(n)
 */
bool Purgatory::containsDuplicate(vector<int>& nums) {
    unordered_set<int> seen;

    for (int x: nums) {
        if (seen.count(x)) {
            return true;
	}

	seen.insert(x);
    }

    return false;
}

/*
 *  using a hash map to record remainders here because we can break the problem into
 *  - handling sign and integer division
 *  - generating fractional digits while tracking remainders
 *  - detecting repetition to insert parentheses
 *  T: O(k), S: O(k)
 */
string Purgatory::fractionToDecimal(int numerator, int denominator) {
    if (numerator == 0) return "0";

    string result;

    if ((numerator < 0) ^ (denominator < 0)) result += '-';

    long long n = llabs((long long) numerator);
    long long d = llabs((long long) denominator);

    result += to_string(n/d);

    long long remainder = n % d;

    if (remainder == 0) return result;

    result += '.';

    unordered_map<long long, int> seen;

    while (remainder) {
        if (seen.count(remainder)) {
            result.insert(seen[remainder], "(");
	    result += ')';
	    break;
	}

	seen[remainder] = result.size();
	remainder *= 10;
	result += to_string(remainder/d);
	remainder %= d;
    }

    return result;
}

/*
 *  using index mapping here because we can break the problem into an implicit hash. The state we define is: each index I should ideally hold i + 1. The first index that breaks this invariant gives the missing positive.
 *  T: O(n), S: O(1)
 */
int Purgatory::firstMissingPositive(vector<int>& nums) {
    int n = nums.size();

    for (int i = 0; i < n; ++i) {
        while (nums[i] > 0 && nums[i] <= n && nums[nums[i]- 1] != nums[i]) {
	    swap(nums[i], nums[nums[i] - 1]);
	}
    }

    for (int i = 0; i < n; ++i) {
        if (nums[i] != i + 1) {
	    return i + 1;
	}
    }

    return n + 1;
}

}
