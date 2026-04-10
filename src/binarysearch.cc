#include "purgatory.h"

namespace purgatory {

/*
 *  using binary search here because the problem reduces to finding the first index where nums[i] >= target. Binary search guarantees O(log n) complexity. The final left variable naturally gives us the correct insertion index, whether the target is found or not.
 *  T:O(log n), S: O(1)
 */
int Purgatory::searchInsert(vector<int>& nums, int target) {
    int left = 0, right = nums.size();

    while (left < right) {
        int mid = left + ((right - left) >> 1);
	// register vs memory
        int val = nums[mid];

	// branch prediction
	bool cond = val < target;
	left = cond ? mid + 1 : left;
	right = cond ? right : mid;
    }

    return left;
}

/*
 *  using binary search across the flattened matrix here because the matrix properties let us treat it as a sotred 1D array. The state is defined by the search range [left, right]. Mapping mid back into (row, col) allows us to compare correctly. This give O(log m * n) complexity.
 *  T: O(log (m * n)), S: O(1)
 */
bool Purgatory::searchMatric(vector<vector<int>>& matrix, int target) {
    if (matrix.empty() || matrix[0].empty())
        return false;

    int m = matrix.size(), n = matrix[0].size();

    // cpu pipeline
    int top = 0, bottom = m - 1;

    while (top <= bottom) {
        int mid = top + ((bottom - top) >> 1);
	// register vs memory
	auto &row = matrix[mid];

	// branch prediction
        if (row[0] <= target && target <= row[n - 1]) {
	    int left = 0, right = n - 1;

	    while (left <= right) {
                int mid2 = right + (right - left) >> 1;
		int val = row[mid2];

		if (val < target)
		    left = mid2 + 1;
		else if (val > target)
		    right = mid2 - 1;
		else
		    return true;
	    }

	    return false;
	}

	if (row[0] > target)
	    bottom = mid - 1;
	else
	    top = mid + 1;
    }

    return false;
}

/*
 *  using binary search on slope property here
 *  T: O(log n), S: O(1)
 */
int Purgatory::findPeakElement(vector<int>& nums) {
    int left = 0, right = nums.size() - 1;

    while (left < right) {
	// compiler optimization
	int mid = left + ((right - left) >> 1);
	// register vs memory
	int val = nums[mid];
	int nextVal = nums[mid + 1]; 

        if (val < nextVal) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }
    return left;
}

/*
 *  using binary search on partitions here because we can break the problem into finding the correct split point
 *  T: O(log min(m, n)), S: O(1)
 */
double Purgatory::findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
    if (nums1.size() > nums2.size()) return findMedianSortedArrays(nums2, nums1);

    int m = nums1.size(), n = nums2.size();

    // register vs memory
    int half = (m + n + 1) >> 1;
    int odd = (m + n) & 1;

    int left = 0, right = m;

    while ( left <= right ) {
        int i = left + ((right - left) >> 1);
	int j = half - i;

	int left1 = ( i > 0 ) ? nums1[i - 1] : INT_MIN;
	int right1 = ( i < m ) ? nums1[i] : INT_MAX;
	int left2 = ( j > 0 ) ? nums2[j - 1] : INT_MIN;
	int right2 = ( j < n ) ? nums2[j] : INT_MAX;

	// branch prediction
	if (left1 > right2) {
	    right = i - 1;
	    continue;
	}

	// branch prediction
	if (left2 > right1) {
	    left = i + 1;
	    continue;
	}

	int leftMax = max(left1, left2);

	if (odd) return (double) leftMax;

	int rightMin = min(right1, right2);

	return (leftMax + rightMin) * 0.5;
    } 

    return 0.0;
}

/*
 *  using XOR here because we can break the problem into elimination pairs symmetrically
 *  T: O(n), S: O(1)
 */
int Purgatory::missingNumber(vector<int>& nums) {
    int n = nums.size();
    int x = n;

    // cpu pipeline
    for (int i = 0; i < n; ++i) {
        x ^= i ^ nums[i];
    }

    return x;
}

/*
 *  using Floy'd algorithm here because we can break the problem into the array into a function f(i) = nums[i]
 *   T: O(n), S: O(1)
 */
int Purgatory::findDuplicate(vector<int>& nums) {
    // register vs memory
    const int *a = nums.data();

    int slow = a[0], fast = a[0];

    do{
        slow = a[slow];
	// cpu pipeline
	int f = nums[fast];
	fast = nums[f];
    } while (slow != fast);

    slow = a[0];
    
    while (slow != fast) {
        slow = a[slow];
	fast = a[fast];
    }

    return slow;
}

/*
 *  using binary search with duplicate-skip shrink here because we can break the problem into the array as two sorted parts separated by rotation
 *  T: O(log n), S: O(1)
 */
bool Purgatory::search(vector<int>& nums, int target) {
    int l = 0, r = nums.size() - 1;

    // register vs memory
    const int *data = nums.data();

    while (l <= r) {
	// compiler optimization
        int mid = l + ((r - l) >> 1);
	// register vs memory
	int lval = data[l];
	int mval = data[mid];
	int rval = data[r];

	if (mval == target) return true;

	// branch predication
	if (lval == mval && rval == mval) { // equality case
	    l++;
	    r--;
	    continue;
	}
	
	if (lval <= mval) { // left sorted case
            if (mval > target && lval <= target) {
	        r = mid - 1;
	    } else {
	        l = mid + 1;
	    }
	} else { // right sorted case
            if (mval < target && target <= rval) {
	        l = mid + 1;
	    } else {
	        r = mid - 1;
	    }
	}
    }
    return false;
}

/*
 *  using binary search with duplicate handling here because we can break the problem into in a rotated sorted array, the direction of mod relative to right tell us which half is unsorted.
 *  T: O(log n), S: O(n)
 */
int Purgatory::findMin(vector<int>& nums) {
    int left = 0, right = nums.size() - 1;
    // cache behavior
    const int *data = nums.data();

    while (left < right) {
	// compiler optimization
        int mid = left + ((right - left) >> 1);
	// register vs memory
	int m = nums[mid];
	int r = nums[right];

	if (m > r) {
            left = mid + 1;
	} else {
	    right = mid;
	}
    }

    return data[left];
}


}
