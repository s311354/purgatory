#include "purgatory.h"

namespace purgatory {

/*
 *  using frequency array here because we can break the problem into how many
 * times each letter is available T: O(n), S: O(1)
 */
bool Purgatory::canConstruct(const string &ransomNot, const string &magazine) {
  if (ransomNot.size() > magazine.size())
    return false;

  int count[26] = {0};

  // register vs memory
  const char *p = magazine.data();
  const char *end = p + magazine.size();

  // cache behavior
  while (p != end) {
    ++count[*p++ - 'a'];
  }

  // register vs memory
  p = ransomNot.data();
  end = p + ransomNot.size();
  // cache behavior
  while (p != end) {
    if (--count[*p++ - 'a'] < 0)
      return false;
  }

  return true;
}

/*
 *  using hash map + sorting approach here because we can break the problem into
 *  - find a way to identify anagram groups -> use sorted string as group key
 *  - use a hash table to accumulate groups efficiently
 *  T: O(N * k log k), S: O(N*k)
 */
vector<vector<string>> Purgatory::groupAnagrams(vector<string> &strs) {
  unordered_map<string, vector<string>> groups;
  // cache behavior
  groups.reserve(strs.size());

  for (string &s : strs) {
    // cache behavior
    int freq[26] = {0};
    for (char &c : s) {
      freq[c - 'a']++;
    }

    // cache behavior
    string key(26, 0);
    for (int i = 0; i < 26; ++i)
      key[i] = freq[i];

    groups[key].push_back(move(s));
  }

  vector<vector<string>> result;
  result.reserve(groups.size());
  for (auto &entry : groups) {
    result.push_back(move(entry.second));
  }

  return result;
}

/*
 *  using hashSet-based algorithm here because we want
 *  - constant-time lookup
 *  - skip unnecessary checks by only starting from smallest elements
 *  T: O(n), S: O(n)
 */
int Purgatory::longestConsecutive(vector<int> &nums) {
  unordered_set<int> numSet;
  // cache behavior
  numSet.reserve(nums.size());
  numSet.insert(nums.begin(), nums.end());

  int longest = 0;

  for (int num : numSet) {
    if (num != INT_MIN && numSet.count(num - 1))
      continue;

    // register vs memory
    int currentNum = num;
    int length = 1;

    while (currentNum != INT_MAX && numSet.count(currentNum + 1)) {
      ++currentNum;
      ++length;
    }

    longest = max(longest, length);
  }

  return longest;
}

/*
 *  using sliding window here because we can break the problem into checking
 * fixed-length segments T: O(n), S: O(m)
 */
vector<int> Purgatory::findSubstring(const string &s, vector<string> &words) {
  vector<int> result;

  if (words.empty() || s.empty())
    return result;

  // register vs memory
  const size_t n = s.size();
  const size_t wordLen = words.front().size();
  const size_t numWords = words.size();

  if (wordLen == 0)
    return result;

  for (const auto &word : words) {
    if (word.size() != wordLen)
      return result;
  }

  if (numWords > (n / wordLen))
    return result;

  // cache behavior
  unordered_map<string, size_t> wordToId;
  wordToId.reserve(numWords);
  vector<size_t> targetFreq;
  targetFreq.reserve(numWords);

  for (const auto &w : words) {
    const auto entry = wordToId.emplace(w, targetFreq.size());

    if (entry.second)
      targetFreq.push_back(0);

    ++targetFreq[entry.first->second];
  }

  vector<size_t> seen(targetFreq.size(), 0);
  deque<size_t> window;
  string token(wordLen, '\0');

  const size_t lastStart = n - numWords * wordLen;

  for (size_t offset = 0; offset < wordLen && offset <= lastStart; ++offset) {
    int left = offset;

    const auto popLeft = [&]() {
      --seen[window.front()];
      window.pop_front();
      left += wordLen;
    };

    for (size_t right = offset; right + wordLen <= n; right += wordLen) {
      // cpu pipeline
      memcpy(&token[0], s.data() + right, wordLen);

      auto it = wordToId.find(token);
      if (it == wordToId.end()) {
        while (!window.empty())
          popLeft();

        left = right + wordLen;
        continue;
      }

      size_t wid = it->second;
      window.push_back(wid);
      ++seen[wid];

      while (seen[wid] > targetFreq[wid]) {
        popLeft();
      }

      if (window.size() == numWords) {
        result.push_back(static_cast<int>(left));
        popLeft();
      }
    }

    while (!window.empty()) {
      popLeft();
    }
  }

  return result;
}

/*
 *  using a hash-set approach here because we can break the problem into a
 * membership detection. T: O(n), S: O(n)
 */
bool Purgatory::containsDuplicate(const vector<int> &nums) {
  const size_t n = nums.size();
  if (n < 2)
    return false;

  unordered_set<int> seen;
  seen.reserve(n);

  for (const auto &x : nums) {
    if (!seen.insert(x).second)
      return true;
  }

  return false;
}

/*
 *  using a hash map to record remainders here because we can break the problem
 * into
 *  - handling sign and integer division
 *  - generating fractional digits while tracking remainders
 *  - detecting repetition to insert parentheses
 *  T: O(k), S: O(k)
 */
string Purgatory::fractionToDecimal(int numerator, int denominator) {
  if (denominator == 0)
    return "0"; // or throw exception
  if (numerator == 0)
    return "0";

  long long n = numerator;
  long long d = denominator;

  string result;
  // cache behavior
  result.reserve(128);

  if ((n < 0) != (d < 0))
    // function call
    result.push_back('-');

  if (d < 0)
    d = -d;

  if (n < 0)
    n = -n;

  result += to_string(n / d);

  long long remainder = n % d;

  if (remainder == 0)
    return result;

  result.push_back('.');

  unordered_map<long long, string::size_type> seen;
  // cahce behavior
  seen.reserve(1024);

  while (remainder != 0) {
    const auto entry = seen.emplace(remainder, result.size());

    if (!entry.second) {
      result.insert(entry.first->second, 1, '(');
      result.push_back(')');
      return result;
    }

    const long long scaled = remainder * 10;
    const int digit = static_cast<int>(scaled / d);

    remainder = scaled % d;
    result.push_back(static_cast<char>('0' + digit));
  }

  return result;
}

/*
 *  using index mapping here because we can break the problem into an implicit
 * hash. The state we define is: each index I should ideally hold i + 1. The
 * first index that breaks this invariant gives the missing positive. T: O(n),
 * S: O(1)
 */
int Purgatory::firstMissingPositive(vector<int> &nums) {
  const int n = nums.size();

  for (int i = 0; i < n; ++i) {
    // cpu pipeline
    for (;;) {
      // register vs memory
      const int val = nums[i];

      if (val <= 0 || val > n)
        break;

      // register vs memory
      const int target = val - 1;
      const int correct = nums[target];

      if (correct == val)
        break;

      nums[target] = val;
      nums[i] = correct;
    }
  }

  for (int i = 0; i < n; ++i) {
    if (nums[i] != i + 1) {
      return i + 1;
    }
  }

  return n + 1;
}

vector<int> Purgatory::intersection(vector<int> &nums1, vector<int> &nums2) {
  vector<int> result;

  if (nums1.empty() || nums2.empty())
    return result;

  sort(nums1.begin(), nums1.end());
  sort(nums2.begin(), nums2.end());

  size_t i = 0, j = 0;

  // register vs memory
  size_t n1 = nums1.size(), n2 = nums2.size();

  while (i < n1 && j < n2) {
    // register vs memory
    const int a = nums1[i];
    const int b = nums2[j];

    if (a == b) {
      if (result.empty() || result.back() != a) {
        result.push_back(a);
      }

      ++i;
      ++j;
    } else if (a < b) {
      ++i;
    } else {
      ++j;
    }
  }

  return result;
}

vector<int> Purgatory::majorityElement(const vector<int> &nums) {
  int candidate1 = 0, candidate2 = 0;
  size_t count1 = 0, count2 = 0;

  for (int num : nums) {
    // branch prediction
    if (num == candidate1) {
      ++count1;
    } else if (num == candidate2) {
      ++count2;
    } else if (count1 == 0) {
      candidate1 = num;
      count1 = 1;
    } else if (count2 == 0) {
      candidate2 = num;
      count2 = 1;
    } else {
      --count1;
      --count2;
    }
  }

  count1 = count2 = 0;
  for (int num : nums) {
    if (num == candidate1)
      ++count1;
    else if (num == candidate2)
      ++count2;
  }

  vector<int> result;
  int n = nums.size();
  size_t threshold = n / 3;

  if (count1 > threshold)
    result.push_back(candidate1);

  if (count2 > threshold)
    result.push_back(candidate2);

  return result;
}

string Purgatory::getHint(const string &secret, const string &guess) {
  int bulls = 0, cows = 0;
  int balance[10] = {0};

  size_t n = secret.size();

  for (size_t i = 0; i < n; ++i) {
    // cpu pipeline
    const int si = secret[i] - '0';
    const int gi = guess[i] - '0';

    if (si == gi) {
      ++bulls;
      continue;
    }

    const int secretBalance = balance[si];
    const int guessBalance = balance[gi];

    // branch prediction
    cows += (secretBalance < 0) + (guessBalance > 0);

    balance[si] = secretBalance + 1;
    balance[gi] = guessBalance - 1;
  }

  return to_string(bulls) + 'A' + to_string(cows) + 'B';
}

int Purgatory::numberOfBoomeranges(const vector<vector<int>> &points) {
  int n = points.size();
  int total = 0;

  for (int i = 0; i < n; ++i) {
    // cache behavior
    unordered_map<int, int> distCount;
    distCount.reserve(n);

    for (int j = 0; j < n; ++j) {
      if (i == j)
        continue;

      int dx = points[i][0] - points[j][0];
      int dy = points[i][1] - points[j][1];

      int dist = dx * dx + dy * dy;

      // cpu pipeline
      total += 2 * distCount[dist];
      ++distCount[dist];
    }
  }

  return total;
}

char Purgatory::findTheDifference(string s, string t) {
  char xor_result = 0;
  int n = s.size();

  // cahce behavior
  for (int i = 0; i < n; ++i) {
    xor_result ^= s[i];
    xor_result ^= t[i];
  }

  xor_result ^= t[n];

  return xor_result;
}

vector<int> Purgatory::findAnagrams(string s, string p) {
  vector<int> result;

  // cache behavior
  int freq[26] = {0};

  for (char c : p)
    freq[c - 'a']++;

  int count = p.size();
  int ns = s.size(), np = p.size();

  for (int r = 0, l = 0; r < ns; ++r) {

    // branch prediction
    if (freq[s[r] - 'a']-- > 0)
      count--;

    if (r - l + 1 > np) {
      if (++freq[s[l] - 'a'] > 0)
        count++;

      l++;
    }

    if (count == 0)
      result.push_back(l);
  }

  return result;
}

int Purgatory::subarraySum(const vector<int> &nums, int k) {
  // cache behavior
  unordered_map<int, int> prefixCount;
  prefixCount.reserve(nums.size());

  prefixCount[0] = 1;

  int currentSum = 0;
  int result = 0;

  for (int num : nums) {
    currentSum += num;

    // branch prediction
    auto it = prefixCount.find(currentSum - k);
    if (it != prefixCount.end()) {
      result += it->second;
    }

    prefixCount[currentSum]++;
  }

  return result;
}

string Purgatory::longestWord(vector<string> &words) {
  sort(words.begin(), words.end());

  // cache behavior
  unordered_set<string> valid;
  valid.reserve(words.size());
  string result = "";

  for (const string &word : words) {
    // branch prediction
    bool canBuild = false;

    if (word.size() == 1) {
      canBuild = true;
    } else {
      // cache behavior
      string prefix = word;
      prefix.pop_back();
      if (valid.count(prefix)) {
        canBuild = true;
      }
    }

    if (canBuild) {
      valid.insert(word);
      if (word.size() > result.size()) {
        result = word;
      }
    }
  }

  return result;
}

int Purgatory::deleteAndEarn(const vector<int> &nums) {
  // cache behavior
  int sum[10001] = {0};
  int maxVal = 0;

  for (int num : nums) {
    sum[num] += num;
    if (num > maxVal)
      maxVal = num;
  }

  int prev2 = 0, prev1 = 0;

  for (int i = 0; i <= maxVal; ++i) {
    // branch prediction
    int curr = prev1 > (prev2 + sum[i]) ? prev1 : (prev2 + sum[i]);

    prev2 = prev1;
    prev1 = curr;
  }

  return prev1;
}

// cache behavior
struct TrieNode {
  TrieNode *children[26] = {};
};

int Purgatory::minimumLengthEncoding(vector<string> &words) {
  sort(words.begin(), words.end(),
       [](const string &a, const string &b) { return a.size() > b.size(); });

  TrieNode *root = new TrieNode();
  int totalLength = 0;

  for (const string &word : words) {
    // register vs memory
    TrieNode *node = root;
    bool isNew = false;

    // cpu pipeline
    for (int i = word.size() - 1; i >= 0; --i) {
      // register vs memory
      int idx = word[i] - 'a';

      // branch prediction
      if (!node->children[idx]) {
        node->children[idx] = new TrieNode();
        isNew = true;
      }

      node = node->children[idx];
    }

    if (isNew)
      totalLength += word.size() + 1;
  }

  return totalLength;
}

vector<string> Purgatory::wordSubsets(const vector<string> &words1,
                                      const vector<string> &word2) {
  // cache behavior
  int maxFreq[26] = {0};

  for (const string &b : word2) {
    int freq[26] = {0};

    for (char c : b)
      freq[c - 'a']++;

    for (int i = 0; i < 26; ++i)
      // branch prediction
      if (freq[i] > maxFreq[i])
        maxFreq[i] = freq[i];
  }

  // cache behavior
  vector<string> result;
  result.reserve(words1.size());

  for (const string &a : words1) {
    // cache behavior
    int freq[26] = {0};

    for (char c : a)
      freq[c - 'a']++;

    bool isValid = true;

    for (int i = 0; i < 26; ++i) {
      if (freq[i] < maxFreq[i]) {
        isValid = false;
        break;
      }
    }
    if (isValid)
      result.push_back(a);
  }

  return result;
}

vector<int> Purgatory::findErrorNums(const vector<int> &nums) {
  int n = nums.size();
  vector<int> freq(n + 1, 0);

  for (const int value : nums) {
    ++freq[value];
  }

  // cache behavior
  vector<int> result(2);
  for (int i = 1; i <= n; ++i) {
    if (freq[i] == 2)
      result[0] = i;
    if (freq[i] == 0)
      result[1] = i;
  }

  return result;
}

int Purgatory::longestPalindrome(string s) {
  // cache behavior
  int freq[128] = {0};
  for (const char c : s) {
    freq[c]++;
  }

  int result = 0;
  for (int i = 0; i < 128; i++) {
    result += (freq[i] >> 1) << 1;
  }

  if (result < s.size())
    ++result;

  return result;
}

int Purgatory::findMaxLength(const vector<int> &nums) {
  int n = nums.size();
  // cache behavior
  vector<int> findIndex((n << 1) + 1, -2);

  int prefixSum = 0;
  int result = 0;

  int offset = n;
  findIndex[offset] = -1;

  for (int i = 0; i < n; ++i) {
    prefixSum += (nums[i] == 1 ? 1 : -1);

    int idx = prefixSum + offset;

    if (findIndex[idx] != -2) {
      result = max(result, i - findIndex[idx]);
    } else {
      findIndex[idx] = i;
    }
  }
  return result;
}

vector<int> Purgatory::fairCandySwap(const vector<int> &aliceSizes,
                                     const vector<int> &bobSizes) {
  int sumA = 0, sumB = 0;

  unordered_set<int> set;
  // cache behavior
  set.reserve(bobSizes.size() << 1);

  for (const int a : aliceSizes)
    sumA += a;
  for (const int b : bobSizes) {
    sumB += b;
    set.insert(b);
  }

  int diff = (sumA - sumB) >> 1;

  for (const int a : aliceSizes) {
    // register vs memory
    int b = a - diff;

    // cache behavior
    if (set.find(b) != set.end())
      return {a, b};
  }

  return {};
}

bool Purgatory::checkSubarraySum(const vector<int> &nums, int k) {
  int n = nums.size();

  if (n < 2)
    return false;

  unordered_map<int, int> mp;
  // cache behavior
  mp.reserve(n);
  mp[0] = -1;

  int sum = 0;
  for (int i = 0; i < n; ++i) {
    sum += nums[i];

    int mod = (k == 0) ? sum : sum % k;

    // cahce behavior
    auto it = mp.find(mod);
    if (it != mp.end()) {
      if (i - it->second >= 2)
        return true;
    } else {
      mp[mod] = i;
    }
  }

  return false;
}

vector<vector<string>> Purgatory::findDuplicate(vector<string> &paths) {
  unordered_map<string, vector<string>> buckets;
  // cache behavior
  buckets.reserve(paths.size() << 2);

  for (string &path : paths) {
    // cpu pipeline
    int i = 0, n = path.size();

    while (i < n && path[i] != ' ')
      ++i;
    string dir = path.substr(0, i);

    ++i;
    while (i < n) {
      int start = i;
      while (i < n && path[i] != '(')
        ++i;
      string file = path.substr(start, i - start);

      ++i;
      int contentStart = i;
      while (i < n && path[i] != ')')
        ++i;
      string content = path.substr(contentStart, i - contentStart);

      ++i;
      if (i < n && path[i] == ' ')
        ++i;

      buckets[content].push_back({dir + '/' + file});
    }
  }

  vector<vector<string>> result;

  for (auto &bucket : buckets) {
    if (bucket.second.size() > 1)
      result.push_back(move(bucket.second));
  }

  return result;
}

} // namespace purgatory
