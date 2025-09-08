#include "purgatory.h"

namespace purgatory {

/*
 *  using a max-heap here because the main operation is repeatedly taking the two largest elements. We break the problem into
 *  - building the heap from input
 *  - loop until <= 1 element left
 *  - handle smash rules
 */
int Purgatory::lastStoneWeight(vector<int>& stones) {
    priority_queue<int> pq(stones.begin(), stones.end());

    while(pq.size() > 1) {
        int y = pq.top(); pq.pop();
	int x = pq.top(); pq.pop();

	if (y != x) pq.push(y - x);
    }
     
    return pq.empty() ? 0 : pq.top();
}

/*
 *  using DP with three pointers here because we can break the problem into multiplying previous ugly numbers by 2, 3, 5, and then always taking the minimum
 */
int Purgatory::nthUglyNumber(int n) {
    vector<int> ugly(n);
    ugly[0] = 1;

    int p2 = 0, p3 = 0, p5 = 0;

    for(int i = 1; i < n; ++i) {
        int next2 = ugly[p2]*2;
	int next3 = ugly[p3]*3;
	int next5 = ugly[p5]*5;

	int nextUgly = min(next2, min(next3, next5));
	ugly[i] = nextUgly;

	if (nextUgly == next2) p2++;
	if (nextUgly == next3) p3++;
	if (nextUgly == next5) p5++;
    }
    return ugly[n-1];
}

/*
 *  using a min-heap with size k here because we only need the top k frequent elements, not a full sort.
 */
vector<int> Purgatory::topKFrequent(vector<int>& nums, int k) {
    unordered_map<int, int> freq;
    for(int n : nums) {
        freq[n]++;
    }

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    for (auto& f: freq) {
        pq.push({f.second, f.first});
	if (pq.size() > k) pq.pop();
    }


    vector<int> result;
    while(!pq.empty()) {
        result.push_back(pq.top().second);
	pq.pop();
    }

    return result;
}

/*
 *  using a monatomix deque here because it allows us to maintain the max efficiently as the window slides. Each element is processed at most twice.
 */
vector<int> Purgatory::maxSlidingWindow(vector<int>& nums, int k) {
    deque<int> dq;
    vector<int> result;

    for (int i = 0; i < nums.size(); ++i) {
        if (!dq.empty() && dq.front() <= i - k) dq.pop_front();

	while (!dq.empty() && nums[dq.back()] <= nums[i]) dq.pop_back();

	dq.push_back(i);

	if (i >= k - 1) {
            result.push_back(nums[dq.front()]);
	}
    }

    return result;
}

}
