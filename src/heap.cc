#include "purgatory.h"

namespace purgatory {

/*
 *  using a max-heap here because the main operation is repeatedly taking the two largest elements. We break the problem into
 *  - building the heap from input
 *  - loop until <= 1 element left
 *  - handle smash rules
 */
int Purgatory::lastStoneWeight(vector<int>& stones) {
    // cache behavior
    vector<int> heap = stones;
    make_heap(heap.begin(), heap.end());

    while(heap.size() > 1) {
	pop_heap(heap.begin(), heap.end());
        int y = heap.back(); heap.pop_back();
	pop_heap(heap.begin(), heap.end());
	int x = heap.back(); heap.pop_back();

	// branch prediction
	int diff = y - x;
	if (diff > 0) {
	    heap.push_back(diff);
	    push_heap(heap.begin(), heap.end());
	}
    }
     
    return heap.empty() ? 0 : heap.back();
}

/*
 *  using DP with three pointers here because we can break the problem into multiplying previous ugly numbers by 2, 3, 5, and then always taking the minimum
 */
int Purgatory::nthUglyNumber(int n) {
    vector<int> ugly(n);
    ugly[0] = 1;

    int p2 = 0, p3 = 0, p5 = 0;
    // register vs memory
    int next2 = 2, next3 = 3, next5 = 5;

    for(int i = 1; i < n; ++i) {
	// function call
	int nextUgly = next2;
	if (next3 < nextUgly) nextUgly = next3;
	if (next5 < nextUgly) nextUgly = next5;

	ugly[i] = nextUgly;

	if (nextUgly == next2) {
	    p2++;
	    next2 = ugly[p2] << 1;
	}

	if (nextUgly == next3) {
            p3++;
	    next3 = ugly[p3] * 3;
	}
	
	if (nextUgly == next5) { 
	    p5++;
	    next5 = ugly[p5] * 5;
	}
    }
    return ugly[n-1];
}

/*
 *  using a min-heap with size k here because we only need the top k frequent elements, not a full sort.
 */
vector<int> Purgatory::topKFrequent(vector<int>& nums, int k) {
    unordered_map<int, int> freq;
    // cache behavior
    freq.reserve(nums.size());
    for(int n : nums) {
        freq[n]++;
    }

    // cpu pipeline 
    struct Compare {
        bool operator()(const pair<int, int> &a, const pair<int, int> &b) {
	    return a.first > b.first;
	}
    };

    priority_queue<pair<int, int>, vector<pair<int, int>>, Compare> pq;

    for (auto& f: freq) {
        pq.emplace(f.second, f.first);

	if (pq.size() > k) pq.pop();
    }


    vector<int> result;
    result.reserve(k);

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
    // register vs memory
    int n = nums.size();

    // cache behavior
    vector<int> dq(n);
    int head = 0, tail = 0;

    vector<int> result;
    result.reserve(n - k + 1);

    for (int i = 0; i < n; ++i) {
	// register vs memory
	int cur = nums[i];

        if (head < tail && dq[head] <= i - k) head++;

	while (head < tail && nums[dq[tail - 1]] <= cur) tail--;

	dq[tail++] = i;

	if (i >= k - 1) {
            result.push_back(nums[dq[head]]);
	}
    }

    return result;
}

}
