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

int Purgatory::maxProduct(vector<int> &nums) {
    // register vs memory
    int largest = 0;
    int secondLargest = 0;

    for (const int value : nums) {
        if (value >= largest) {
	    secondLargest = largest;
	    largest = value;
	} else if (value > secondLargest) {
	    secondLargest = value;
	}
    }

    return (largest - 1) * (secondLargest - 1);
}

string Purgatory::frequencySort(string s) {
    int freq[128] = {0};
    int maxFreq = 0;

    // cache behavior
    string result;
    result.reserve(s.size());

    for (const char c : s) {
	// register vs memory
        int f = ++freq[(unsigned char)c];
	maxFreq = f > maxFreq ? f : maxFreq;
    }

    vector<string> buckets(maxFreq + 1);

    for (int ch = 0; ch < 128; ++ch) {
	// register vs memory
        int f = freq[ch];
	if (f)
	    buckets[f].push_back(static_cast<char>(ch));
    }

    for (int count = maxFreq ; count >= 1; --count) {
        for (const char c: buckets[count]) 
	    result.append(count, c);
    }

    return result;
}

vector<int> Purgatory::rearrangeBarcodes(vector<int> &barcodes) {
    // cache behavior
    constexpr int MAXV = 10000;
    int freq[MAXV + 1] = {};

    for (int code: barcodes) {
        ++freq[code];
    }

    vector<pair<int, int>> sortedCodes;

    for (int i = 1; i <= MAXV; ++i) {
        if (freq[i])
	    sortedCodes.push_back({freq[i], i});
    }

    sort(sortedCodes.begin(), sortedCodes.end(), [](const pair<int, int> &a, const pair<int, int> &b) {
        return a.first > b.first;
    });

    // register vs memory
    const int n = static_cast<int>(barcodes.size());
    vector<int> result(n);

    int index = 0;
    for (const auto & entry : sortedCodes) {
        int count = entry.first;
	int value = entry.second;

	while (count--) {
	    result[index] = value;
	    index += 2;

	    if (index >= n) {
	        index = 1;
	    }
	}
    }

    return result;
}

int Purgatory::furthestBuilding(vector<int> &heights, int bricks, int ladders) {
    // cache behavior
    priority_queue<int, vector<int>, greater<int>> minHeap;

    const int n = static_cast<int>(heights.size());

    for (int i = 0; i < n - 1; ++i) {
	// register vs memory
        int climb = heights[i + 1] - heights[i];

	if (climb <= 0) continue;

	minHeap.push(climb);

	if (static_cast<int>(minHeap.size()) > ladders) {
	    bricks -= minHeap.top();
	    minHeap.pop();
	}

	if (bricks < 0) 
            return i;
    }

    return n - 1;
}


vector<int> Purgatory::assignTasks(vector<int> &servers, vector<int> &tasks) {
    // cache behavior
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> freeServers;

    priority_queue<tuple<long long, int, int>, vector<tuple<long long, int, int>>, greater<tuple<long long, int, int>>> busyServers;

    vector<int> result(tasks.size());

    for (int i = 0; i < servers.size(); ++i) {
        freeServers.push({servers[i], i});
    }

    long long currentTime = 0;

    for (int taskIndex = 0; taskIndex < tasks.size(); ++taskIndex) {
        currentTime = max(currentTime, (long long) taskIndex);

	while (!busyServers.empty() &&
		get<0>(busyServers.top()) <= currentTime) {
            const auto server = busyServers.top();
	    busyServers.pop();

	    // register vs memory
	    int weight = get<1>(server);
	    int index = get<2>(server);

	    freeServers.emplace(weight, index);
	}

	if (freeServers.empty()) {
	    currentTime = get<0>(busyServers.top());

	    while(!busyServers.empty() &&
		  get<0>(busyServers.top()) <= currentTime) {
	        auto server = busyServers.top();
		busyServers.pop();

		// register vs memory
		int weight = get<1>(server);
		int index = get<2>(server);

		freeServers.emplace(weight, index);

	    }
	}

        auto bestServer = freeServers.top();
	freeServers.pop();

	int serverWeight = bestServer.first;
	int serverIndex = bestServer.second;

	result[taskIndex] = serverIndex;

	long long finishTime = currentTime + tasks[taskIndex];

	busyServers.push({finishTime, serverWeight, serverIndex});
    }

    return result;
}

vector<int> Purgatory::numberGame(vector<int> &nums) {
    // register vs memory
    const int n = nums.size();

    sort(nums.begin(), nums.end());

    for (int i = 0; i < n; i+=2) {
        int temp = nums[i];
	nums[i] = nums[i + 1];
	nums[i + 1] = temp;
    }

    return nums;
}

struct EdgeNetwork {
   int to;
   int w;
};

int Purgatory::networkDelayTime(vector<vector<int>> &times, int n, int k) {

    // cache behavior
    vector<vector<EdgeNetwork>> graph(n + 1);

    for (const auto &edge : times) {
        graph[edge[0]].push_back({edge[1], edge[2]});
    }

    // cache behavior
    vector<int> dist(n + 1, INT_MAX);
    dist[k] = 0;

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
    pq.push({0, k});

    while (!pq.empty()) {
        auto [currDist, node] = pq.top();
	pq.pop();

	if (currDist > dist[node]) continue;

	for (const EdgeNetwork &edge: graph[node]) {
	    // register vs memory
	    int next = edge.to;
	    int newDist = currDist + edge.w;

	    if (newDist < dist[next]) {
	        dist[next] = newDist;
		pq.push({newDist, next});
	    }
	}
    }

    int maxDelay = 0;
    for (int i = 1; i <= n; ++i) {
        if (dist[i] == INT_MAX) return -1;

	maxDelay = max(maxDelay, dist[i]);
    }

    return maxDelay;
}

int Purgatory::minSetSize(vector<int> &arr) {
    // cache behavior
    unordered_map<int, int> freq;
    for (const int num : arr) {
        ++freq[num];
    }

    // cache behavior
    const int n = arr.size();
    vector<int> bucket(n + 1, 0);

    for (const auto [num, time]: freq) {
        ++bucket[time];
    }

    int size = 0;
    int result = 0;
    int target = n >> 1;

    for (int i = n; i > 0 && size < target; --i) {
       while (bucket[i] > 0 && size < target) {
           size += i;
	   --bucket[i];
	   ++result;
       }
    }

    return result;
}

int Purgatory::deleteGreatestValue(vector<vector<int>> &grid) {
    // register vs memory
    int rows = grid.size();
    int cols = grid[0].size();

    for (auto &row : grid)
        sort(row.begin(), row.end());

    int result =0;

    for (int col = 0; col < cols; ++col) {
	// register vs memory
	int roundMax = 0;
        for (int row = 0; row < rows; ++row) {
            const int value = grid[row][col];

	    roundMax = value > roundMax ? value : roundMax;
	}

	result += roundMax;
    }

    return result;
}

string Purgatory::longestDiverseString(int a, int b, int c) {

    // cache behavior
    priority_queue<pair<int, char>> pq;

    if (a > 0) pq.push({a, 'a'});
    if (b > 0) pq.push({b, 'b'});
    if (c > 0) pq.push({c, 'c'});

    string result;

    while (!pq.empty()) {
        auto [count, letter] = pq.top();
	pq.pop();

	const int n = result.size();

	// branch prediction
        int isvalid = n >= 2 && result[n - 1] == letter && result[n - 2] == letter;

	if (isvalid) {
            if (pq.empty()) break;

            auto [count2, letter2] = pq.top();
	    pq.pop();

	    result.push_back(letter2);
	    --count2;

	    if (count2 > 0)
	        pq.push({count2, letter2});

	    pq.push({count, letter});
	} else {
	    result.push_back(letter);
	    --count;

	    if (count > 0)
	        pq.push({count, letter});
	}
    }

    return result;
}

int Purgatory::minimumEffortPath(vector<vector<int>> &heights) {
    // register vs memory
    int rows = heights.size();
    int cols = heights[0].size();
    
    vector<vector<int>> dist(rows, vector<int>(cols, INT_MAX));

    vector<pair<int, int>> dirs = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

    using State = tuple<int, int, int>;

    priority_queue<State, vector<State>, greater<State>> minHeap;

    dist[0][0] = 0;
    minHeap.push({0, 0, 0});

    while (!minHeap.empty()) {
        auto [currentEffort, x, y] = minHeap.top();
	minHeap.pop();

	if (currentEffort > dist[x][y]) continue;

	if (x == rows - 1 && y == cols - 1) return currentEffort;

	for (const auto &dir : dirs) {
            int dx = x + dir.first;
	    int dy = y + dir.second;

	    if (dx < 0 || dy < 0 || dx >= rows || dy >= cols) continue;

	    int edgeCost = abs(heights[x][y] - heights[dx][dy]);

	    int nextEffort = max(currentEffort, edgeCost);

	    if (nextEffort < dist[dx][dy]) {
                dist[dx][dy] = nextEffort;

		minHeap.push({nextEffort, dx, dy});
	    }
	}
    }


    return 0;
}

long long Purgatory::pickGifts(vector<int> &gifts, int k) {
    // cache behavior
    priority_queue<int> pq(gifts.begin(), gifts.end());

    while (k-- > 0) {
        int gift = pq.top();
	pq.pop();

	int reducedGift = static_cast<int>(sqrt(gift));

	pq.push(reducedGift);
    }

    int result = 0;

    while (!pq.empty()) {
        result += pq.top();
	pq.pop();
    }

    return result;
}

struct TaskGetOrder {
    int enqueueTime;
    int processingTime;
    int index;
};

vector<int> Purgatory::getOrder(vector<vector<int>> &tasks) {
    int n = tasks.size();
    
    // cache behavior
    vector<TaskGetOrder> sortedTasks;

    for (int i = 0; i < n; ++i) {
        sortedTasks.push_back({
	    tasks[i][0],
	    tasks[i][1],
	    i});
    }

    sort(sortedTasks.begin(), sortedTasks.end(), [](const TaskGetOrder &a, const TaskGetOrder &b) {
        return a.enqueueTime < b.enqueueTime;		    
    });

    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<>> pq;

    // cache behavior
    vector<int> order;
    order.reserve(n);

    long long currentTime = 0;
    int taskIndex = 0;

    while (taskIndex < n || !pq.empty()) {
        if (pq.empty() && sortedTasks[taskIndex].enqueueTime > currentTime)
	    currentTime = sortedTasks[taskIndex].enqueueTime;

	while (taskIndex < n && sortedTasks[taskIndex].enqueueTime <= currentTime) {
	    // register vs memory
            const TaskGetOrder &t = sortedTasks[taskIndex];
	    pq.push({t.processingTime, t.index});
	    taskIndex++;
	}

	auto [processingTime, index] = pq.top();
	pq.pop();

	currentTime += processingTime;
	order.push_back(index);
    }

    return order;
}


}
