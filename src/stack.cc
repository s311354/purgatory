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




}
