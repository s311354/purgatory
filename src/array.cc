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

    while ( p1 >= 0 && p2 >= 0 ) {
        if (nums1[p1] > nums2[p2]) {
	    nums1[p--] = nums1[p1--];
	} else {
	    nums1[p--] = nums2[p2--];
	}
    }

    while ( p2 >= 0 ) {
        nums1[p--] = nums2[p2--];
    }
}

/*
 *  using two pointer technique here because we can break the problem into
 *  1. one pointer to read each element, read
 *  2. one pointer to write valid entries, write
 *  T:O(n), S:O(1)
 */
int Purgatory::removeDuplicates(vector<int>& nums) {
    if (nums.size() < 2) return nums.size();

    int write = 2;

    for (int read = 2; read < nums.size(); ++read) {
        if (nums[read] != nums[write - 2]) {
	    nums[write] = nums[read];
	    ++write;
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
void Purgatory::rotate(vector<int> & nums, int k) {
    int n = nums.size();

    k = k % n;

    reverse(nums.begin(), nums.end());
    reverse(nums.begin(), nums.begin() + k);
    reverse(nums.begin() + k, nums.end());
}

/*
 *  using two-pass greedy method here because we can break the problem into two directional constraints
 *  - left to right handles increasing sequences
 *  - right to left handles decreasing sequences
 *  T: O(n), S: O(n)
 */
int Purgatory::candy(vector<int>& ratings) {

    int n = ratings.size();

    vector<int> candies(n, 1);

    for (int i = 1; i < n; ++i) {
        if (ratings[i] > ratings[i - 1]) {
	    candies[i] = candies[i - 1] + 1;
	}
    }

    for (int i = n - 2; i >= 0; --i) {
        if (ratings[i] > ratings[i + 1]) {
	    candies[i] = max(candies[i], candies[i + 1] + 1);
	}
    }

    int total = 0;

    for(auto c : candies) {
        total += c;
    }

    return total;
}

/*
 *  using two pointers here because it helps us process the array in-place without needing extra memory.
 *  T: O(n), S: O(1)
 */
int Purgatory::removeElemet(vector<int>& nums, int val) {
    int write = 0;

    for (int read = 0; read < nums.size(); ++read) {
        if ( nums[read] != val ) {
	    nums[write] = nums[read];
	    ++write;
	}
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
        if ( i > maxReach ) return false;
    
	maxReach = max(maxReach, i + nums[i]);

	if ( maxReach >= n - 1) return true;
    }

    return true;
}

/*
 *  using two-pass scan strategy
 *  T: O(n), S: O(1)
 */
vector<int> Purgatory::productExceptSelf(vector<int>& nums) {
    int n = nums.size();
    vector<int> answer(n, 1);

    for (int i = 1; i < n; ++i ) {
        answer[i] = answer[i - 1] * nums[i - 1];
    }

    int suffix = 1;
    for ( int i = n - 1; i >=0 ; --i ) {
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
    int i = 0, n = words.size();

    while ( i < n ) {
        int j = i, lineLen = 0;

	while ( j < n && lineLen + words[j].length() + (j - i) <= maxWidth ) {
	    lineLen += words[j].length();
	    ++j;
	}

        int wordCount = j - i;
	int totalSpace = maxWidth - lineLen;

	string line;
        
	if ( j == n || wordCount == 1) {
            for (int k = i; k < j; ++k) {
	        line += words[k];

		if (k < j - 1) line += ' ';
	    }

	    line += string(maxWidth - line.size(), ' ');
	} else {
	    int spaceBetween = totalSpace / (wordCount - 1);
	    int extraSpace = totalSpace % (wordCount - 1);

	    for (int k = i; k < j; ++k) {
		line += words[k];
		
		if (k < j - 1) {
	            int spaces = spaceBetween + (extraSpace-- > 0 ? 1 : 0);
		    line += string(spaces, ' ');
		}
	    }
	}

        result.push_back(line);
	i = j;

    }

    return result;
}

/*
 * using a bottom-up dynamic programming pattern here because we can break into each state row[i][j] depends only on two previous states from row[i - 1]
 * T:O(n^2), S:O(n^2)
 */
vector<vector<int>> Purgatory::generate(int numRows) {
    vector<vector<int>> triangle(numRows);

    if (numRows == 0) return triangle;

    for (int i = 0; i < numRows; ++i) {
        triangle[i].resize(i + 1);
	triangle[i][0] = triangle[i][i] = 1;

	for (int j = 1; j < i; ++j) {
	    triangle[i][j] = triangle[i - 1][j - 1] + triangle[i - 1][j];
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

    while (i >= 0 && nums[i] >= nums[i + 1]) i--;

    if (i >= 0) {
        int j = n - 1;
	while (nums[j] <= nums[i]) j--;
	swap(nums[i], nums[j]);
    }

    reverse(nums.begin() + i + 1, nums.end());
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
        if (i > start && nums[i] == nums[i - 1])
            continue;

	if (nums[i]> remain) break;

	path.push_back(nums[i]);

	backtrackingCombinationSum2(nums, remain - nums[i], i + 1, path, res);

	path.pop_back();
    }
}	

vector<vector<int>> Purgatory::combinationSum2(vector<int>& candidates, int target) {
    sort(candidates.begin(), candidates.end());

    vector<vector<int>> res;
    vector<int> path;

    backtrackingCombinationSum2(candidates, target, 0, path, res);

    return res;
}

/*
 *  using recursive DFS with constraint pruning here because we can break the problem into combination of backtracking + constraint propagation
 *  T: O(9^m), S: O(m)
 */
void Purgatory::solveSudoku(vector<vector<char>>& board) {
    vector<vector<bool>> row(9, vector<bool>(10, false));
    vector<vector<bool>> col(9, vector<bool>(10, false));
    vector<vector<bool>> box(9, vector<bool>(10, false));

    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            if (board[i][j] != '.') {
                int d = board[i][j] - '0';
		row[i][d] = col[j][d] = box[(i/3)*3 + j/3][d] = true;
	    }
	}
    }

    function<bool(int, int)> dfs = [&](int i, int j) -> bool {
        if (i == 9) return true;

	if (j == 9) return dfs(i + 1, 0);

	if (board[i][j] != '.')
	    return dfs(i, j + 1);

	int b = (i/3)*3 + j/3;
	for (int d = 1; d <= 9; ++d) {
	    if (!row[i][d] && !col[j][d] && !box[b][d]) {
	        board[i][j] = '0' + d;

	        row[i][d] = col[j][d] = box[b][d] = true;

	        if (dfs(i, j + 1)) return true;

	        board[i][j] = '.';
	        row[i][d] = col[j][d] = box[b][d] = false;
	    }
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
    k = k % n;

    for (int i = 0; i < n; ++i) {
	result[i] = s[(i + k) % n];
    }

    return result;
}

}
