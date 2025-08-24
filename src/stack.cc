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
	         (c == '{' && top != '}') ||
		 (c == '[' && top != ']') ) {
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




}
