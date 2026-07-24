#include "purgatory.h"

namespace purgatory {

/*
 *  using unordered_map to store the last seen index of each value here because
 * this let me check O(1) time whether the current element has appeared within
 * distance k. T: O(n), S: O(n)
 */
bool Purgatory::containsNearbyDuplicate(const vector<int> &nums, int k) {
  unordered_map<int, int> lastIndex;
  // register vs memory
  int n = nums.size();
  // cache behavior
  lastIndex.reserve(n);

  for (int i = 0; i < n; ++i) {
    // register vs memory
    int value = nums[i];
    auto it = lastIndex.find(value);
    if (it != lastIndex.end()) {
      if (i - it->second <= k)
        return true;
      it->second = i;
    } else {
      lastIndex.emplace(value, i);
    }
  }

  return false;
}

/*
 *  using a sliding window approach here because all numbers are positive,
 * ensuring that once the sum exceeds the target, moving left forward will only
 * reduce the sum. T: O(n), S: O(1)
 */
int Purgatory::minSubArrayLen(int target, const vector<int> &nums) {
  int left = 0, sum = 0;
  int minLen = INT_MAX;

  // memory vs register
  int n = nums.size();
  for (int right = 0; right < n; ++right) {
    sum += nums[right];

    // branch prediction
    if (sum >= target) {
      do {
        // cpu pipeline
        int len = right - left + 1;
        if (len < minLen)
          minLen = len;
        sum -= nums[left++];
      } while (sum >= target);
    }
  }

  return minLen == INT_MAX ? 0 : minLen;
}

/*
 *  using a sliding window with a hash map to track the last scene index of each
 * character here because whenever a duplicate is found within the current
 * window, left jumps past its previous occurrence. This ensure we always have a
 * substring with unique characters. T: O(n), S: O(n, charset_size)
 */
int Purgatory::lengthOfLongestSubstring(const string &s) {
  // cache behavior
  int last[256];
  memset(last, -1, sizeof(last));

  int left = 0, maxLen = 0;

  for (int right = 0; right < s.size(); ++right) {
    unsigned char c = s[right];

    // register vs memory
    int prev = last[c];
    left = prev >= left ? prev + 1 : left;

    last[c] = right;
    // register vs memory
    int len = right - left + 1;
    maxLen = len > maxLen ? len : maxLen;
  }

  return maxLen;
}

/*
 *  using divide-and-conquer
 *  T: O(n log n), S: O(n)
 */
string solveLongestNiceSubstring(const string &s, int l, int r) {
  if (r - l < 2)
    return "";

  // cpu pipeline
  int lower = 0, upper = 0;
  for (int i = l; i < r; ++i) {
    if (islower(s[i]))
      lower |= 1 << (s[i] - 'a');
    else
      upper |= 1 << (s[i] - 'A');
  }

  int valid = lower & upper;

  for (int i = l; i < r; ++i) {
    char c = s[i];

    // branch prediction
    if (islower(c) && !(valid & (1 << (c - 'a'))) ||
        islower(c) && !(valid & (1 << (c - 'A')))) {
      // cache behavior
      string left = solveLongestNiceSubstring(s, l, i);
      string right = solveLongestNiceSubstring(s, i + 1, r);
      return left.size() >= right.size() ? left : right;
    }
  }

  return s.substr(l, r - l);
}

string Purgatory::longestNiceSubstring(const string &s) {
  return solveLongestNiceSubstring(s, 0, s.size());
}

/*
 *  using frequency-based divide pattern here because we can break the problem
 * into invalid characters as natural boundaries. T: O(n log n), S: O(n)
 */
int solveLongestSubstring(const string &s, int l, int r, int k) {
  if (r - l < k)
    return 0;

  // cache behavior
  int freq[26] = {0};

  for (int i = l; i < r; ++i)
    freq[s[i] - 'a']++;

  // cpu pipeline
  for (int i = l; i < r; ++i) {
    if (freq[s[i] - 'a'] < k) {
      int j = i + 1;

      while (j < r && freq[s[j] - 'a'] < k)
        ++j;

      return max(solveLongestSubstring(s, l, i, k),
                 solveLongestSubstring(s, j, r, k));
    }
  }

  return r - l;
}

int Purgatory::longestSubstring(const string &s, int k) {
  return solveLongestSubstring(s, 0, s.size(), k);
}

/*
 *  using recurrence dynamic idea here because we can break the problem into the
 * cumulative native of extending arithmetic subarrays. T: O(n), S: O(1)
 */
int Purgatory::numberOfArithmeticSlices(vector<int> &nums) {
  if (nums.size() < 3)
    return 0;

  int count = 0, current = 0;

  // cache behavior
  const int *p = nums.data();
  const int *end = p + nums.size();

  // register vs memory
  int prev = p[0];
  int curr = p[1];
  int prev_diff = curr - prev;

  for (p += 2; p < end; ++p) {
    int next = *p;
    int diff = next - curr;

    // branch prediction
    int same = (diff == prev_diff);
    current = same * (current + 1);
    count += current;

    prev_diff = diff;
    curr = next;
  }

  return count;
}

/*
 *  using multiset median-tracking approach here because we can break the
 * problem into median partitioning T: O(n log k), S: O(k)
 */
vector<double> Purgatory::medianSlidingWindow(vector<int> &nums, int k) {
  vector<double> res;
  multiset<int> window(nums.begin(), nums.begin() + k);

  auto mid = next(window.begin(), k / 2);

  for (int i = k;; ++i) {
    if (k % 2 == 1)
      res.push_back(*mid);
    else
      res.push_back(((double)*mid + *prev(mid)) / 2.0);

    if (i == nums.size())
      break;

    window.insert(nums[i]);
    if (nums[i] < *mid)
      mid--;

    if (nums[i - k] <= *mid)
      mid++;
    window.erase(window.lower_bound(nums[i - k]));
  }

  return res;
}

int Purgatory::minimumSumSubarray(const vector<int> &nums, int l, int r) {
  int minSum = INT_MAX;
  int n = nums.size();

  vector<int> prefix(n + 1, 0);

  for (int i = 0; i < n; ++i) {
    prefix[i + 1] = prefix[i] + nums[i];
  }

  for (int start = 0; start < n; ++start) {
    const int maxLen = min(r, n - start);

    for (int bound = l; bound <= maxLen; ++bound) {
      int sum = prefix[start + bound] - prefix[start];

      if (sum > 0 && sum < minSum)
        minSum = sum;
    }
  }

  return minSum == INT_MAX ? -1 : minSum;
}

int Purgatory::numSubarraysWithSum(const vector<int> &nums, int goal) {
  int n = nums.size();
  unordered_map<int, int> freq;
  // cache behavior
  freq.reserve(n << 1);
  freq[0] = 1;

  int prefixSum = 0;
  int result = 0;

  for (const int value : nums) {
    prefixSum += value;

    // branch prediction
    auto it = freq.find(prefixSum - goal);
    if (it != freq.end())
      result += it->second;

    ++freq[prefixSum];
  }

  return result;
}

int Purgatory::maxLength(vector<int> &nums) {
  int result = 0;
  const int n = nums.size();

  for (int i = 0; i < n; ++i) {
    // register vs memory
    long long prod = 1;
    long long g = 0;
    long long l = 1;

    for (int j = i; j < n; ++j) {
      prod *= nums[j];
      if (prod > 25200)
        break;

      if (j == i) {
        g = nums[j];
        l = nums[j];
      } else {
        g = std::gcd(g, (long long)nums[j]);

        long long common = std::gcd(l, (long long)nums[j]);

        l = l / common * nums[j];
      }

      // branch prediction
      if (prod == g * l)
        result = max(result, j - i + 1);
    }
  }

  return result;
}

int Purgatory::characterReplacement(string s, int k) {
  int result = 0;

  // cache behavior
  int count[26] = {0};
  int left = 0, maxFreq = 0;

  for (int right = 0; right < s.size(); ++right) {
    // register vs memory
    int idx = s[right] - 'A';
    count[idx]++;

    // branch prediction
    if (count[idx] > maxFreq)
      maxFreq = count[idx];

    while ((right - left + 1) - maxFreq > k) {
      count[s[left] - 'A']--;
      left++;
    }

    // branch prediction
    if (right - left + 1 > result)
      result = right - left + 1;
  }

  return result;
}

int Purgatory::numSubarrayProductLessThanK(const vector<int> &nums, int k) {
  if (k <= 1)
    return 0;

  int result = 0;
  long long prod = 1;
  int left = 0;

  for (int right = 0; right < nums.size(); ++right) {
    prod *= nums[right];

    // branch prediction
    while (prod >= k && left <= right) {
      prod /= nums[left++];
    }

    result += (right - left + 1);
  }

  return result;
}

int Purgatory::totalFruit(const vector<int> &fruits) {
  int result = 0;

  // cache behavior
  int type1 = -1, type2 = -1;
  int count1 = 0, count2 = 0;
  int left = 0;

  for (int right = 0; right < fruits.size(); ++right) {
    // register vs memory
    int f = fruits[right];

    // branch prediction
    if (f == type1) {
      count1++;
    } else if (f == type2) {
      count2++;
    } else {
      while (count1 > 0 && count2 > 0) {
        int leftFruit = fruits[left++];

        if (leftFruit == type1) {
          count1--;
        } else {
          count2--;
        }
      }

      if (count1 == 0) {
        type1 = f;
        count1 = 1;
      } else {
        type2 = f;
        count2 = 1;
      }
    }

    result = max(result, right - left + 1);
  }

  return result;
}

int Purgatory::numberOfAlternatingGroups(const vector<int> &colors) {
  int n = colors.size();
  int result = 0;

  for (int i = 0; i < n; ++i) {
    // register vs memory
    const int current = colors[i];
    int leftIdx = (i - 1 + n) % n;
    int rightIdx = (i + 1) % n;

    // branch prediction
    result += (current != colors[leftIdx] && current != colors[rightIdx]);
  }

  return result;
}

int Purgatory::findLength(const vector<int> &nums1, const vector<int> &nums2) {
  int result = 0;

  const int n = nums1.size();
  const int m = nums2.size();

  // cache behavior
  vector<int> dp(m + 1, 0);

  for (int i = 1; i <= n; ++i) {
    // register vs memory
    const int value = nums1[i - 1];

    for (int j = m; j >= 1; --j) {
      // branch prediction
      const bool match = (value == nums2[j - 1]);
      dp[j] = match ? dp[j - 1] + 1 : 0;
      result = max(result, dp[j]);
    }
  }

  return result;
}

int Purgatory::maxSatisfied(const vector<int> &customers,
                            const vector<int> &grumpy, int minutes) {
  int baseSatisfied = 0;
  int currentGain = 0;
  int maxGain = 0;

  const int n = customers.size();

  for (int i = 0; i < n; ++i) {
    // register vs memory
    const int customer = customers[i];
    const int isGrumpty = grumpy[i];

    // branch prediction
    baseSatisfied += customer * (1 - isGrumpty);
    currentGain += customer * isGrumpty;

    if (i >= minutes && grumpy[i - minutes] == 1)
      currentGain -= customers[i - minutes];

    if (i >= minutes - 1)
      maxGain = max(maxGain, currentGain);
  }

  return baseSatisfied + maxGain;
}

int Purgatory::countKConstraintSubstrings(string s, int k) {
  int result = 0;
  int left = 0;

  // branch prediction
  int count[2] = {0, 0};

  for (int right = 0; right < s.size(); ++right) {
    ++count[s[right] - '0'];

    while (count[0] > k && count[1] > k) {
      --count[s[left] - '0'];
      ++left;
    }

    result += right - left + 1;
  }

  return result;
}

int Purgatory::maxTurbulenceSize(const vector<int> &arr) {
  int result = 1;
  int n = arr.size();

  int prevCmp = 0;
  int curr = 1;

  for (int i = 1; i < n; ++i) {
    // branch prediction
    int cmp = (arr[i] > arr[i - 1]) - (arr[i] < arr[i - 1]);

    if (cmp == 0) {
      curr = 1;
    } else if (cmp * prevCmp == -1) {
      ++curr;
    } else {
      curr = 2;
    }

    result = max(result, curr);
    prevCmp = cmp;
  }

  return result;
}

int Purgatory::numberOfSubarrays(const vector<int> &nums, int k) {
  int result = 0;
  int n = nums.size();

  int left = 0;
  int prefix = 0;
  int oddCount = 0;

  for (int right = 0; right < n; ++right) {
    // register vs memory
    bool isOdd = nums[right] & 1;

    // branch prediction
    oddCount += isOdd;
    prefix *= (!isOdd);

    while (oddCount == k) {
      ++prefix;
      oddCount -= (nums[left] & 1);
      ++left;
    }

    result += prefix;
  }

  return result;
}

int Purgatory::maximumUniqueSubarray(const vector<int> &nums) {
  int result = 0;
  // cache behavior
  vector<int> freq(10001, 0);

  int left = 0;
  int currSum = 0;

  for (int right = 0; right < nums.size(); ++right) {

    // register vs memory
    int num = nums[right];
    freq[num]++;
    currSum += num;

    while (freq[num] > 1) {
      // register vs memory
      int leftNum = nums[left];
      freq[leftNum]--;
      currSum -= leftNum;
      ++left;
    }

    result = max(result, currSum);
  }

  return result;
}

} // namespace purgatory
