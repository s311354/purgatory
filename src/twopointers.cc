#include "purgatory.h"

namespace purgatory {

/*
 *  using two-pointer method here becuase
 *  - we can skip non-alphanumeric characters in-place without building a new
 * filtered string
 *  - this reduce extra memory usage to O(1)
 *  T: O(n), S: O(1)
 */

// function call & branch prediction
inline bool isAlnum(char c) {
  return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') ||
         (c >= '0' && c <= '9');
}

inline char toLower(char c) { return (c >= 'A' && c <= 'Z') ? c + 32 : c; }

bool Purgatory::isPalindrome(string s) {
  int left = 0, right = s.size() - 1;

  while (left < right) {
    // register vs memory
    while (left < right) {
      char l = s[left];
      if (isAlnum(l))
        break;
      ++left;
    }

    while (left < right) {
      char r = s[right];
      if (isAlnum(r))
        break;
      right--;
    }

    // register vs memory
    char l = toLower(s[left]), r = toLower(s[right]);

    if (l != r)
      return false;

    left++;
    right--;
  }

  return true;
}

/*
 *  using two pointers here because the input is sorted
 *  T: O(n), S: O(n)
 */
vector<int> Purgatory::twoSum(vector<int> &numbers, int target) {
  // register vs memory
  const int n = numbers.size();
  // cache behavior
  const int *data = numbers.data();

  unordered_map<int, int> seen;
  // cache behavior
  seen.reserve(n);

  for (int i = 0; i < n; ++i) {
    // register vs memory
    const int num = data[i];
    const int complement = target - num;

    // branch prediction
    auto it = seen.find(complement);
    if (it != seen.end()) {
      return {it->second, i};
    }

    seen.emplace(num, i);
  }

  return {};
}

/*
 *  using two pointers here because we can break the problme into repeatedly
 * eliminating impossible pairs. We always move the pointer at the shorter
 * height inward because that's the only way to potentially increase area. T:
 * O(n), S: O(1)
 */
int Purgatory::maxArea(vector<int> &height) {
  // cache behavior
  const int *data = height.data();

  int left = 0, right = height.size() - 1;
  int maxWater = 0;

  while (left < right) {
    // register vs memory
    const int hl = data[left];
    const int hr = data[right];

    // CPU pipleline
    const int width = right - left;
    const int minH = (hl < hr) ? hl : hr;
    const int area = minH * width;

    // function call
    if (area > maxWater)
      maxWater = area;

    // branch prediction
    left += (hl < hr);
    right -= (hl >= hr);
  }

  return maxWater;
}

/*
 *  using two pointers here becuase we can break the problem into continuously
 * shrinking the search space from both ends, while keeping track of the max
 * heights seen so far. T: O(n), S: O(1)
 */
int Purgatory::trap(vector<int> &height) {
  // cache behavior
  const int *data = height.data();
  int left = 0, right = height.size() - 1;
  int leftMax = 0, rightMax = 0;
  int water = 0;

  while (left < right) {
    // register vs memory
    const int hl = data[left], hr = data[right];
    // branch prediction
    const bool moveLeft = (hl < hr);
    const int current = moveLeft ? hl : hr;
    int &currentMax = moveLeft ? leftMax : rightMax;

    currentMax = (current > currentMax) ? current : currentMax;
    water += (currentMax - current);
    left += moveLeft;
    right -= !moveLeft;
  }

  return water;
}

/*
 *  using symmetry-based in-place here because we can break the problem into
 * pairwise swapping from both ends T: O(n), S: O(1)
 */
void Purgatory::reverseString(vector<char> &s) {
  // register vs memory
  char *l = &s[0];
  char *r = &s[s.size() - 1];

  // cache behavior
  while (l < r) {
    char temp = *l;
    *l++ = *r;
    *r-- = temp;
  }
}

/*
 * using the dutch national flag algorithm here because we can break the problem
 * into three regions T: O(n), S: O(1)
 */
void Purgatory::sortColors(vector<int> &nums) {
  // register vs memory
  int *l = &nums[0];
  int *m = &nums[0];
  int *r = &nums[nums.size() - 1];

  while (m <= r) {
    // cache behavior
    int v = *m;
    if (v == 0) {
      if (m != l) {
        int tmp = *l;
        *l = *m;
        *m = tmp;
      }
      l++;
      m++;
    } else if (v == 2) {
      if (m != r) {
        int tmp = *r;
        *r = *m;
        *m = tmp;
      }
      r--;
    } else {
      m++;
    }
  }
}

/*
 *  using two-pointer parsing method here because we can break the problem into
 * small numeric segments without splitting strings T: O(n + m), S: O(1)
 */
int Purgatory::compareVersion(const string &version1, const string &version2) {
  // register vs memory
  const char *p1 = version1.c_str();
  const char *p2 = version2.c_str();

  while (*p1 || *p2) {
    long num1 = 0, num2 = 0;

    while (*p1 && *p1 != '.') {
      num1 = num1 * 10 + (*p1 - '0');
      ++p1;
    }

    while (*p2 && *p2 != '.') {
      num2 = num2 * 10 + (*p2 - '0');
      ++p2;
    }

    // branch prediction
    if (num1 != num2)
      return num1 < num2 ? -1 : 1;

    if (*p1 == '.')
      ++p1;
    if (*p2 == '.')
      ++p2;
  }

  return 0;
}

vector<int> maxSubsequence(const vector<int> &nums, int k) {
  vector<int> st;

  int drop = nums.size() - k;

  for (int num : nums) {
    while (!st.empty() && drop > 0 && st.back() < num) {
      st.pop_back();
      drop--;
    }

    st.push_back(num);
  }

  st.resize(k);
  return st;
}

bool greaterVec(const vector<int> &a, int i, const vector<int> &b, int j) {
  while (i < a.size() && j < b.size() && a[i] == b[j]) {
    i++;
    j++;
  }

  return j == b.size() || (i < a.size() && a[i] > b[j]);
}

vector<int> mergeMaxNumber(vector<int> &a, vector<int> &b) {
  vector<int> result;
  // cache behavior
  result.reserve(a.size() + b.size());

  int i = 0, j = 0;

  while (i < a.size() || j < b.size()) {
    // cpu pipleline
    if (greaterVec(a, i, b, j)) {
      result.push_back(a[i++]);
    } else {
      result.push_back(b[j++]);
    }
  }

  return result;
}

/*
 *  using greedy monotonic stack + lexicographic merge hear because we can break
 * the problem into
 *  - selecting best subsequence from each array
 *  - merging them optimally
 *  - trying all possible divisons
 *  T:((M + N)^2), S:O(K)
 */
vector<int> Purgatory::maxNumber(const vector<int> &nums1,
                                 const vector<int> &nums2, int k) {
  vector<int> best;

  int m = nums1.size(), n = nums2.size();

  for (int i = max(0, k - n); i <= min(k, m); ++i) {
    vector<int> part1 = maxSubsequence(nums1, i);
    vector<int> part2 = maxSubsequence(nums2, k - i);

    vector<int> candidate = mergeMaxNumber(part1, part2);

    best = max(best, candidate);
  }

  return best;
}

int Purgatory::findContentChildren(vector<int> &g, vector<int> &s) {
  sort(g.begin(), g.end());
  sort(s.begin(), s.end());

  // register vs memory
  int gn = g.size(), sn = s.size();
  int child = 0, cookie = 0;

  while (child < gn && cookie < sn) {
    // branch prediction
    if (s[cookie] >= g[child])
      ++child;

    ++cookie;
  }

  return child;
}

int Purgatory::magicalString(int n) {
  if (n <= 0)
    return 0;
  if (n <= 3)
    return 1;

  vector<int> s(n);
  s[0] = 1;
  s[1] = 2;
  s[2] = 2;

  int read = 2;
  int write = 3;
  int num = 1;
  int count = 1;

  while (write < n) {
    // cpu pipeline
    int len = s[read++];

    for (int i = 0; i < len && write < n; ++i) {

      s[write++] = num;
      // branch prediction
      count += (num == 1);
    }

    num ^= 3;
  }

  return count;
}

bool Purgatory::checkInclusion(string s1, string s2) {
  int n1 = s1.size(), n2 = s2.size();

  if (n1 > n2)
    return false;

  // cache behavior
  int freq[26] = {0};

  for (char c : s1)
    freq[c - 'a']++;

  int count = n1;

  for (int i = 0; i < n2; ++i) {
    if (freq[s2[i] - 'a']-- > 0)
      count--;

    // branch prediction
    if (i >= n1)
      if (freq[s2[i - n1] - 'a'] >= 0)
        count++;

    if (count == 0)
      return true;
  }

  return false;
}

long findSqrt(int c) {
  long l = 0, r = c, ans = 0;

  while (l <= r) {
    long mid = l + (r - l) / 2;

    // branch prediction
    if (mid * mid <= c) {
      ans = mid;
      l = mid + 1;
    } else {
      r = mid - 1;
    }
  }

  return ans;
}

bool Purgatory::judgeSquareSum(int c) {
  long left = 0, right = findSqrt(c);

  // cpu pipeline
  long l2 = 0, r2 = right * right;

  while (left <= right) {
    long sum = l2 + r2;

    if (sum == c)
      return true;
    else if (sum < c) {
      left++;
      l2 = left * left;
    } else {
      right--;
      r2 = right * right;
    }
  }
  return false;
}

int Purgatory::removePalindromeSub(const string &s) {
  // cache behavior
  const char *l = s.data();
  const char *r = l + s.size() - 1;

  while (l < r) {
    // branch prediction
    if (*r != *l)
      return 2;
    ++l;
    --r;
  }
  return 1;
}

int Purgatory::findRadius(vector<int> &house, vector<int> &heaters) {
  // cpu pipeline
  sort(house.begin(), house.end());
  sort(heaters.begin(), heaters.end());

  int i = 0;
  int maxRadius = 0;

  for (int h : house) {
    // branch prediction
    while (i < heaters.size() - 1 &&
           abs(heaters[i + 1] - h) <= abs(heaters[i] - h)) {
      ++i;
    }

    maxRadius = max(maxRadius, abs(heaters[i] - h));
  }

  return maxRadius;
}

bool Purgatory::circularArrayLoop(vector<int> &nums) {
  int n = nums.size();

  for (int i = 0; i < n; ++i) {
    if (nums[i] == 0)
      continue;

    int slow = i, fast = i;
    bool isForward = nums[i] > 0;

    while (true) {
      int nextSlow = slow + nums[slow];
      if (nextSlow >= n || nextSlow < 0)
        nextSlow = (nextSlow % n + n) % n;
      int valSlow = nums[nextSlow];

      int nextFast = fast + nums[fast];
      if (nextFast >= n || nextFast < 0)
        nextFast = (nextFast % n + n) % n;
      int valFast1 = nums[nextFast];

      nextFast = nextFast + valFast1;
      if (nextFast >= n || nextFast < 0)
        nextFast = (nextFast % n + n) % n;
      int valFast2 = nums[nextFast];

      // branch prediction
      if (((valSlow > 0) != isForward) || ((valFast1 > 0) != isForward) ||
          ((valFast2 > 0) != isForward))
        break;

      slow = nextSlow;
      fast = nextFast;

      if (slow == fast) {
        int next = slow + nums[slow];

        if (next >= n || next < 0)
          next = (next % n + n) % n;

        if (next == slow)
          break;

        return true;
      }
    }

    int cur = i;

    while (true) {
      // register vs memory
      int step = nums[cur];

      if ((step > 0) != isForward)
        break;

      int nxt = cur + step;

      if (nxt >= n || nxt < 0)
        nxt = (nxt % n + n) % n;

      nums[cur] = 0;

      if (nxt == cur)
        break;

      cur = nxt;
    }
  }

  return false;
}

int Purgatory::maxProfitAssignment(vector<int> &difficulty, vector<int> &profit,
                                   vector<int> &worker) {
  int n = difficulty.size();

  // cache behavior
  vector<pair<int, int>> jobs;
  jobs.reserve(n);

  for (int i = 0; i < n; ++i) {
    jobs.push_back({difficulty[i], profit[i]});
  }

  sort(jobs.begin(), jobs.end());
  sort(worker.begin(), worker.end());

  int maxProfitSoFar = 0;
  int j = 0;
  int total = 0;

  for (int w : worker) {
    while (j < n) {
      // register vs memory
      int d = jobs[j].first;

      if (d > w)
        break;

      // register vs memory
      int p = jobs[j].second;

      if (p > maxProfitSoFar)
        maxProfitSoFar = p;

      ++j;
    }
    total += maxProfitSoFar;
  }
  return total;
}

int Purgatory::countBinarySubstrings(const string &s) {
  int prevGroup = 0;
  int currGroup = 1;
  int totalCount = 0;

  if (s.size() < 2)
    return 0;

  // register vs memory
  const char *data = s.data();

  for (int i = 1; i < s.size(); ++i) {
    if (data[i] == data[i - 1])
      ++currGroup;
    else {
      prevGroup = currGroup;
      currGroup = 1;
    }

    // branch prediction
    totalCount += (prevGroup >= currGroup);
  }
  return totalCount;
}

int expandAorundCenterCountSubstrings(const string &s, int left, int right) {

  // register vs memory
  int length = s.size();
  int palindromeCount = 0;

  while (left >= 0 && right < length && s[left] == s[right]) {
    ++palindromeCount;
    --left;
    ++right;
  }

  return palindromeCount;
}

int Purgatory::countSubstrings(const string &s) {
  // register vs memory
  int n = s.size();
  int totalPalindromes = 0;

  for (int center = 0; center < n; ++center) {
    totalPalindromes += expandAorundCenterCountSubstrings(s, center, center);

    totalPalindromes +=
        expandAorundCenterCountSubstrings(s, center, center + 1);
  }

  return totalPalindromes;
}

int Purgatory::longestMountain(const vector<int> &arr) {
  int n = arr.size();

  if (n < 3)
    return 0;

  int up = 0, down = 0;
  int maxLength = 0;

  for (int i = 1; i < n; ++i) {
    // register vs memory
    const int diff = arr[i] - arr[i - 1];
    if ((down > 0 && diff > 0) || diff == 0) {
      up = 0;
      down = 0;
    }

    if (diff > 0)
      ++up;
    else if (diff < 0)
      ++down;

    if (up > 0 && down > 0)
      maxLength = max(maxLength, up + down + 1);
  }

  return maxLength;
}

string Purgatory::reverseStr(string s, int k) {
  const int n = s.size();

  for (int start = 0; start < n; start += (k << 1)) {
    // register vs memory
    int left = start;
    int right = min(start + k, n) - 1;

    // branch prediction
    while (left < right) {
      char temp = s[left];
      s[left++] = s[right];
      s[right--] = temp;
    }
  }

  return s;
}

vector<int> Purgatory::shortestToChar(string s, char c) {
  const int n = s.size();

  vector<int> result(n);

  int lastSeen = -n;

  for (int i = 0; i < n; ++i) {
    // branch prediction
    lastSeen = (s[i] == c) ? i : lastSeen;
    result[i] = i - lastSeen;
  }

  lastSeen = n << 1;

  for (int i = n - 1; i >= 0; --i) {
    // branch prediction
    lastSeen = (s[i] == c) ? i : lastSeen;
    // register vs memory
    const int rightDist = lastSeen - i;
    result[i] = result[i] < rightDist ? result[i] : rightDist;
  }

  return result;
}

int Purgatory::rangeSum(vector<int> &nums, int n, int left, int right) {
  const int MOD = 1e9 + 7;

  // cache behavior
  vector<int> subarraySums;
  subarraySums.reserve(n * (n + 1) / 2);

  for (int start = 0; start < n; ++start) {
    // register vs memory
    int runningSum = 0;

    for (int end = start; end < n; ++end) {
      runningSum += nums[end];
      subarraySums.emplace_back(runningSum);
    }
  }

  sort(subarraySums.begin(), subarraySums.end());

  long long answer = 0;

  for (int i = left - 1; i < right; ++i) {
    answer += subarraySums[i];
  }

  return static_cast<int>(answer % MOD);
}

string Purgatory::addSpaces(string s, vector<int> &spaces) {
  // register vs memory
  const size_t n = s.size();
  const size_t m = spaces.size();

  // cache behavior
  string result;
  result.reserve(n + m);

  size_t spaceIndex = 0;

  for (size_t i = 0; i < n; ++i) {
    // branch prediction
    bool needSpace =
        (spaceIndex < m) && (static_cast<int>(i) == spaces[spaceIndex]);

    if (needSpace) {
      result.push_back(' ');
      ++spaceIndex;
    }

    result.push_back(s[i]);
  }

  return result;
}

long long Purgatory::minimumSteps(const string &s) {
  long long onesCount = 0;
  long long totalSwaps = 0;

  // cache behavior
  const char *ptr = s.data();
  const size_t n = s.size();

  for (size_t i = 0; i < n; ++i) {
    // branch prediction
    const bool isBlack = (ptr[i] == '1');
    onesCount += isBlack;
    totalSwaps += (!isBlack) * onesCount;
  }

  return totalSwaps;
}

int Purgatory::getCommon(const vector<int> &nums1, const vector<int> &nums2) {
  // register vs memory
  int n1 = nums1.size(), n2 = nums2.size();

  int i = 0, j = 0;

  while (i < n1 && j < n2) {
    // register vs memory
    const int a = nums1[i];
    const int b = nums2[j];

    if (a == b) {
      return a;
    }

    if (a < b) {
      ++i;
    } else {
      ++j;
    }
  }

  return -1;
}

int Purgatory::numFriendRequests(const vector<int> &ages) {

  // cache behavior
  int cnt[121] = {};

  for (int age : ages)
    ++cnt[age];

  int total = 0;
  for (int i = 1; i <= 120; ++i) {
    if (cnt[i] == 0)
      continue;
    for (int j = 1; j <= 120; ++j) {
      if (cnt[j] == 0)
        continue;

      if (j <= (i >> 1) + 7)
        continue;

      if (j > i)
        continue;

      if (j > 100 && i < 100)
        continue;

      if (i == j) {
        total += cnt[i] * (cnt[i] - 1);
      } else {
        total += cnt[i] * cnt[j];
      }
    }
  }

  return total;
}

string Purgatory::reverseOnlyLetters(string s) {
  int left = 0, right = s.size() - 1;

  while (left < right) {
    // function call
    while (left < right && !((s[left] >= 'a' && s[left] <= 'z') ||
                             (s[left] >= 'A' && s[left] <= 'Z')))
      ++left;

    while (left < right && !((s[right] >= 'a' && s[right] <= 'z') ||
                             (s[right] >= 'A' && s[right] <= 'Z')))
      --right;

    if (left < right) {
      char c = s[left];
      s[left] = s[right];
      s[right] = c;

      ++left;
      --right;
    }
  }

  return s;
}

int Purgatory::numRescueBoats(vector<int> &people, int limit) {
  int count = 0;
  sort(people.begin(), people.end());
  int left = 0, right = people.size() - 1;

  while (left <= right) {
    // register vs memory
    int sum = people[right];

    if (left != right) {
      sum += people[left];

      if (sum <= limit) {
        ++left;
      }
    }

    ++count;
    --right;
  }

  return count;
}

int Purgatory::waysToSplit(vector<int> &nums) {
  int n = nums.size();
  const int MOD = 1e9 + 7;

  // cache behavior
  vector<long long> prefixSum(n);
  prefixSum[0] = nums[0];

  for (int i = 1; i < n; ++i) {
    prefixSum[i] = prefixSum[i - 1] + nums[i];
  }

  long long total = prefixSum.back();
  long long count = 0;

  // register vs memory
  const auto begin = prefixSum.begin();
  const auto end = prefixSum.end() - 1;

  for (int leftEnd = 0; leftEnd < n - 2; ++leftEnd) {
    // register vs memory
    long long leftSum = prefixSum[leftEnd];

    const long long lowerTarget = leftSum << 1;
    const long long upperTarget = (leftSum + total) >> 1;

    int leftBound = lower_bound(begin + leftEnd + 1, end, lowerTarget) - begin;
    int rightBound =
        upper_bound(begin + leftEnd + 1, end, upperTarget) - begin - 1;

    if (leftBound <= rightBound)
      count += rightBound - leftBound + 1;
  }

  return static_cast<int>(count % MOD);
}

vector<int> Purgatory::applyOperations(vector<int> &nums) {
  int n = nums.size();

  for (int i = 0; i < n - 1; ++i) {
    // register vs memory
    int current = nums[i];
    int next = nums[i + 1];

    if (current == next) {
      nums[i] = current << 1;
      nums[i + 1] = 0;
    }
  }

  int write = 0;
  for (int read = 0; read < n; ++read) {
    if (nums[read] != 0)
      nums[write++] = nums[read];
  }

  while (write < n) {
    nums[write++] = 0;
  }

  return nums;
}

int Purgatory::arithmeticTriplets(const vector<int> &nums, int diff) {
  // register vs memory
  int n = nums.size();

  if (n < 3)
    return 0;

  int count = 0;
  int left = 0;
  int right = 2;

  for (int mid = 0; mid < n - 1; ++mid) {
    const int midValue = nums[mid];
    const int leftTarget = midValue - diff;
    const int rightTarget = midValue + diff;

    while (left < mid && nums[left] < leftTarget) {
      ++left;
    }

    if (right <= mid)
      right = mid + 1;

    while (right < n && nums[right] < rightTarget) {
      ++right;
    }

    // branch prediction
    const bool leftFound = left < mid && nums[left] == leftTarget;
    const bool rightFound = right < n && nums[right] == rightTarget;

    count += leftFound && rightFound;
  }

  return count;
}

int Purgatory::findLUSlegnth(vector<string> &strs) {
  // register vs memory
  int n = strs.size();

  sort(strs.begin(), strs.end(),
       [](const string &a, const string &b) { return a.size() > b.size(); });

  for (int i = 0; i < n; ++i) {
    bool uncommon = true;

    for (int j = 0; j < n; ++j) {
      // branch prediction
      if (i == j || strs[j].size() < strs[i].size())
        continue;

      int count = 0;

      for (char c : strs[j]) {
        if (count < strs[i].size() && strs[i][count] == c)
          ++count;
      }

      if (count == strs[i].size()) {
        uncommon = false;
        break;
      }
    }

    if (uncommon)
      return strs[i].size();
  }
  return -1;
}

vector<int> Purgatory::partitionLabels(string s) {
  if (s.empty())
    return {};

  int length = s.size();

  int lastPartition[26] = {};

  for (int i = 0; i < length; ++i) {
    lastPartition[s[i] - 'a'] = i;
  }

  // cache behavior
  vector<int> result;
  result.reserve(26);

  int start = 0;
  int end = 0;

  for (int i = 0; i < length; ++i) {
    // register vs memory
    const int letter = s[i] - 'a';
    const int letterEnd = lastPartition[letter];

    if (end < letterEnd)
      end = letterEnd;

    if (end == i) {
      result.push_back(end - start + 1);
      start = i + 1;
    }
  }

  return result;
}

vector<int> Purgatory::findIndices(vector<int> &nums, int indexDifference,
                                   int valueDifference) {
  const int length = static_cast<int>(nums.size());
  if (length == 0)
    return {-1, -1};

  int minIndex = -1;
  int maxIndex = -1;

  int minValue = INT_MAX;
  int maxValue = INT_MIN;

  // CPU pipleline
  for (int rightIndex = 0; rightIndex < length; ++rightIndex) {
    const int eligibalIndex = rightIndex - indexDifference;

    if (eligibalIndex >= 0) {
      const int eligibalValue = nums[eligibalIndex];

      if (eligibalValue < minValue) {
        minIndex = eligibalIndex;
        minValue = eligibalValue;
      }

      if (eligibalValue > maxValue) {
        maxIndex = eligibalIndex;
        maxValue = eligibalValue;
      }
    }

    if (minIndex == -1)
      continue;

    // register vs memory
    const int currentValue = nums[rightIndex];

    if (currentValue - minValue >= valueDifference)
      return {minIndex, rightIndex};

    if (maxValue - currentValue >= valueDifference)
      return {maxIndex, rightIndex};
  }

  return {-1, -1};
}

long long Purgatory::perfectPairs(vector<int> &nums) {
  if (nums.size() < 2)
    return 0;

  // cache behavior
  vector<long long> values;
  values.reserve(nums.size());

  for (int value : nums) {
    values.push_back(llabs(static_cast<long long>(value)));
  }

  sort(values.begin(), values.end());

  long long count = 0;
  int left = 0;
  for (int right = 0; right < values.size(); ++right) {
    // register vs memory
    const long long currentValue = values[right];

    while (left < right && currentValue > values[left] << 1) {
      ++left;
    }

    count += right - left;
  }

  return count;
}

int Purgatory::maxCapacity(const vector<int> &costs,
                           const vector<int> &capacity, int budget) {
  const int n = costs.size();

  if (n == 0 || budget <= 1)
    return 0;

  const int maxCost = budget - 1;

  // cache behavior
  vector<int> firstCapacity(maxCost + 1, 0);
  vector<int> secondCapacity(maxCost + 1, 0);

  for (int i = 0; i < n; ++i) {
    const int cost = costs[i];

    if (cost >= budget)
      continue;

    const int currentCapacity = capacity[i];

    // register vs memory
    int &firsthigh = firstCapacity[cost];
    int &secondhigh = secondCapacity[cost];

    // branch prediction
    if (currentCapacity > firsthigh) {
      secondhigh = firsthigh;
      firsthigh = currentCapacity;
    } else if (currentCapacity > secondhigh) {
      secondhigh = currentCapacity;
    }
  }

  // CPU pipleline
  vector<int> prefixBest(maxCost + 1, 0);

  for (int cost = 1; cost <= maxCost; ++cost) {
    prefixBest[cost] = max(prefixBest[cost - 1], firstCapacity[cost]);
  }

  int result = 0;

  for (int cost = 1; cost <= maxCost; ++cost) {
    const int currentBest = firstCapacity[cost];

    if (currentBest == 0)
      continue;

    result = max(result, currentBest);

    if (cost < budget - cost && secondCapacity[cost] > 0) {
      result = max(result, currentBest + secondCapacity[cost]);
    }

    const int maxPartnerCost = min(cost - 1, budget - cost - 1);

    if (maxPartnerCost >= 1) {
      result = max(result, currentBest + prefixBest[maxPartnerCost]);
    }
  }

  return result;
}

int Purgatory::distinctAverage(const vector<int> &nums) {
  if (nums.empty() || nums.size() % 2 != 0)
    return 0;

  // CPU pipleline
  array<int, 101> freq{};

  for (int value : nums) {
    ++freq[value];
  }

  int minValue = 0;
  int maxValue = 100;

  int pairsNum = nums.size() >> 1;

  bitset<201> seenSums;

  while (pairsNum-- > 0) {
    while (freq[minValue] == 0)
      ++minValue;

    while (freq[maxValue] == 0)
      --maxValue;

    seenSums.set(minValue + maxValue);

    --freq[minValue];
    --freq[maxValue];
  }

  return seenSums.count();
}

long long Purgatory::maximumTotalDamage(vector<int> &power) {
  if (power.empty())
    return 0;

  sort(power.begin(), power.end());

  const int n = power.size();
  vector<int> values;
  values.reserve(n);

  // cache behavior
  vector<int> gains;
  gains.reserve(n);

  int index = 0;
  while (index < n) {
    const int damage = power[index];
    long long total = 0;

    do {
      total += damage;
      ++index;
    } while (index < n && power[index] == damage);

    values.push_back(damage);
    gains.push_back(total);
  }

  const int groupCount = values.size();

  vector<long long> dp(groupCount, 0);

  int last = -1;

  for (int current = 0; current < groupCount; ++current) {
    const int currentDamage = values[current];
    const long long currentGain = gains[current];
    const int limit = currentDamage - 3;

    // branch prediction
    while (last + 1 < current && values[last + 1] <= limit) {
      ++last;
    }

    const long long skip = (current == 0) ? 0 : dp[current - 1];

    const long long best = (last < 0) ? 0 : dp[last];

    const long long take = currentGain + best;

    dp[current] = max(skip, take);
  }

  return dp.back();
}

int Purgatory::firstMatchingIndex(string s) {
  const int n = static_cast<int>(s.size());

  if (n == 0)
    return -1;

  // cpu pipeline
  int left = 0;
  int right = n - 1;

  while (left <= right) {
    if (s[left] == s[right])
      return left;

    ++left;
    --right;
  }

  return -1;
}

int Purgatory::maxRemovals(string source, string pattern,
                           const vector<int> &targetIndices) {
  int sourceLength = source.size();
  int patternLength = pattern.size();

  vector<int> isTarget(sourceLength, 0);

  for (int index : targetIndices)
    isTarget[index] = 1;

  const int INF = INT_MAX >> 1;

  vector<int> dp(patternLength + 1, INF);
  dp[0] = 0;

  for (int i = 0; i < sourceLength; ++i) {
    const char current = source[i];
    const int cost = isTarget[i];

    for (int matched = patternLength; matched >= 1; --matched) {
      if (current == pattern[matched - 1]) {
        dp[matched] = min(dp[matched], dp[matched - 1] + cost);
      }
    }
  }

  return targetIndices.size() - dp[patternLength];
}

double Purgatory::minimumAverage(vector<int> &nums) {
  if (nums.empty())
    return 0;

  double result = INT_MAX;

  sort(nums.begin(), nums.end());

  // branch prediction
  for (int left = 0, right = nums.size() - 1; left < right; ++left, --right) {
    // register vs memory
    const int minValue = nums[left];
    const int maxValue = nums[right];

    double average = static_cast<double>(minValue + maxValue) / 2;

    result = result < average ? result : average;
  }

  return result;
}

string Purgatory::pushDominoes(string dominoes) {
  int prevForce = 'L';
  int prevIndex = -1;

  const int n = dominoes.size();

  // cpu pipleline
  for (int i = 0; i <= n; ++i) {
    char current = (i == n) ? 'R' : dominoes[i];

    // branch prediction
    if (current == '.')
      continue;

    if (prevForce == current) {
      for (int j = prevIndex + 1; j < i; ++j) {
        dominoes[j] = current;
      }
    } else if (prevForce == 'R' && current == 'L') {
      int left = prevIndex + 1;
      int right = i - 1;

      while (left < right) {
        dominoes[++left] == 'R';
        dominoes[--right] == 'L';
      }
    }

    prevForce = current;
    prevIndex = i;
  }

  return dominoes;
}

vector<vector<int>>
Purgatory::intervalIntersection(const vector<vector<int>> &firstList,
                                const vector<vector<int>> &secondList) {
  const int n = firstList.size();
  const int m = secondList.size();

  int firstIndex = 0;
  int secondIndex = 0;

  vector<vector<int>> result;

  // cpu pipleline
  while (firstIndex < n && secondIndex < m) {
    // register vs memory
    const auto &first = firstList[firstIndex];
    const auto &second = secondList[secondIndex];

    // Skip empty intervals
    if (first.empty() || second.empty()) {
      if (first.empty())
        ++firstIndex;
      if (second.empty())
        ++secondIndex;
      continue;
    }

    const int firstStart = first[0];
    const int firstEnd = first[1];

    const int secondStart = second[0];
    const int secondEnd = second[1];

    int left = max(firstStart, secondStart);
    int right = min(firstEnd, secondEnd);

    // branch prediction
    if (left <= right) {
      result.push_back({left, right});
    }

    if (firstEnd < secondEnd) {
      ++firstIndex;
    } else {
      ++secondIndex;
    }
  }

  return result;
}

bool Purgatory::isLongPressedName(string name, string typed) {
  const int nameLength = name.size();
  const int typedLength = typed.size();

  if (nameLength > typedLength)
    return false;

  int nameIndex = 0;

  // cpu pipleline
  for (int typedIndex = 0; typedIndex < typedLength; ++typedIndex) {
    // register vs memory
    const char current = typed[typedIndex];

    if (nameIndex < nameLength && name[nameIndex] == current) {
      ++nameIndex;
      continue;
    }

    if (typedIndex == 0 || current != typed[typedIndex - 1])
      return false;
  }

  return nameIndex == nameLength;
}

long long Purgatory::findTheArrayConcVal(const vector<int> &nums) {
  long long result = 0;

  int left = 0;
  int right = nums.size() - 1;

  // cpu pipleline
  while (left <= right) {
    if (left == right) {
      result += nums[left];
      break;
    }

    int leftNum = nums[left];
    int rightNum = nums[right];
    int multi = rightNum < 10      ? 10
                : rightNum < 100   ? 100
                : rightNum < 1000  ? 1000
                : rightNum < 10000 ? 10000
                                   : 100000;

    result += leftNum * multi + rightNum;
    ++left;
    --right;
  }

  return result;
}

int Purgatory::maxNumOfMarkedIndices(vector<int> &nums) {
  int n = nums.size();

  if (n < 2)
    return 0;

  sort(nums.begin(), nums.end());

  int limit = n / 2;
  int left = 0;
  int right = (n + 1) / 2;
  int pair = 0;

  while (left < limit && right < n) {
    const long long twice = static_cast<long long>(nums[left]) << 1;
    const int large = nums[right];

    // branch prediction
    if (twice <= large) {
      ++pair;
      ++left;
    }

    ++right;
  }

  return pair << 1;
}

} // namespace purgatory
