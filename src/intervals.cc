#include "purgatory.h"

namespace purgatory {

/*
 *  using a two-pointer style approach here because the array is sorted, we just need to find where a consecutive run starts and ends.
 *  T: O(n), S: O(n)
 */
vector<string> Purgatory::summaryRanges(vector<int>& nums) {
	vector<string> result;
	// register vs memory
        int n = nums.size();

	if (n == 0) return result;
        // cache behavior
	result.reserve(n);

	int start = nums[0];
        int prev = nums[0];

	for (int i = 1; i < n; ++i) {
            int curr = nums[i];

	    // cpu pipeline
            if ( curr != prev + 1) {
                string s;
		s.reserve(20);

	        s += to_string(start);
		
	        if (start != prev) {
		    s += "->";
		    s += to_string(prev);
	        }

		result.push_back(move(s));
		start = curr;
	    }

	    prev = curr;
	}

	// cpu pipeline
	string s;
	s.reserve(20);

        s += to_string(start);
	if (start != prev) {
	    s += "->";
	    s += to_string(prev);
	}

	result.push_back(move(s));

	return result;
}

/*
 *  using sorting + linear scan here because we can break the problem into
 *  - first align intervals in order
 *  - then merge only when overlap happens
 *  T: O(n), S: O(n)
 */
vector<vector<int>> Purgatory::merge(vector<vector<int>>& intervals) {
    vector<vector<int>> merged;

    // register vs memory
    int n = intervals.size();

    if ( n == 0) return merged;

    // loop optimization
    sort(intervals.begin(), intervals.end(), [](const vector<int> &a, const vector<int> &b) {
        return a[0] < b[0];
    });

    merged.push_back(intervals[0]);

    for (int i = 1; i < n; ++i) {
	// cache behavior
	const vector<int> &curr = intervals[i];
	int start = curr[0], end = curr[1];

	vector<int> &last = merged.back();

        if (last[1] < start) {
	    merged.emplace_back();
	    merged.back().push_back(start);
	    merged.back().push_back(end);
	} else {
	    // function call
	    last[1] = (last[1] > end) ? last[1] : end;
	}
    }

    return merged;
}

/*
 *  using the linear scan method here because input is already sorted, so
 *  - append non-overlapped before part
 *  - merge overlaps
 *  - append non-overlapped after part
 *  T: O(n), S: O(n)
 */
vector<vector<int>> Purgatory::insert(vector<vector<int>>& intervals, vector<int>& newInterval) {
	vector<vector<int>> result;
	// register vs memory
	int n = intervals.size();
	// cache behavior
        result.reserve(n + 1);

	int newStart = newInterval[0];
	int newEnd = newInterval[1];

	int i = 0;
	while( i < n ) {
	    // register vs memory
	    const vector<int> &curr = intervals[i];

	    // branch prediction
	    if (!(curr[1] < newStart))
	        break;

	    result.emplace_back(curr);
	    i++;
	}

	while( i < n ) {
	    // register vs memory
	    const vector<int> &curr = intervals[i];

	    // branch prediction
	    if (! (curr[0] <= newEnd) )
	        break;
	
	    newStart = (curr[0] < newStart) ? curr[0] : newStart;
	    newEnd = (curr[1] > newEnd) ? curr[1] : newEnd;
	    i++;
	}

	result.emplace_back();
	result.back().push_back(newStart);
	result.back().push_back(newEnd);

	while (i<n) {
            result.emplace_back(intervals[i]);
	    i++;
	}

	return result;
}

/*
 *  using greedy + sorting method here because we can break the problem into
 *  - sort by end
 *  - always shoot at the current end to maximize coverage
 *  T: O(n log n), S: O(1)
 */
int Purgatory::findMinArrowShots(vector<vector<int>>& points) {
        if (points.empty()) return 0;
	// register vs memory
	int n = points.size();

        // cache behavior
	vector<pair<int, int>> order;
	order.reserve(n);

        for (int i = 0; i < n; ++i) {
	    order.emplace_back(points[i][1], i);
	}

        sort(order.begin(), order.end());

	int arrows = 1;
	int arrowPos = order[0].first;

	for (int i = 1; i < n; ++i) {
	    // register vs memory
	    int idx = order[i].second;
	    const vector<int> &p = points[idx];
	    int start = p[0];

            if (start > arrowPos) {
                arrows++;
		arrowPos = order[i].first;
	    }
	}

	return arrows;
}

}
