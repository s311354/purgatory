#include "purgatory.h"

namespace purgatory {

/*
 *  using binary search here because the problem reduces to finding the first index where nums[i] >= target. Binary search guarantees O(log n) complexity. The final left variable naturally gives us the correct insertion index, whether the target is found or not.
 *  T:O(log n), S: O(1)
 */
int Purgatory::searchInsert(vector<int>& nums, int target) {
    int left = 0, right = nums.size() - 1;

    while (left <= right) {
        int mid = left + (right - left)/2;

	if (nums[mid] == target) return mid;
	else if (nums[mid] < target) left = mid + 1;
	else right = mid - 1;
    }

    return left;
}

/*
 *  using binary search across the flattened matrix here because the matrix properties let us treat it as a sotred 1D array. The state is defined by the search range [left, right]. Mapping mid back into (row, col) allows us to compare correctly. This give O(log m * n) complexity.
 *  T: O(log (m * n)), S: O(1)
 */
bool Purgatory::searchMatric(vector<vector<int>>& matrix, int target) {
    int m = matrix.size(), n = matrix[0].size();

    int left = 0, right = m*n - 1;

    while (left <= right ) {
        int mid = left + (right - left)/2;
	int val = matrix[mid/n][mid%n];

	if (val == target) return true;
	else if (val < target) left = mid + 1;
	else right = mid - 1;
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
	int mid = left + (right - left)/2;

        if (nums[mid] < nums[mid + 1]) {
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
    int half = (m + n + 1)/2;

    int left = 0, right = m;

    while ( left <= right ) {
        int i = (left + right)/ 2;
	int j = half - i;

	int left1 = ( i > 0 ) ? nums1[i - 1] : INT_MIN;
	int right1 = ( i < m ) ? nums1[i] : INT_MAX;
	int left2 = ( j > 0 ) ? nums2[j - 1] : INT_MIN;
	int right2 = ( j < n ) ? nums2[j] : INT_MAX;

	if (left1 < right2 && left2 <= right1) {
            if ((m + n) % 2 == 0) return (max(left1, left2) + min(right1, right2)) / 2.0;
	    else return max(left1, left2);
	} else if (left1 > right2) right = i - 1;
	else left = i + 1;
    } 

    return 0.0;
}

/*
 *  using XOR here because we can break the problem into elimination pairs symmetrically
 *  T: O(n), S: O(1)
 */
int Purgatory::missingNumber(vector<int>& nums) {
    int n = nums.size();
    int xorAll = 0;

    for (int i = 0; i <= n; ++i) {
        xorAll ^= i;
    }

    for (int num: nums) xorAll ^= num;

    return xorAll;
}

/*
 *  using Floy'd algorithm here because we can break the problem into the array into a function f(i) = nums[i]
 *   T: O(n), S: O(1)
 */
int Purgatory::findDuplicate(vector<int>& nums) {
    int slow = nums[0], fast = nums[0];

    do{
        slow = nums[slow];
	fast = nums[nums[fast]];
    } while (slow != fast);

    slow = nums[0];
    
    while (slow != fast) {
        slow = nums[slow];
	fast = nums[fast];
    }

    return slow;
}

/*
 *  using binary search with duplicate-skip shrink here because we can break the problem into the array as two sorted parts separated by rotation
 *  T: O(log n), S: O(1)
 */
bool Purgatory::search(vector<int>& nums, int target) {
    int l = 0, r = nums.size() - 1;

    while (l <= r) {
        int mid = l + (r - l)/2;

	if (nums[mid] == target) return true;

	if (nums[l] == nums[mid] && nums[r] == nums[mid]) { // equality case
	    l++;
	    r--;
	} else if (nums[l] <= nums[mid]) { // left sorted case
            if (nums[mid] > target && nums[l] <= target) {
	        r = mid - 1;
	    } else {
	        l = mid + 1;
	    }
	} else { // right sorted case
            if (nums[mid] < target && target <= nums[r]) {
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

    while (left < right) {
        int mid = left + (right - left)/2;

	if (nums[mid] > nums[right]) {
            left = mid + 1;
	} else {
	    right = mid;
	}
    }

    return nums[left];
}


}
