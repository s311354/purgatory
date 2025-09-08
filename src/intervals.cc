#include "purgatory.h"

namespace purgatory {

/*
 *  using a two-pointer style approach here because the array is sorted, we just need to find where a consecutive run starts and ends.
 */
vector<string> Purgatory::summaryRanges(vector<int>& nums) {
	vector<string> result;
	if (nums.empty()) return result;

	int start = nums[0];

	for (int i = 1; i < nums.size(); ++i) {
            if (i == nums.size() || nums[i] != nums[i - 1] + 1) {
	        if (start == nums[i-1]) result.push_back(to_string(start));
		else result.push_back(to_string(start) + "->" + to_string(nums[i-1]));
	    }

	    if (i < nums.size()) start = nums[i];
	}
	return result;
}

/*
 *  using sorting + linear scan here because we can break the problem into
 *  - first align intervals in order
 *  - then merge only when overlap happens
 */
vector<vector<int>> Purgatory::merge(vector<vector<int>>& intervals) {
    if (intervals.empty()) return {};

    sort(intervals.begin(). intervals.end());

    vector<vector<int>> merged;

    for (auto& interval: intervals) {
        if (interval.empty() || merged.back()[1] < interval[0])
		merged.push_back(interval);
	else
		merged.back()[1] = max(merged.back()[1], interval[1]);
    }

    return merged;
}

/*
 *  using the linear scan method here because input is already sorted, so
 *  - append non-overlapped before part
 *  - merge overlaps
 *  - append non-overlapped after part
 */
vector<vector<int>> Purgatory::insert(vector<vector<int>>& intervals, vector<int>& newInterval) {
	vector<vector<int>> result;

	int i = 0, n = intervals.size();

	while( i < n && intervals[i][1] < newInterval[0]) {
	    result.push_back(intervals[i]);
	    i++;
	}

	while( i < n && intervals[i][0] <= newInterval[1]) {
	    newInterval[0] = min(intervals[i][0], newInterval[0]);
	    newInterval[1] = max(intervals[i][1], newInterval[1]);
	    i++;
	}
	result.push_back(newInterval);

	while (i<n) {
            result.push_back(intervals[i]);
	    i++;
	}

	return result;
}

/*
 *  using greedy + sorting method here because we can break the problem into
 *  - sort by end
 *  - always shoot at the current end to maximize coverage
 */
int Purgatory::findMinArrowShots(vector<vector<int>>& points) {
        if (points.empty()) return 0;

        sort(points.begin(), points.end(), [][const vector<int>& a, const vector<int>& b] {
	    if (a[1] == b[1]) return a[0] < b[0];
	    return a[1] < b[1];
        };)

	int arrows = 1;
	long long arrowPos = points[0][1];

	for (int i = 1; i < points.size(); ++i) {
            if (points[i][0] > arrowPos) {
                arrows++;
		arrowPos = points[i][1];
	    }
	}

	return arrows;
}

}
