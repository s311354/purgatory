#include "purgatory.h"

namespace purgatory {

/*
 *  using a stack-based solution here because parentheses matching is naturally
 * Last In First Out T: O(n), S: O(n)
 */
bool Purgatory::isValid(string s) {
  // cache behavior
  vector<char> stack;
  stack.reserve(s.size());
  int top = 0;

  for (const char c : s) {
    char expected = 0;

    switch (c) {
    case ')':
      expected = '(';
      break;
    case ']':
      expected = '[';
      break;
    case '}':
      expected = '{';
      break;
    default:
      stack[top++] = c;
      continue;
    }

    if (top == 0 || stack[top - 1] != expected)
      return false;
    --top;
  }

  // cpu pipelie
  return top == 0;
}

/*
 *  using a stack-based solution here because it naturally models directory
 * traversal. This problem can be broken down into tokenizing by /, then
 * applying rules for ".", "..", and normal names. T: O(n), S: O(n)
 */
string Purgatory::simplifyPath(string path) {
  struct Slice {
    int start;
    int len;
  };

  const int n = path.size();

  vector<Slice> dirs;
  dirs.reserve(n / 2 + 1);

  int i = 0;
  // cpu pipeline
  while (i < n) {
    while (i < n && path[i] == '/')
      ++i;

    const int start = i;

    while (i < n && path[i] != '/')
      ++i;

    const int len = i - start;

    if (len == 0)
      continue;

    if (len == 1 && path[start] == '.')
      continue;

    // branch prediction
    if (len == 2 && path[start] == '.' && path[start + 1] == '.') {
      if (!dirs.empty())
        dirs.pop_back();

      continue;
    }

    dirs.push_back({start, len});
  }

  if (dirs.empty())
    return "/";

  string result;
  result.reserve(path.size());

  for (const Slice &dir : dirs) {
    result.push_back('/');
    result.append(path, dir.start, dir.len);
  }

  return result;
}

/*
 *  using a stack-based evaluation here because RPN naturally maps to push/pop
 * operations T: O(n), S: O(n)
 */
int Purgatory::evalRPN(const vector<string> &tokens) {
  // cache behavior
  vector<int> st;
  st.reserve(tokens.size());

  for (const string &tok : tokens) {
    // branch prediction
    if (tok.size() == 1) {
      const char c = tok[0];

      if (c == '+' || c == '-' || c == '*' || c == '/') {
        const int b = st.back();
        st.pop_back();
        const int a = st.back();
        st.pop_back();

        int value;

        switch (c) {
        case '+':
          value = a + b;
          break;
        case '-':
          value = a - b;
          break;
        case '*':
          value = a * b;
          break;
        default:
          value = a / b;
          break;
        }

        st.push_back(value);
        continue;
      }
    }

    int sign = 1;
    int index = 0;
    int value = 0;

    if (tok[0] == '-') {
      sign = -1;
      index = 1;
    }

    const int length = tok.size();
    for (; index < length; ++index) {
      value = value * 10 + (tok[index] - '0');
    }

    st.push_back(sign * value);
  }

  return st.back();
}

/*
 *  using a stack to store cotext when entering parentheses here because this
 * allows linear traversal. T: O(n), S: O(n)
 */
int Purgatory::calculate(const string &s) {
  // cache behavior
  vector<int> signs;
  signs.reserve(64);
  signs.push_back(1);

  long long result = 0;
  int sign = 1;

  // cpu pipeline
  const char *p = s.data();
  const char *end = p + s.size();

  while (p < end) {
    const char c = *p;

    // branch prediction
    if (c >= '0' && c <= '9') {
      long long number = 0;

      do {
        number = number * 10 + (*p - '0');
        ++p;
      } while (p < end && *p >= '0' && *p <= '9');

      result += static_cast<long long>(sign) * number;
      continue;
    }

    if (c == '+') {
      sign = signs.back();
    } else if (c == '-') {
      sign = -signs.back();
    } else if (c == '(') {
      signs.push_back(sign);
    } else if (c == ')') {
      signs.pop_back();
    }

    ++p;
  }

  return static_cast<int>(result);
}

/*
 *  using a monotonic decreasing stack here because we can break the problem
 * into computing next greater element in linear time T: O(m + n), S: O(n)
 */
vector<int> Purgatory::nextGreaterElement(const vector<int> &nums1,
                                          const vector<int> &nums2) {
  constexpr int MAX_VALUE = 10000;
  // cache behavior
  vector<int> next(MAX_VALUE + 1, -1);
  vector<int> st;
  st.reserve(nums2.size());

  for (const int x : nums2) {
    // register vs memory
    while (!st.empty() && x > st.back()) {
      const int smaller = st.back();
      st.pop_back();

      next[smaller] = x;
    }

    st.push_back(x);
  }

  vector<int> result;
  result.reserve(nums1.size());

  for (int x : nums1) {
    result.push_back(next[x]);
  }

  return result;
}

/*
 *  using a greedy + monotonic stack approach here because we can break the
 * problem into pop a character if it reapears later and would lead to a smaller
 * lexicographical result. T: O(n), S: O(1)
 */
string Purgatory::removeDuplicateLetters(string s) {
  // cache behavior
  int last[26];
  for (int i = 0; i < 26; ++i)
    last[i] = -1;

  const int n = s.size();
  for (int i = 0; i < n; ++i)
    last[s[i] - 'a'] = i;

  // cache behavior
  bool inStack[26] = {};
  string st;
  st.reserve(26);

  for (int i = 0; i < n; ++i) {
    const char c = s[i];
    const int index = c - 'a';

    if (inStack[index])
      continue;

    // branch prediction
    while (!st.empty()) {
      const char top = st.back();

      if (top <= c)
        break;

      const int topIndex = top - 'a';
      if (last[topIndex] <= i)
        break;

      inStack[topIndex] = false;
      st.pop_back();
    }

    st.push_back(c);
    inStack[index] = true;
  }

  return st;
}

/*
 *  using a single pass + stack approach here becuase we cn break the expression
 * into terms. This handles operator precedence naturally. T: O(n), S: O(n)
 */
int Purgatory::calculateII(const string &s) {
  int n = s.size();

  const char *p = s.data();
  const char *end = p + s.size();

  long long result = 0;
  long long last = 0;
  char op = '+';

  while (p < end) {

    while (p < end && *p == ' ')
      ++p;

    long long number = 0;

    while (p < end && *p >= '0' && *p <= '9') {
      number = number * 10 + (*p - '0');
      ++p;
    }

    // branch prediction
    switch (op) {
    case '+':
      result += last;
      last = number;
      break;
    case '-':
      result += last;
      last = -number;
      break;
    case '*':
      last = last * number;
      break;
    case '/':
      last = last / number;
      break;
    }

    while (p < end && *p == ' ')
      ++p;

    if (p < end)
      op = *p++;
  }

  return static_cast<int>(result + last);
}

/*
 *  using two-pass counter scan here
 *  T: O(n), S: O(1)
 */
int Purgatory::longestValidParentheses(string s) {
  // register vs memory
  const int n = s.size();
  int maxLen = 0;
  int left = 0, right = 0;

  for (int i = 0; i < n; ++i) {
    // register vs memory
    const char c = s[i];
    // branch prediction
    left += (c == '(');
    right += (c == ')');

    if (left == right) {
      // function call
      const int len = right << 1;
      maxLen = maxLen > len ? maxLen : len;
    } else if (right > left) {
      left = right = 0;
    }
  }

  left = right = 0;
  for (int i = n - 1; i >= 0; --i) {
    // register vs memory
    const char c = s[i];
    // branch prediction
    left += (c == '(');
    right += (c == ')');

    if (left == right) {
      // function call
      const int len = left << 1;
      maxLen = maxLen > len ? maxLen : len;
    } else if (left > right) {
      left = right = 0;
    }
  }

  return maxLen;
}

bool Purgatory::backspaceCompare(string s, string t) {
  int i = s.size() - 1, j = t.size() - 1;
  int skipS = 0, skipT = 0;

  while (i >= 0 || j >= 0) {
    while (i >= 0) {
      // register vs memory
      const char c = s[i];
      // branch prediction
      if (c == '#') {
        ++skipS;
        --i;
      } else if (skipS > 0) {
        --skipS;
        --i;
      } else {
        break;
      }
    }

    while (j >= 0) {
      // register vs memory
      const char c = t[j];
      // branch prediction
      if (c == '#') {
        ++skipT;
        --j;
      } else if (skipT > 0) {
        --skipT;
        --j;
      } else {
        break;
      }
    }

    // branch prediction
    if (i < 0 || j < 0)
      return i == j;

    if (s[i] != t[j])
      return false;

    --i;
    --j;
  }

  return true;
}

int Purgatory::findUnsortedSubarray(const vector<int> &nums) {
  const int n = nums.size();

  if (n < 2)
    return 0;

  int left = n, right = -1;

  int curMax = nums[0];
  int curMin = nums[n - 1];

  for (int i = 1, j = n - 2; i < n; ++i, --j) {
    const int forward = nums[i];
    const int backward = nums[j];

    curMax = (curMax > forward) ? curMax : forward;
    curMin = (curMin < backward) ? curMin : backward;

    right = (forward < curMax) ? i : right;
    left = (backward > curMin) ? j : left;
  }

  return (right < 0) ? 0 : right - left + 1;
}

int Purgatory::carFleet(int target, vector<int> &position, vector<int> &speed) {
  const int n = position.size();

  // cache behavior
  vector<pair<int, int>> cars;

  for (int i = 0; i < n; ++i) {
    cars.push_back(make_pair(position[i], speed[i]));
  }

  sort(cars.begin(), cars.end());

  int fleets = 0;
  double maxTime = -1.0;

  for (int i = n - 1; i >= 0; --i) {
    const double time =
        static_cast<double>(target - cars[i].first) / cars[i].second;

    // branch prediction
    if (time > maxTime) {
      maxTime = time;
      ++fleets;
    }
  }

  return fleets;
}

int Purgatory::sumSubarrayMins(vector<int> &arr) {
  const long long MOD = 1e9 + 7;

  struct Entry {
    int value;
    int count;
  };

  // cache behavior
  vector<Entry> st;
  st.reserve(arr.size());

  long long currentSum = 0;
  long long result = 0;

  for (const int value : arr) {
    int count = 1;

    while (!st.empty() && st.back().value >= value) {
      const Entry top = st.back();
      st.pop_back();

      count += top.count;

      currentSum -= static_cast<long long>(top.value) * top.count;
    }

    st.push_back({value, count});

    currentSum += static_cast<long long>(value) * count;

    currentSum %= MOD;
    result += currentSum;
    result %= MOD;
  }

  return static_cast<int>(result);
}

string Purgatory::removeOccurrences(const string &s, const string &part) {
  const int m = part.size();

  if (m == 0)
    return s;

  string result;
  result.reserve(m);

  const char lastChar = part[m - 1];

  for (char c : s) {
    result.push_back(c);

    const size_t size = result.size();

    if (size >= m && c == lastChar &&
        memcmp(&result[size - m], part.data(), m) == 0) {
      result.resize(size - m);
    }
  }

  return result;
}

static int removePattern(string &s, char a, char b, int score) {
  const int n = s.size();
  // cpu pipeline
  int write = 0;
  int total = 0;

  for (int read = 0; read < n; ++read) {
    // register vs memory
    const char c = s[read];

    // branch prediction
    if (write > 0 && s[write - 1] == a && c == b) {
      --write;
      total += score;
    } else {
      s[write++] = c;
    }
  }

  s.resize(write);
  return total;
}

int Purgatory::maximumGain(string s, int x, int y) {

  if (x >= y) {
    return removePattern(s, 'a', 'b', x) + removePattern(s, 'b', 'a', y);
  }

  return removePattern(s, 'b', 'a', y) + removePattern(s, 'a', 'b', x);
}

int Purgatory::addMinimum(string word) {
  const int n = word.size();

  if (n == 0)
    return 0;

  int groups = 1;
  char prev = word[0];

  for (int i = 1; i < n; ++i) {
    const char current = word[i];

    groups += (current <= prev);
    prev = current;
  }

  return groups * 3 - n;
}

long long Purgatory::calculateScore(string s) {
  // cache behavior
  vector<int> stacks[26];
  long long score = 0;
  const int n = s.size();

  for (int i = 0; i < n; ++i) {
    const int cur = s[i] - 'a';
    const int mirror = 25 - cur;

    // register vs memory
    vector<int> &stk = stacks[mirror];
    if (!stk.empty()) {
      const int index = stk.back();
      stk.pop_back();

      score += static_cast<long long>(i - index);
    } else {
      stacks[cur].push_back(i);
    }
  }

  return score;
}

int Purgatory::minLengthAfterRemovals(string s) {
  int balance = 0;

  for (char c : s) {
    // branch prediction
    balance += (c == 'a') ? 1 : -1;
  }

  return abs(balance);
}

int Purgatory::minLength(string s) {
  // cache behavior
  string stackBuffer;
  stackBuffer.reserve(s.size());

  // cpu pipelie
  for (char c : s) {
    if (!stackBuffer.empty()) {
      char top = stackBuffer.back();

      // branch prediction
      bool removable =
          ((top == 'A') && (c == 'B')) || ((top == 'C') && (c == 'D'));

      if (removable) {
        stackBuffer.pop_back();
        continue;
      }
    }

    stackBuffer.push_back(c);
  }

  return static_cast<int>(stackBuffer.size());
}

vector<int> Purgatory::exclusiveTime(int n, const vector<string> &logs) {
  vector<int> result(n, 0);
  // cache behavior
  stack<int> st;
  int prevTime = 0;

  for (const string &log : logs) {
    int id = 0, time = 0, i = 0;

    // cpu pipeline
    while (log[i] != ':')
      id = id * 10 + (log[i++] - '0');
    i++;

    bool isStart = (log[i] == 's');
    while (log[i] != ':')
      i++;
    i++;

    while (i < log.size())
      time = time * 10 + (log[i++] - '0');

    // branch prediction
    if (isStart) {
      if (!st.empty()) {
        result[st.top()] += time - prevTime;
      }

      st.push(id);
      prevTime = time;
    } else {
      result[st.top()] += time - prevTime + 1;
      st.pop();
      prevTime = time + 1;
    }
  }
  return result;
}

vector<string> Purgatory::buildArray(const vector<int> &target, int n) {
  // register vs memory
  int size = target.size();
  // cache behavior
  vector<string> st;
  st.reserve(n << 1);
  int index = 0;

  for (int num = 1; num <= n && index < size; ++num) {
    st.push_back("Push");

    if (num == target[index])
      ++index;
    else
      st.push_back("Pop");
  }

  return st;
}

long long Purgatory::subArrayRanges(const vector<int> &nums) {
  int n = nums.size();
  long long maxSum = 0, minSum = 0;

  // cache behavior
  stack<int> st;

  for (int i = 0; i <= n; ++i) {
    // register vs memory
    int current = (i == n) ? INT_MAX : nums[i];

    while (!st.empty() && current > nums[st.top()]) {
      int mid = st.top();
      st.pop();

      int left = st.empty() ? -1 : st.top();

      // register vs memory
      long long leftCount = mid - left;
      long long rightCount = i - mid;

      maxSum += 1LL * nums[mid] * leftCount * rightCount;
    }

    st.push(i);
  }

  while (!st.empty())
    st.pop();

  for (int i = 0; i <= n; ++i) {
    int current = (i == n) ? INT_MIN : nums[i];

    while (!st.empty() && current < nums[st.top()]) {
      int mid = st.top();
      st.pop();

      int left = st.empty() ? -1 : st.top();

      long long leftCount = mid - left;
      long long rightCount = i - mid;

      minSum += 1LL * nums[mid] * leftCount * rightCount;
    }

    st.push(i);
  }

  return maxSum - minSum;
}

string Purgatory::makeGood(string s) {
  // cache behavior
  string result;
  result.reserve(s.size());

  for (const char c : s) {
    if (!result.empty()) {
      const int diff = result.back() - c;

      // branch prediction
      if (diff == 32 || diff == -32) {
        result.pop_back();
        continue;
      }
    }

    result.push_back(c);
  }

  return result;
}

string Purgatory::reversePrefix(string word, char ch) {
  int targetIndex = -1;

  for (int i = 0; i < word.size(); ++i) {
    // branch prediction
    if (word[i] == ch) {
      targetIndex = i;
      break;
    }
  }

  if (targetIndex == -1)
    return word;

  // cpu pipelie
  for (int l = 0, r = targetIndex; l < r; ++l, --r) {
    char temp = word[l];
    word[l] = word[r];
    word[r] = temp;
  }

  return word;
}

bool Purgatory::checkValidString(string s) {
  int low = 0, high = 0;

  for (const char c : s) {
    // branch prediction
    switch (c) {
    case '(':
      ++low;
      ++high;
      break;
    case ')':
      --low;
      --high;
      break;
    default:
      --low;
      ++high;
    }

    if (high < 0)
      return false;
    if (low < 0)
      low = 0;
  }

  return low == 0;
}

string Purgatory::removeDuplicates(string s) {
  // cache behavior
  string stack;
  stack.reserve(s.size());

  for (const char c : s) {

    if (!stack.empty()) {
      const char letter = stack.back();
      // branch prediction
      if (letter == c) {
        stack.pop_back();
        continue;
      }
    }

    stack.push_back(c);
  }

  return stack;
}

bool Purgatory::find132pattern(const vector<int> &nums) {
  int n = nums.size();
  if (n < 3)
    return false;

  // cache behavior
  vector<int> st;
  st.reserve(n);
  int second = INT_MIN;

  for (int i = n - 1; i >= 0; --i) {
    // register vs memory
    int cur = nums[i];

    if (cur < second)
      return true;

    while (!st.empty()) {
      int top = st.back();

      // branch prediction
      if (top >= cur)
        break;

      second = top;
      st.pop_back();
    }

    st.push_back(cur);
  }

  return false;
}

int Purgatory::maxWidthRamp(const vector<int> &nums) {
  const int n = nums.size();
  if (n < 2)
    return 0;

  // cache behavior
  vector<int> st;
  st.reserve(n);

  for (int i = 0; i < n; ++i) {
    if (st.empty() || nums[i] < nums[st.back()]) {
      st.push_back(i);
    }
  }

  int result = 0;

  for (int j = n - 1; j >= 0; --j) {
    // register vs memory
    int val = nums[j];
    while (!st.empty()) {
      int i = st.back();

      // branch prediction
      if (val < nums[i])
        break;

      result = max(result, j - i);
      st.pop_back();
    }
  }

  return result;
}

string Purgatory::clearDigits(string s) {
  // cache behavior
  vector<char> st;
  st.reserve(s.size());

  for (const char c : s) {
    // branch prediction
    if (c >= '0' && c <= '9') {
      if (!st.empty())
        st.pop_back();
    } else {
      st.push_back(c);
    }
  }

  return string(st.begin(), st.end());
}

bool Purgatory::validateStackSequences(const vector<int> &pushed,
                                       const vector<int> &popped) {
  // cache behavior
  vector<int> stack;
  stack.reserve(pushed.size());
  int index = 0;

  for (const int val : pushed) {
    stack.push_back(val);
    while (!stack.empty() && stack.back() == popped[index]) {
      stack.pop_back();
      ++index;
    }
  }

  return stack.empty();
}

string Purgatory::minRemoveToMakeValid(string s) {
  int open = 0;
  // cache behavior
  string temp;
  temp.reserve(s.size());

  for (const char c : s) {
    if (c != '(' && c != ')') {
      temp.push_back(c);
    } else {
      if (c == '(') {
        ++open;
        temp.push_back(c);
      } else {
        // branch prediction
        if (open == 0)
          continue;

        temp.push_back(c);
        --open;
      }
    }
  }

  string result;
  result.reserve(temp.size());

  for (int i = temp.size() - 1; i >= 0; --i) {
    // branch prediction
    if (temp[i] == '(' && open > 0) {
      --open;
      continue;
    }

    result.push_back(temp[i]);
  }

  reverse(result.begin(), result.end());

  return result;
}

int Purgatory::totalSteps(const vector<int> &nums) {
  // cache behavior
  vector<pair<int, int>> st;
  int result = 0;

  for (const int num : nums) {
    int step = 0;

    while (!st.empty() && num >= st.back().first) {
      step = max(step, st.back().second);
      st.pop_back();
    }

    // branch prediction
    step = st.empty() ? 0 : step + 1;

    result = max(result, step);
    st.emplace_back(num, step);
  }

  return result;
}

int Purgatory::minOperations(const vector<string> &logs) {
  int result = 0;

  for (const string &log : logs) {
    // register vs memory
    char c = log[0];

    if (c == '.') {
      if (log[1] == '.') {
        if (result > 0)
          --result;
      }
    } else {
      ++result;
    }
  }
  return result;
}

int Purgatory::scoreOfParentheses(string s) {
  // register vs memory
  int depth = 0, count = 0;

  // cpu pipelie
  for (int i = 0; i < s.size(); ++i) {
    if (s[i] == '(') {
      ++depth;
    } else {
      --depth;

      // branch prediction
      if (s[i - 1] == '(') {
        count += (1 << depth);
      }
    }
  }

  return count;
}

int Purgatory::maximumPossibleSize(const vector<int> &nums) {
  int n = nums.size();
  int count = 1;
  int last = nums[0];

  // cpu pipelie
  for (int i = 1; i < n; ++i) {
    int curr = nums[i];

    if (curr >= last) {
      ++count;
      last = curr;
    }
  }

  return count;
}

void dfsPreorderTraversal(TreeNode *node, vector<int> &result) {
  // branch prediction
  if (!node)
    return;

  result.push_back(node->val);

  dfsPreorderTraversal(node->left, result);
  dfsPreorderTraversal(node->right, result);
}

vector<int> Purgatory::preorderTraversal(TreeNode *root) {
  vector<int> result;

  dfsPreorderTraversal(root, result);

  return result;
}

int Purgatory::maxBalanceShipments(const vector<int> &weight) {
  int n = weight.size();
  int count = 0;

  for (int i = 0; i < n;) {
    // branch prediction
    const bool split = weight[i] < weight[i - 1];
    count += split;

    i += split ? 2 : 1;
  }

  return count;
}

long long Purgatory::bowlSubarrays(const vector<int> &nums) {
  int n = nums.size();

  // cache behavior
  vector<int> stack;
  stack.reserve(n);

  long long count = 0;
  for (const int val : nums) {
    while (!stack.empty() && val > stack.back()) {
      stack.pop_back();

      // branch prediction
      if (!stack.empty())
        ++count;
    }

    stack.push_back(val);
  }

  return count;
}

vector<long long> Purgatory::mergeAdjacent(const vector<int> &nums) {
  int n = nums.size();
  // cache behavior
  vector<long long> result;
  result.reserve(n);

  for (const int num : nums) {
    result.push_back(num);

    while (result.size() >= 2) {
      // register vs memory
      const size_t top = result.size() - 1;
      const long long right = result[top];
      const long long left = result[top - 1];

      if (right != left)
        break;

      result.pop_back();
      result.back() = right + left;
    }
  }

  return result;
}

void dfsPostorderTraversal(TreeNode *node, vector<int> &result) {
  if (!node)
    return;

  dfsPostorderTraversal(node->left, result);
  dfsPostorderTraversal(node->right, result);

  result.push_back(node->val);
}

vector<int> Purgatory::postorderTraversal(TreeNode *root) {
  vector<int> result;
  // cache behavior
  result.reserve(100);

  dfsPostorderTraversal(root, result);

  return result;
}

string Purgatory::decodeAtIndex(string s, int k) {
  long long size = 0;

  for (const char c : s) {
    if (!isdigit(c)) {
      size += 1;
    } else {
      size *= (c - '0');
    }
  }

  for (int i = s.size() - 1; i >= 0; --i) {
    char c = s[i];

    // cpu pipelie
    if (c >= '2' && c <= '9') {
      int d = c - '0';
      size /= d;
      if (k > size)
        k %= size;
    } else {
      // branch prediction
      if (k == 0 || k == size) {
        return string(1, c);
      }
      --size;
    }
  }
  return "";
}

bool Purgatory::isValidString(string s) {
  string st;
  // cache behavior
  st.reserve(s.size());

  for (char c : s) {
    st.push_back(c);
    int n = st.size();

    // branch prediction
    if (n >= 3 && st[n - 3] == 'a' && st[n - 2] == 'b' && st[n - 1] == 'c') {
      st.resize(n - 3);
    }
  }
  return st.empty();
}

} // namespace purgatory
