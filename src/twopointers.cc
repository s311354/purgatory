#include "purgatory.h"

namespace purgatory {

/*
 *  using two-pointer method here becuase
 *  - we can skip non-alphanumeric characters in-place without building a new filtered string
 *  - this reduce extra memory usage to O(1)
 *  T: O(n), S: O(1)
 */

// function call & branch prediction
inline bool isAlnum(char c) {
    return (c >= 'a' && c <= 'z') ||
	   (c >= 'A' && c <= 'Z') ||
	   (c >= '0' && c <= '9');
}

inline char toLower(char c) {
    return (c >= 'A' && c <= 'Z') ? c + 32 : c;
}

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

	if (l != r) return false;

	left++; right--;
    }

    return true;
}

/*
 *  using two pointers here because the input is sorted
 *  T: O(n), S: O(n)
 */
vector<int> Purgatory::twoSum(vector<int>& numbers, int target) {
    // register vs memory
    int n = numbers.size();
    unordered_map<int, int> seen;
    // cache behavior
    seen.reserve(n);

    for (int i = 0; i < n; ++i) {
	// register vs memory
	int num = numbers[i];
        int complement = target - num;

	// branch prediction
	auto it = seen.find(complement);
	if (it != seen.end()) {
	    return {it->second, i};
	}

	seen[num] = i;
    }
    
    return {};
}

/*
 *  using two pointers here because we can break the problme into repeatedly eliminating impossible pairs. We always move the pointer at the shorter height inward because that's the only way to potentially increase area.
 *  T: O(n), S: O(1)
 */
int Purgatory::maxArea(vector<int> &height) {
    int left = 0, right = height.size() - 1;
    int maxWater = 0;

    while (left < right) {
	// register vs memory
	int hl = height[left];
	int hr = height[right];

	int width = right - left;
	int area = (hl < hr ? hl : hr) * width;
        
	// function call
	if (area > maxWater) maxWater = area;

	// branch prediction
	if (hl < hr)
	    ++left;
        else
	    --right;
    }

    return maxWater;
}

/*
 *  using two pointers here becuase we can break the problem into continuously shrinking the search space from both ends, while keeping track of the max heights seen so far.
 *  T: O(n), S: O(1)
 */
int Purgatory::trap(vector<int> & height) {
    int left = 0, right = height.size() - 1;
    int leftMax = 0, rightMax = 0;
    int water = 0;

    while (left < right) {
	// register vs memory
        int hl = height[left], hr = height[right];
        if (hl < hr) {
	    // function call
	    if (hl > leftMax)
	        leftMax = hl;

            water += leftMax - hl;
	    left++;
	} else {
	    if (hr > rightMax)
	        rightMax = hr;

	    water += rightMax - hr;
	    right--;
	}
    }

    return water;
}

/*
 *  using symmetry-based in-place here because we can break the problem into pairwise swapping from both ends
 *  T: O(n), S: O(1)
 */
void Purgatory::reverseString(vector<char>& s) {
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
 * using the dutch national flag algorithm here because we can break the problem into three regions
 * T: O(n), S: O(1)
 */
void Purgatory::sortColors(vector<int>& nums) {
    // register vs memory
    int *l = &nums[0];
    int *m = &nums[0];
    int *r = &nums[nums.size() - 1];

    while ( m <= r) {
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
 *  using two-pointer parsing method here because we can break the problem into small numeric segments without splitting strings
 *  T: O(n + m), S: O(1)
 */
int Purgatory::compareVersion(string version1, string version2) {
    // register vs memory
    const char *p1 = version1.c_str();
    const char *p2 = version2.c_str();

    while (*p1 || *p2) {
        long num1 = 0, num2 = 0;

	while (*p1 && *p1 != '.') {
            num1 = num1*10 + (*p1 - '0');
	    ++p1;
	}

	while (*p2 && *p2 != '.') {
             num2 = num2*10 + (*p2 - '0');
	     ++p2;
	}


	// branch prediction
	if (num1 != num2) 
	    return num1 < num2 ? -1 : 1;

	if (*p1 == '.') ++p1;
        if (*p2 == '.') ++p2;	
    }

    return 0;
}

vector<int> maxSubsequence(vector<int>& nums, int k) {
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
        i++; j++;
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
        if ( greaterVec(a, i, b, j)) {
            result.push_back(a[i++]);
	} else {
            result.push_back(b[j++]);
	}
    }

    return result;
}

/*
 *  using greedy monotonic stack + lexicographic merge hear because we can break the problem into 
 *  - selecting best subsequence from each array
 *  - merging them optimally
 *  - trying all possible divisons
 *  T:((M + N)^2), S:O(K)
 */
vector<int> Purgatory::maxNumber(vector<int>& nums1, vector<int>& nums2, int k) {
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
    if (n <= 0) return 0;
    if (n <= 3) return 1;

    vector<int> s(n);
    s[0] = 1; s[1] = 2; s[2] = 2;

    int read = 2;
    int write = 3;
    int num = 1;
    int count = 1;

    while (write < n) {
	// cpu pipeline
        int len = s[read++];

	for (int i = 0; i < len && write < n ; ++i) {

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

    if (n1 > n2) return false;

    // cache behavior
    int freq[26] = {0};

    for (char c : s1) freq[c - 'a']++;

    int count = n1;

    for (int i = 0; i < n2; ++i) {
        if (freq[s2[i] - 'a']-- > 0) count--;

	// branch prediction
	if (i >= n1)
	    if (freq[s2[i - n1] - 'a'] >= 0) count++;

	if (count == 0) return true;
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

	if (sum == c) return true;
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

int Purgatory::removePalindromeSub(string s) {
    // cache behavior
    const char *l = s.data();
    const char *r = l + s.size() - 1;

    while (l < r) {
	// branch prediction
        if (*r != *l) return 2;
        ++l;
	--r;
    }
    return 1;
}

int Purgatory::findRadius(vector<int> &houses, vector<int> &heaters) {
    // cpu pipeline
    sort(houses.begin(), houses.end());
    sort(heaters.begin(), heaters.end());

    int i = 0;
    int maxRadius = 0;

    for (int house : houses) {
	// branch prediction
        while (i < heaters.size() - 1 &&
		abs(heaters[i + 1] - house) <= abs(heaters[i] - house)) {
	    ++i;
	}

	maxRadius = max(maxRadius, abs(heaters[i] - house));
    }

    return maxRadius;
}

bool Purgatory::circularArrayLoop(vector<int> &nums) {
    int n = nums.size();

    for (int i = 0; i < n; ++i) {
        if (nums[i] == 0) continue;

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
	    if ( ((valSlow > 0) != isForward) |
	         ((valFast1 > 0) != isForward) |
		 ((valFast2 > 0) != isForward))
                break;

	    slow = nextSlow;
	    fast = nextFast;

	    if (slow == fast) {
                int next = slow + nums[slow];

		if (next >= 0 || next < 0)
		    next = (next % n + n) % n;

		if (next == slow) break;

		return true;
	    } 
	}

	int cur = i;

	while (true) {
	    // register vs memory
            int step = nums[cur];

	    if ((step > 0) != isForward) break;

	    int nxt = cur + step;

	    if (nxt >= n || nxt < 0) 
	        nxt = (nxt % n + n) % n;

	    nums[cur] = 0;

	    if (nxt == cur) break;

	    cur = nxt;
	}
    }

    return false;
}

int Purgatory::maxProfitAssignment(vector<int> &difficulty, vector<int> &profit, vector<int> &worker) {
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

	    if (d > w) break;

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

}
