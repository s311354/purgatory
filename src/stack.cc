#include "purgatory.h"

namespace purgatory {

/*
 *  using a stack-based solution here because parentheses matching is naturally Last In First Out
 *  T: O(n), S: O(n)
 */
bool Purgatory::isValid(string s) {
    // cache behavior
    vector<char> st;
    st.reserve(s.size());

    // cpu pipelie
    auto match = [](unsigned char c) -> char {
       if (c == ')') return '(';
       if (c == ']') return '[';
       if (c == '}') return '{';
       return 0;
    };

    for (char c: s) {
	char m = match(c);
	if (m) {
	    // branch prediction
            if (st.empty() || st.back() != m)
                return false;

	    st.pop_back();
	} else {
	    st.push_back(c);
	}
    }
    return st.empty();
}

/*
 *  using a stack-based solution here because it naturally models directory traversal. This problem can be broken down into tokenizing by /, then applying rules for ".", "..", and normal names.
 *  T: O(n), S: O(n)
 */
string Purgatory::simplifyPath(string path) {
    int n = path.size();
    // cache behavior
    vector<string> stack;
    stack.reserve(n);

    int i = 0;
    // cpu pipeline
    while (i < n) {
        while (i < n && path[i] == '/') ++i;

	int start = i;

	while (i < n && path[i] != '/') ++i;

	int len = i - start;

	if (len == 0) continue;

        if (len == 1 && path[start] == '.')
	    continue;

	// branch prediction
	if (len == 2 && path[start] == '.' && path[start + 1] == '.') {
	    if (!stack.empty()) stack.pop_back();
	} else {
	    stack.emplace_back(path.substr(start, len));
	}
    }
    
    if (stack.empty()) return "/";

    string result;
    result.reserve(path.size());

    for (const string &dir : stack) {
        result.push_back('/');
        result.append(dir);
    }

    return result;
}

/*
 *  using a stack-based evaluation here because RPN naturally maps to push/pop operations
 *  T: O(n), S: O(n)
 */
int Purgatory::evalRPN(vector<string>& tokens) {
    // cache behavior
    vector<int> st;
    st.reserve(tokens.size());


    for (const string &tok: tokens) {
	// branch prediction
        if (tok.size() == 1 && !isdigit(tok[0])) {
            int b = st.back(); st.pop_back();
	    int a = st.back(); st.pop_back();

	    // register vs memory
	    char op = tok[0];

	    if (op == '+') st.push_back(a + b);
	    else if (op == '-') st.push_back(a - b);
	    else if (op == '*') st.push_back(a * b);
	    else if (op == '/') st.push_back(a / b);
	} else {
	    // function call
            int num = 0, sign = 1, i = 0;

	    if (tok[0] == '-') {
	        sign = -1;
		i = 1;
	    }

	    for (;i < tok.size();++i) {
	        num = num * 10 + (tok[i] - '0');
	    }

	    st.push_back(sign * num);
	}
    }
    return st.back();
}

/*
 *  using a stack to store cotext when entering parentheses here because this allows linear traversal.
 *  T: O(n), S: O(n)
 */
int Purgatory::calculate(string s) {
    // cache behavior
    vector<int> signs;
    signs.reserve(64);
    signs.push_back(1);

    int result = 0;
    int sign = 1;

    // cpu pipeline
    const char *p = s.c_str();

    while(*p) {
	char c = *p;
	
	// branch prediction
	if (c >= '0' && c <= '9') {    
            long long number = 0;
            
	    while (*p >= '0' && *p <= '9') {
                number = number * 10 + (*p - '0');
	        ++p;
	    }	
	    result += sign*number;
	    continue;
	} else if (c == '+') {
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

    return result;
}

/*
 *  using a monotonic decreasing stack here because we can break the problem into computing next greater element in linear time
 *  T: O(m + n), S: O(n)
 */
vector<int> Purgatory::nextGreaterElement(vector<int>& nums1, vector<int>& nums2) {
    // cache behavior
    vector<int> next(10001, -1);
    vector<int> st;
    st.reserve(nums2.size());


    for (int x : nums2 ) {	    
	// register vs memory
	int top;
        while(!st.empty() && x > (top = st.back())) {
	    next[top] = x;
	    st.pop_back();
	}

	st.push_back(x);
    }
    
    while (!st.empty()) {
        next[st.back()]= -1;
	st.pop_back();
    }

    vector<int> result;
    result.reserve(nums1.size());

    for (int x : nums1) {
        result.push_back(next[x]);
    }

    return result;
}

/*
 *  using a greedy + monotonic stack approach here because we can break the problem into pop a character if it reapears later and would lead to a smaller lexicographical result.
 *  T: O(n), S: O(1)
 */
string Purgatory::removeDuplicateLetters(string s) {
    // cache behavior
    int last[256];
    for (int i = 0; i < 256; ++i)
        last[i] = -1;

    int n = s.size();
    for (int i = 0; i < n; ++i)
        last[(unsigned char) s[i]] = i;

    // cache behavior
    bool inStack[256] = {false};
    string st;
    st.reserve(n);

    for (int i = 0; i < n; ++i) {
        char c = s[i];

	if (inStack[(unsigned char) c])
	    continue;

	// branch prediction
	while(!st.empty()) {
	    char top = st.back();

	    if (top <= c) break;
	   
	    if (last[(unsigned char) top] <= i) break;

            inStack[(unsigned char) top] = false;
	    st.pop_back();
	}

	st.push_back(c);
	inStack[(unsigned char) c] = true;
    }

    return st;
}

/*
 *  using a single pass + stack approach here becuase we cn break the expression into terms. This handles operator precedence naturally.
 * T: O(n), S: O(n)
 */
int Purgatory::calculateII(string s) {
    int n = s.size();
    long current = 0;
    char lastOp = '+';
    long result = 0;
    long last = 0;

    for (int i = 0; i < n; ++i) {
        char c = s[i];

	// function call
	if (c >= '0' && c <= '9')
	    current = current*10 + (c-'0');

	// branch prediction
	bool isLast = (i == n - 1);
	bool isOp = !(c >= '0' && c <= '9') && c != ' ';
	if (isOp || isLast) {
	    // branch prediction
            switch (lastOp) {
	        case '+':
                    result += last;
		    last = current;
		    break;
	        case '-':
	            result += last;
		    last = -current;
                    break;
	        case '*':
	            last = last * current;
		    break;
	        case '/':
                    last = last / current;
		    break;
	    }

	    current = 0;
	    lastOp = c;
	}
    }


    return (int) result + last;
}

/*
 *  using two-pass counter scan here
 *  T: O(n), S: O(1)
 */
int Purgatory::longestValidParentheses(string s) {
    // register vs memory
    int n = s.size();
    int maxLen = 0;

    int left = 0, right = 0;

    for (int i = 0; i < n ; ++ i) {
	// register vs memory
        char c = s[i];
	// branch prediction
	left += (c =='(');
	right += (c == ')');

	if (left == right) {
	    // function call
	    int len = right << 1;
	    maxLen = maxLen > len ? maxLen : len;
	} else if (right > left) {
	    left = right = 0;
	}
    }

    left = right = 0;
    for (int i = n - 1; i >= 0; --i) {
	// register vs memory
        char c = s[i];
	// branch prediction
	left += (c == '(');
        right += (c == ')');
    
        if (left == right) {
            // function call
	    int len = left << 1;
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

    while (true) {
        while (i >= 0) {
            // register vs memory
            char c = s[i--];
	    // branch prediction
	    if (c == '#') skipS++;
	    else if (skipS > 0) skipS--;
	    else {
	        ++i;
		break;
	    }
	}

	while (j >= 0) {
            // register vs memory
            char c = t[j--];
	    // branch prediction
	    if (c == '#') skipT++;
	    else if (skipT > 0) skipT--;
	    else {
	        ++j;
		break;
	    }
	}

	// branch prediction
        if (i < 0 || j < 0) return i == j;

	if (s[i] != t[j]) return false;

	--i; --j;
    }
}

int Purgatory::findUnsortedSubarray(vector<int>& nums) {
    int n = nums.size();
    int left = n, right = -1;

    int curMax = nums[0];
    int curMin = nums[n - 1];

    for (int i = 1; i < n; ++i) {
        curMax = max(curMax, nums[i]);
	if (nums[i] < curMax) right = i;

	int j = n - 1 - i;
	curMin = min(curMin, nums[j]);
	if (nums[j] > curMin) left = j;
    }

    return right == -1 ? 0 : right - left + 1;
}


int Purgatory::carFleet(int target, vector<int>& position, vector<int>& speed) {
    int n = position.size();

    // cache behavior
    vector<int> idx(n);
    iota(idx.begin(), idx.end(), 0);
    sort(idx.begin(), idx.end(), [&](int a, int b) {
        return position[a] < position[b];	
    });

    int fleets = 0;
    double maxTime = 0;

    for (int i = n - 1; i >= 0; --i) {
        int id = idx[i];
	double time = (double) (target - position[id]) / speed[id];

	// branch prediction
	if (time > maxTime) {
	    fleets++;
	    maxTime = time;
	}
    }

    return fleets;
}

int Purgatory::sumSubarrayMins(vector<int>& arr) {
    const int MOD = 1e9 + 7;
    int n = arr.size();

    // cache behavior
    vector<int> left(n), right(n), stack(n);
    int top = -1;

    for (int i = 0; i < n; ++i) {
        while (top >= 0 && arr[stack[top]] > arr[i]) {
	    --top;
	}

	left[i] = (top < 0) ? (i + 1) : (i - stack[top]);
	stack[++top] = i;
    }

    top = -1;

    for (int i = n - 1; i >= 0; --i) {
        while (top >= 0 && arr[stack[top]] >= arr[i]) {
            top--;
	}

	right[i] = (top < 0) ? (n - i) : (stack[top] - i);
	stack[++top] = i;
    }

    long long result = 0;

    for (int i = 0; i < n; ++i) {
        result = result + (long long) arr[i] * left[i] * right[i] % MOD;
    }

    return (int) result;
}

string Purgatory::removeOccurrences(string s, string part) {
    string result;

    int m = part.size();

    for (char c : s) {
        result.push_back(c);

	if (result.size() >= m) {
	    // branch prediction
            if (memcmp(&result[result.size() - m], part.data(), m) == 0) 
                result.resize(result.size() - m);
	}
    }

    return result;
}

int removePattern(string &s, char a, char b, int score) {
    int n = s.size();
    // cpu pipeline
    int write = 0;
    int total = 0;

    for (int read = 0; read < n; ++read) {
	// register vs memory
        char c = s[read];

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
    int result = 0;

    if (x > y) {
        result += removePattern(s, 'a', 'b', x);
	result += removePattern(s, 'b', 'a', y);
    } else {
        result += removePattern(s, 'b', 'a', y);
	result += removePattern(s, 'a', 'b', x);
    }
    
    return result;
}

int Purgatory::addMinimum(string word) {
    int insertions = 0;
    int expected = 0;

    for (char c : word) {
	// register vs memory
        int cur = c - 'a';

	// branch prediction
	while (cur != expected) {
	    ++insertions;
	    expected = (expected + 1) % 3;
	}

	expected = (expected + 1) % 3;
    }

    if (expected != 0)
        insertions += (3 - expected);

    return insertions;
}

long long Purgatory::calculateScore(string s) {
    // cache behavior
    vector<int> stacks[26];
    long long score = 0;

    for (int i = 0; i < s.size(); ++i) {
        int cur = s[i] - 'a';
	int mirror = 25 - cur;

	// register vs memory
	auto &stk = stacks[mirror];
	if (!stk.empty()) {
            score += i - stk.back();
	    stk.pop_back();
	} else {
	    stacks[cur].push_back(i);
	}
    }

    return score;
}

int Purgatory::minLengthAfterRemovals(string s) { 
    int balance = 0;

    for (char c:s) {
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
	    bool removable = ((top == 'A') && (c == 'B')) || ((top == 'C') && (c == 'D'));

	    if (removable) {
                stackBuffer.pop_back();
		continue;
	    } 
	}

	stackBuffer.push_back(c);
    }

    return static_cast<int>(stackBuffer.size());
}

vector<int> Purgatory::exclusiveTime(int n, vector<string> &logs) {
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
	while (log[i] != ':') i++;
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

vector<string> Purgatory::buildArray(vector<int> & target, int n) {
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

long long Purgatory::subArrayRanges(vector<int> &nums) {
    int n = nums.size();
    long long maxSum = 0, minSum = 0;

    // cache behavior
    stack<int> st;

    for (int i = 0; i <= n; ++i) {
	//register vs memory
        int current = (i == n) ? INT_MAX : nums[i];

	while (!st.empty() && current > nums[st.top()]) {
	    int mid = st.top();
	    st.pop();

	    int left = st.empty() ? -1 : st.top();

	    // register vs memory
	    long long leftCount = mid - left;
	    long long rightCount = i - mid;

	    maxSum += 1LL*nums[mid] * leftCount * rightCount; 
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

	    minSum += 1LL*nums[mid] * leftCount * rightCount;
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

    if (targetIndex == -1) return word;

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
        switch(c) {
            case '(':
	        ++low; ++high;
		break;
	    case ')':
		--low; --high;
		break;
	    default:
		--low; ++high;
	}

	if (high < 0) return false;
	if (low < 0) low = 0;
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

bool Purgatory::find132pattern(vector<int> &nums) {
    int n = nums.size();
    if (n < 3) return false;

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
	    if (top >= cur) break;
            
	    second = top;
	    st.pop_back();
	}

	st.push_back(cur);
    }

    return false;
}

int Purgatory::maxWidthRamp(vector<int> &nums) {
    const int n = nums.size();
    if (n < 2) return 0;

    // cache behavior
    vector<int> st;
    st.reserve(n);

    for (int i = 0; i < n; ++i) {
        if (st.empty() || nums[i] < nums[st.back()]) {
	    st.push_back(i);
	}
    }

    int result = 0;

    for (int j = n - 1; j >= 0; --j ) {
	// register vs memory
        int val = nums[j];
	while (!st.empty()) {
            int i = st.back();

	    // branch prediction
	    if (val < nums[i]) break;

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

bool Purgatory::validateStackSequences(vector<int> &pushed, vector<int> &popped) {
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

int Purgatory::totalSteps(vector<int> &nums) {
    // cache behavior
    vector<pair<int, int>> st;
    int result = 0;

    for (const int num: nums) {
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


}
