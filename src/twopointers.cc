#include "purgatory.h"

namespace purgatory {

/*
 *  using two-pointer method here becuase
 *  - we can skip non-alphanumeric characters in-place without building a new filtered string
 *  - this reduce extra memory usage to O(1)
 */
bool Purgatory::isPalindrome(string s) {
    int left = 0, right = s.size() - 1;

    while (left < right) {
        while (left < right && !isalnum(s[left])) left++;

	while (left < right && !isalnum(s[right])) right--;

	if (tolower(s[left]) != tolower(s[right])) return false;

	left++; right--;
    }

    return true;
}

/*
 *  using two pointers here because the input is sorted
 */
vector<int> Purgatory::twoSum(vector<int>& numbers, int target) {
    int left = 0, right = numbers.size() - 1;

    while (left < right) {
        int sum = numbers[left] + numbers[right];

	if (sum == target) {
            return {left + 1, right + 1};
	} else if (sum < target) {
            left++;
	} else {
	    right--;
	}
    }

    return {};
}

/*
 *  using two pointers here because we can break the problme into repeatedly eliminating impossible pairs. We always move the pointer at the shorter height inward because that's the only way to potentially increase area.
 */
int Purgatory::maxArea(vector<int> &height) {
    int left = 0, right = height.size() - 1;
    int maxWater = 0;

    while (left < right) {
        int h = min(height[left], height[right]);
	int width = right - left;
	int area = h * width;

	maxWater = max(maxWater, area);

	if (height[left] < height[right]) left++;
	else right--;
    }

    return maxWater;
}

/*
 *  using two pointers here becuase we can break the problem into continuously shrinking the search space from both ends, while keeping track of the max heights seen so far.
 */
int Purgatory::trap(vector<int> & height) {
    int left = 0, right = height.size() - 1;
    int leftMax = 0, rightMax = 0;
    int water = 0;

    while (left < right) {
        if (height[left] < height[right]) {
            if (height[left] > leftMax) {
                leftMax = height[left];
	    } else {
	        water += leftMax - height[left];
	    }

	    left++;
	} else {
            if (height[right] >rightMax) {
	        rightMax = height[right];
	    } else {
		water += rightMax - height[right];
	    }

	    right--;
	}
    }

    return water;
}

}
