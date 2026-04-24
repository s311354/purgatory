#include "purgatory.h"

namespace purgatory {

Purgatory::Purgatory() {};
Purgatory::Purgatory(istream& s) {};
Purgatory::~Purgatory() {};

/*
 *  we are using a two-pointer approach with variables first and second to track
 *  potential increasing subsequence candidates. It lets us break the problem
 *  into three candidates:
 *  - update first to smallest
 *  - update second if it's larger than first
 *  - if a third number is larger than second, we're done
 *  T: O(n), S: O(1)
 */
bool Purgatory::increasingTriplet(vector<int>& nums) {
    // initalize: first and second 
    int first = INT_MAX, second = INT_MAX;

    for (int num : nums) {
	// update first
        if (num <= first) first = num;
	// update second
	else if (num <= second) second = num;
	// a < b < c
	else return true;
    }

    return false;
}

/*
 *  using reverse two-pointer merge here because we can break the problem into
 *  - comparing elements from the back
 *  - inserting in-place from the end of nums1
 *  - only copying remaining nums2 if needed
 *  T: O(n), S: O(1)
 */
void Purgatory::merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
    int p1 = m - 1, p2 = n - 1, p = m + n - 1;

    // Loop optimization
    while ( p2 >= 0 ) {
	// branch prediction
        if ( p1 >= 0) {
	    // register vs memory
	    int x = nums1[p1];
	    int y = nums2[p2];

	    bool take_p1 = x > y;

	    nums1[p] = take_p1 ? x : y;
	    p1 -= take_p1;
	    p2 -= !take_p1;
	} else {
	    nums1[p] = nums2[p2];
	    --p2;
	}
	--p;
    }
}

/*
 *  using two pointer technique here because we can break the problem into
 *  1. one pointer to read each element, read
 *  2. one pointer to write valid entries, write
 *  T:O(n), S:O(1)
 */
int Purgatory::removeDuplicates(vector<int>& nums) {
    // register vs memory
    int n = nums.size();
    if (n < 2) return n;

    int write = 2;

    // register vs memory
    int last2 = nums[0];
    int last1 = nums[1];

    for (int read = 2; read < n; ++read) {

        int curr = nums[read];
        // branch prediction
	int keep = (curr != last2);

	nums[write] = curr;
	write += keep;

	if (keep) {
	    last2 = last1;
	    last1 = curr;
	}
    }

    return write;
}

/*
 *  using reverse-in-place trick here because we can break the problem into 
 *  - reverse full array
 *  - reverse prefix
 *  - reverse suffix
 *  T: O(n), S: O(1)
 */
inline void reverse_int(int *l, int *r) {
    while (l < r) {
        int tmp = *l;
	*l++ = *r;
	*r-- = tmp;
    }
}

void Purgatory::rotate(vector<int> & nums, int k) {
    int n = nums.size();

    k %= n;

    if (k == 0) return;

    // cache behavior
    int *base = nums.data();

    reverse_int(base, base + n - 1);
    reverse_int(base, base + k - 1);
    reverse_int(base + k, base + n - 1);
}

/*
 *  using two-pass greedy method here because we can break the problem into two directional constraints
 *  - left to right handles increasing sequences
 *  - right to left handles decreasing sequences
 *  T: O(n), S: O(n)
 */
int Purgatory::candy(vector<int>& ratings) {
    int n = ratings.size();
    if (n == 0) return 0;

    vector<int> candies(n, 1);

    // branch prediction
    int prev = 1;
    candies[0] = 1;

    for (int i = 1; i < n; ++i) {
	// cache behavior
        prev = (ratings[i] > ratings[i - 1]) ? prev + 1 : 1;
	candies[i] = prev;
    }

    // loop optimization
    int total = candies[n - 1];

    for (int i = n - 2; i >= 0; --i) {
        if (ratings[i] > ratings[i + 1]) {
	    candies[i] = max(candies[i], candies[i + 1] + 1);
	}

	total += candies[i];
    }

    return total;
}

/*
 *  using two pointers here because it helps us process the array in-place without needing extra memory.
 *  T: O(n), S: O(1)
 */
int Purgatory::removeElemet(vector<int>& nums, int val) {
    int write = 0;
    // register vs memory
    int n = nums.size();

    for (int read = 0; read < n; ++read) {
	// branch prediction
        int keep = (nums[read] != val );
	nums[write] = nums[read];
	write += keep;
    }

    return write;

}

/*
 *  using a greedy strategy here because each step we only care about the farthest we can reach from all previous positions
 *  T: O(n), S: O(1)
 */
bool Purgatory::canJump(vector<int>& nums) {
    int maxReach = 0, n = nums.size();

    for ( int i = 0; i < n; ++i ) {
	// breach prediction
        if ( i > maxReach )
	    break;
    
	// register vs memory
	int reach = i + nums[i];
	maxReach = (reach > maxReach) ? reach : maxReach;

	if ( maxReach >= n - 1)
	    return true;
    }

    return maxReach >= n - 1;
}

/*
 *  using two-pass scan strategy
 *  T: O(n), S: O(1)
 */
vector<int> Purgatory::productExceptSelf(vector<int>& nums) {
    int n = nums.size();
    vector<int> answer(n, 1);

    int prefix = 1;
    for (int i = 0; i < n; ++i ) {
        answer[i] = prefix;
	prefix *= nums[i];
    }

    // cache behavior
    int suffix = 1;
    for (int i = n - 1; i >= 0; --i) {
	answer[i] *= suffix;
	suffix *= nums[i];
    }

    return answer;
}

/*
 *  using greedy approach + space counting here because we can break the problem into lines one by one
 *  T: O(n), S: O(n)
 */
vector<string> Purgatory::fullJustify(vector<string>& words, int maxWidth) {
    
    vector<string> result;
    int i = 0;
    int n = words.size();

    while ( i < n ) {
        int lineLen = words[i].size();
	// register vs memory
        int totalChars = words[i].size();
        int j = i + 1;

	// loop optimization
	while ( j < n && lineLen + 1 + words[j].size() <= maxWidth ) {
	    lineLen += 1 + words[j].size();
	    totalChars += words[j].size();
	    ++j;
	}

        int wordCount = j - i;
	int totalSpaces = maxWidth - totalChars;

	string line;
	// cache behavior
	line.reserve(maxWidth);
        
	if ( j == n || wordCount == 1) {
	    // compiler optimization
	    line.append(words[i]);

            for (int k = i + 1; k < j; ++k) {
	        line.push_back(' ');
	        line.append(words[k]);
	    }

	    line.append(maxWidth - line.size(), ' ');
	} else {
	    int gaps = wordCount - 1;
	    int spaceBetween = totalSpaces / gaps;
	    int extraSpace = totalSpaces % gaps;

	    for (int k = i; k < j - 1; ++k) {
		line.append(words[k]);
                int spaces = spaceBetween;
		
		// branch prediction
		if (k - i < extraSpace)
		    spaces++;

	        line.append(spaces, ' ');    	
	    }

	    line.append(words[j - 1]);
	}

        result.push_back(move(line));
	i = j;
    }

    return result;
}

/*
 * using a bottom-up dynamic programming pattern here because we can break into each state row[i][j] depends only on two previous states from row[i - 1]
 * T:O(n^2), S:O(n^2)
 */
vector<vector<int>> Purgatory::generate(int numRows) {
    // cache behavior
    vector<vector<int>> triangle(numRows);

    if (numRows == 0) return triangle;

    for (int i = 0; i < numRows; ++i) {
	// cache behavior
	triangle[i].resize(i + 1);

	// register vs memory
	auto &curr = triangle[i];
	curr[0] = curr[i] = 1;

	if (i > 0) {
	    // register vs memory
	    auto &prev = triangle[i - 1];

	    for (int j = 1; j < i; ++j)
	        curr[j] = prev[j - 1] + prev[j];
	}
    }

    return triangle;
}

/*
 *  using an in-place lexicographical successor algorithm here because we can break the problem into finding a pivot that can increase without violating order, then minmize that tail part by reversing it.
 *  T: O(n), S: O(1)
 */
void Purgatory::nextPermutation(vector<int>& nums) {
    int n = nums.size();
    int i = n - 2;

    // branch prediction
    while (i >= 0) {
        if (nums[i] < nums[i + 1])
            break;
	i--;
    }

    if (i >= 0) {
        int j = n - 1;
	// register vs memory
	int pivot = nums[i];

	while (nums[j] <= pivot)
            j--;

	// cache behavior
	int tmp = nums[i];
	nums[i] = nums[j];
	nums[j] = tmp;
    }

    // branch prediction
    int l = i + 1, r = n - 1;
    while (l < r) {
        int tmp = nums[l];
	nums[l++] = nums[r];
	nums[r--] = tmp;
    }
}

/*
 *  using backtracking with pruning and duplicate skipping here because we can break the problem into
 *  - sort the array to bring duplicates together
 *  - skip same elements at the same recursive depth
 *  - stop recursion early when sum exceeds target
 *  T: O(2^n), S: O(n)
 */
void backtrackingCombinationSum2(vector<int>& nums, int remain, int start, vector<int>& path, vector<vector<int>>& res) {
    if (remain == 0) {
        res.push_back(path);
	return;
    }

    for (int i = start; i < nums.size(); ++i) {
	// register vs memory
	int candidate = nums[i];

        if (i > start && candidate == nums[i - 1])
            continue;

	if (candidate > remain) break;

	path.push_back(candidate);

	backtrackingCombinationSum2(nums, remain - candidate, i + 1, path, res);

	path.pop_back();
    }
}	

vector<vector<int>> Purgatory::combinationSum2(vector<int>& candidates, int target) {
    sort(candidates.begin(), candidates.end());

    vector<vector<int>> res;
    vector<int> path;
    // cache behavior
    path.reserve(candidates.size());

    backtrackingCombinationSum2(candidates, target, 0, path, res);

    return res;
}

/*
 *  using recursive DFS with constraint pruning here because we can break the problem into combination of backtracking + constraint propagation
 *  T: O(9^m), S: O(m)
 */
void Purgatory::solveSudoku(vector<vector<char>>& board) {
    // CPU pipeline
    int row[9] = {0}, col[9] = {0}, box[9] = {0};

    auto getBox = [](int i, int j) {return (i/3)*3 + (j/3);};

    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            if (board[i][j] != '.') {
                int d = board[i][j] - '1';
		int mask = 1 << d;

                // branch prediction
		row[i] |= mask;
		col[j] |= mask;
		box[getBox(i, j)] |= mask;
	    }
	}
    }

    function<bool(int, int)> dfs = [&](int i, int j) -> bool {
        if (i == 9) return true;

	if (j == 9) return dfs(i + 1, 0);

	if (board[i][j] != '.')
	    return dfs(i, j + 1);

	int b = getBox(i, j);

	// register vs memory
        int used = row[i] | col[j] | box[b];

	for (int d = 0; d < 9; ++d) {
	    int mask = 1 << d;

	    if (used & mask)
                continue;

	    board[i][j] = '1' + d;

	    // cache behavior
	    row[i] |= mask; col[j] |= mask; box[b] |= mask;

	    if (dfs(i, j + 1))
                return true;

	    board[i][j] = '.';
	    row[i] ^= mask; col[j] ^= mask; box[b] ^= mask;
	}

	return false;
    };

    dfs(0, 0);
}

/*
 *  using simple indexing
 *  T: O(n), S:O(n)
 */
string Purgatory::getEncryptedString(string s, int k) {
    int n = s.size();
    string result(n, ' ');

    k %= n;
    // register vs memory
    int split = n - k;

    // cache behavior
    memcpy(&result[0], &s[k], split);
    memcpy(&result[split], &s[0], k);

    return result;
}

int Purgatory::arrayPairSum(vector<int> &nums) {
    // cache behavior
    const int OFFSET = 10000;
    vector<int> count(20001, 0);

    for (int num : nums) {
        count[num + OFFSET]++;
    }

    int result = 0;
    // branch prediction
    bool take = true;

    for (int i = 0; i < count.size(); ++i) {
	// cpu pipeline
        while (count[i]--) {
            if (take) result += (i - OFFSET);

	    take = !take;
	}
    }

    return result;
}

int Purgatory::maxProduct(vector<string> &words) {
    int n = words.size();
    if (n < 2) return 0;

    // cache behavior 
    vector<uint32_t> masks(n);
    vector<int> lengths(n);

    // cpu pipeline
    for (int i = 0; i < n; ++i) {
        int mask = 0;
	for (char c : words[i])
	    mask |= (1 << (c - 'a'));

	masks[i] = mask;
	lengths[i] = words[i].size();
    }

    // cpu pipeline
    vector<int> idx(n);
    iota(idx.begin(), idx.end(), 0);
    sort(idx.begin(), idx.end(), [&](int a, int b) {
        return lengths[a] > lengths[b];
        });

    vector<uint32_t> s_masks(n);
    vector<int> s_lens(n);

    for (int i = 0; i < n; ++i) {
        s_masks[i] = masks[idx[i]];
	s_lens[i] = lengths[idx[i]];
    }

    int maxProduct = 0;

    // cache behavior
    uint32_t *m_ptr = s_masks.data();
    int *l_ptr = s_lens.data();

    for (int i = 0; i < n - 1; ++i) {
	// register vs memory
	int len = l_ptr[i];
	uint32_t m = m_ptr[i];

	// branch prediction
        if (len * len <= maxProduct) break;

	for (int j = i + 1; j < n ;++j) {
            int product = len * l_ptr[j];

	    // branch prediction
	    if (product <= maxProduct) break;

	    // cpu pipeline
	    if ((m & m_ptr[j]) == 0) {
	        maxProduct = product;
		break;
	    }
	}

    }

    return maxProduct;
}

vector<int> Purgatory::largestDivisibleSubset(vector<int> &nums) {
    int n = nums.size();
    if (n == 0) return {};

    sort(nums.begin(), nums.end());

    vector<int> dp(n, 1);
    vector<int> parent(n, -1);

    int maxLen = 1, maxIdx = 0;

    // cahce behavior
    int *nums_ptr = nums.data();
    int *dp_ptr = dp.data();
    int *parent_ptr = parent.data();

    for (int i = 0; i < n; ++i) {
	// register vs memory
        int ni = nums_ptr[i];

	for (int j = i - 1; j >=0; --j) {
	    // branch prediction
	    if (dp_ptr[j] + 1 <= dp_ptr[i]) continue;

	    if (ni % nums[j] == 0) {
                dp_ptr[i] = dp_ptr[j] + 1;
		parent[i] = j;
	    }
	}

	if (dp_ptr[i] > maxLen) {
	    maxLen = dp_ptr[i];
	    maxIdx = i;
	}
    }

    vector<int> result;

    while (maxIdx != -1) {
        result.push_back(nums_ptr[maxIdx]);
	maxIdx = parent_ptr[maxIdx];
    }

    reverse(result.begin(), result.end());

    return result;
}

int Purgatory::distributeCandies(vector<int> &candyType) {
    // cache behavior
    sort(candyType.begin(), candyType.end());

    int n = candyType.size();
    int unique = 0;

    for (int i = 0; i < n; ++i) {
	// branch prediction
        if (i == 0 || candyType[i] != candyType[ i - 1])
		++unique;
    }

    int result = candyType.size() / 2;

    return min(unique, result);
}

int Purgatory::maxRotateFunction(vector<int> &nums) {
    int n = nums.size();
    if (n == 1) return 0;

    long total = 0;
    long F = 0;

    for (int i = 0; i < n; ++i) {
        total += nums[i];
	F += (int) i * nums[i];
    }

    long max = 0;

    // cpu pipeline
    for (int i = n - 1; i > 0; --i) {
        F = F + total - long(n) * nums[i];
	// branch prediction
	max = (F > max) ? F : max;
    }

    return (int) max;
}

vector<int> Purgatory::findRightInterval(vector<vector<int>> &intervals) {
    int n = intervals.size();

    // cache behavior
    vector<int> starts(n);
    vector<int> indices(n);

    for (int i = 0; i < n; ++i) {
        starts[i] = intervals[i][0];
	indices[i] = i;
    }

    vector<int> orders(n);
    iota(orders.begin(), orders.end(), 0);
    sort(orders.begin(), orders.end(), [&](int a, int b) {
        return starts[a] < starts[b];
    });

    vector<int> sorted_starts(n);
    vector<int> sorted_indices(n);

    for (int i = 0; i < n; ++i) {
        sorted_starts[i] = starts[orders[i]];
	sorted_indices[i] = indices[orders[i]];
    }

    vector<int> result(n, -1);

    for (int i = 0; i < n; ++i) {
        int target = intervals[i][1];

	auto it = lower_bound(sorted_starts.begin(), sorted_starts.end(), target);

        // branch prediction
	if (it != sorted_starts.end()) {
            int pos = it - sorted_starts.begin();
	    result[i] = sorted_indices[pos];
	}
    }

    return result;
}

static bool cmpLargestNumber(const string &a, const string &b) {
    int n = a.size(), m = b.size();

    // branch prediction
    for (int i = 0; i < n + m; ++i) {
        char ca = (i < n) ? a[i] : b[i - n];
	char cb = (i < m) ? b[i] : a[i - m];

	if (ca != cb) return ca > cb;
    }
    return false;
}

string Purgatory::largestNumber(vector<int> &nums) {
    // cache behavior
    vector<string> numStrs;
    numStrs.reserve(nums.size());

    for (int num : nums) {
        numStrs.emplace_back(to_string(num));
    }

    sort(numStrs.begin(), numStrs.end(), cmpLargestNumber);

    if (numStrs[0] == "0") return "0";

    string result;
    result.reserve(nums.size() * 10);

    for (const auto &s: numStrs) {
        result += s;
    }

    return result;
}

}
