#include "purgatory.h"

namespace purgatory {

/*
 *  using frequency array here because we can break the problem into how many times each letter is available
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
 */
int Purgatory::longestConsecutive(vector<int> & nums) {
    unordered_set<int> numSet(nums.begin(), nums.end());
    int longest = 0;

    for (int num : nums) {
        if (!numSet.count(num - 1)) {
            int currentNum = num;
	    int currentSteak = 1;

	    while (numSet.count(currentNum + 1)) {
                currentNum++;
		currentSteak++;
	    }

	    longest = max(longest, currentSteak);
	}
    }

    return longest;
}

/*
 *  using sliding window here because we can break the problem into checking fixed-length segments
 */
vector<int> Purgatory::findSubstring(string s, vector<string>& words) {
    unordered_map<string, int> wordCount;
    int wordLen = words[0].size();
    int numWords = words.size();
    vector<int> result;

    for(string & word : words) ++wordCount[word];

    for (int i = 0; i < wordLen; ++i) {
        int left = i, count = 0;
	unordered_map<string, int> seen;

        for (int j = i; j + wordLen < s.size(); j+= wordLen) {
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
	    
		if ( count == numWords ) result.push_back(left);
	    } else {
		    seen.clear();
                    count = 0;
		    left = j + wordLen;
	    }
	}
    }

    return result;
}

}
