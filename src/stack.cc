#include "purgatory.h"

namespace purgatory {

/*
 *  using a stack-based solution here because parentheses matching is naturally Last In First Out
 */
bool Purgatory::isValid(string s) {
    stack<char> st;

    for (char c: s) {
        if (c == '(' || c == '{' || c == '[') {
	    st.push(c);
	} else {
            if (st.empty()) return false;

	    char top = st.top(); st.pop();

	    if ( (c == ')' && top != '(') ||
	         (c == '}' && top != '{') ||
		 (c == ']' && top != '[') ) {
	        return false;
	    }
	}
    }
    return st.empty();
}

/*
 *  using a stack-based solution here because it naturally models directory traversal. This problem can be broken down into tokenizing by /, then applying rules for ".", "..", and normal names.
 */
string Purgatory::simplifyPath(string path) {
    vector<string> stack;

    string token;
    stringstream ss(path);

    while(getline(ss, token, '/')) {
        if (token == "" || token == ".") {
            continue;
	} else if (token == "..") {
	    if (!stack.empty()) stack.pop_back();
	} else {
	    stack.push_back(token);
	}
    }

    string result = "/";
    for (int i = 0; i < (int) stack.size(); ++i) {
        result += stack[i];

	if (i != stack.size() -1) result += "/";
    }
    return result;
}

/*
 *  using a stack-based evaluation here because RPN naturally maps to push/pop operations
 */
int Purgatory::evalRPN(vector<string>& tokens) {
    stack<int> st;

    for (auto &tok: tokens) {
        if (tok == "+" || tok == "-" || tok == "*" || tok == "/") {
            int b = st.top(); st.pop();
	    int a = st.top(); st.pop();

	    int res = 0;

	    if (tok == "+") res = a + b;
	    else if (tok == "-") res = a - b;
	    else if (tok == "*") res = a * b;
	    else if (tok == "/") res = a / b;

	    st.push(res);
	} else {
	    st.push(stoi(tok));
	}
    }
    return st.top();
}

/*
 *  using a stack to store cotext when entering parentheses here because this allows linear traversal.
 */
int Purgatory::calculate(string s) {
    stack<int> st;
    int result = 0;
    int sign = 1;
    int n = s.size();

    for (int i = 0; i < n; ++i) {
        char c = s[i];

	if (isdigit(c)) {    
            int num = 0;

	    while (i < n && isdigit(s[i])) {
	        num = num*10 + (s[i] - '0');
	        i++;
	    }
	    i--;
	    result += sign*num;
	} else if (c == '+') {
	    sign = 1;
	} else if (c == '-') {
	    sign = -1;
	} else if (c == '(') {
            st.push(result);
	    st.push(sign);
	    result = 0;
	    sign = 1;
	} else if (c == ')') {
            int prevSign = st.top(); st.pop();
	    int prevResult = st.top(); st.pop();

	    result = prevResult + prevSign*result;
	} else if (c == ' ') {
	    continue;
	}	
    }

    return result;
}

/*
 *  using a monotonic decreasing stack here because we can break the problem into computing next greater element in linear time
 *  T: O(m + n), S: O(n)
 */
vector<int> Purgatory::nextGreaterElement(vector<int>& nums1, vector<int>& nums2) {
    unordered_map<int, int> nge;
    stack<int> st;

    for (int num : nums2) {
        while(!st.empty() && st.top() < num) {
	    nge[st.top()] = num;
	    st.pop();
	}
	st.push(num);
    }

    while (!st.empty()) {
        nge[st.top()] = -1;
	st.pop();
    }

    vector<int> result;
    result.reserve(nums1.size());

    for (int x : nums1) {
        result.push_back(nge[x]);
    }

    return result;
}

/*
 *  using a greedy + monotonic stack approach here because we can break the problem into pop a character if it reapears later and would lead to a smaller lexicographical result.
 *  T: O(n), S: O(1)
 */
string Purgatory::removeDuplicateLetters(string s) {
    vector<int> last(26, 0);

    for (int i = 0; i < (int) s.size(); ++i) {
        last[s[i] - 'a'] = i;
    }

    vector<bool> inStack(26, false);
    string st;

    for (int i = 0; i < (int)s.size(); ++i) {
        char c = s[i];

	if (inStack[c - 'a'])
	    continue;

	while(!st.empty() && st.back() > c && last[st.back() - 'a'] > i) {
            inStack[st.back() - 'a'] = false;
	    st.pop_back();
	}

	st.push_back(c);
	inStack[c - 'a'] = true;
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

    vector<long> st;

    for (int i = 0; i < n; ++i) {
        char c = s[i];

	if (isdigit(c))
	    current = current*10 + (c-'0');

	if ( (!isdigit(c) && c != ' ') || i == n - 1) {
            if (lastOp == '+') {
	        st.push_back(current);
	    } else if (lastOp == '-') {
                st.push_back(-current);
	    } else if (lastOp == '*') {
                st.back() = st.back() * current;
	    } else if (lastOp == '/') {
                st.back() = st.back() / current;
	    }

	    current = 0;
	    lastOp = c;
	}
    }

    long result = 0;
    for (long x : st)
        result += x;

    return (int) result;
}

/*
 *  using two-pass counter scan here
 *  T: O(n), S: O(1)
 */
int Purgatory::longestValidParentheses(string s) {
    int maxLen = 0;

    int left = 0, right = 0;

    for (char c : s) {
        if (c == '(')
	    left++;
	else
	    right++;

	if (left == right) {
	    maxLen = max(maxLen, 2 * right);
	} else if (right > left) {
	    left = right = 0;
	}
    }

    left = right = 0;
    for (int i = s.size() - 1; i >= 0; --i) {

        if (s[i] == '(')
	    left++;
        else
            right++;
    
        if (left == right) {
	    maxLen = max(maxLen, 2 * left);
	} else if (left > right) {
	    left = right = 0;
	}
    }

    return maxLen;
}


}
