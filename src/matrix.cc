#include "purgatory.h"

namespace purgatory {

/*
 *  using counting external edges here because we can break the problem into each cell starts with 4 potential edges and every shared edge between two adjacent lands removes 2 total edges (one from each cell)
 *  T: O(rows * cols), S: O(1)
 */
int Purgatory::islandPerimeter(vector<vector<int>>& grid) {
    int perimeter = 0;
    int rows = grid.size(), cols = grid[0].size();

    for (int i = 0; i < rows; ++i) {
	// register vs memory
	const vector<int> &row = grid[i];
	const vector<int> &prevRow = (i > 0) ? grid[i - 1] : row;

        for (int j = 0; j < cols; ++j) {
            int cell = row[j];

	    // cpu pipeline
	    int up = (i > 0) ? prevRow[j] : 0;
	    int left = (j > 0) ? row[j - 1] : 0;

	    perimeter += cell * 4;
	    perimeter -= (cell & up) * 2;
	    perimeter -= (cell & left) * 2;
	}
    }

    return perimeter;
}


/*
 *  using heap-based merge of sorted lists here because we can break the problem into n sorted lists.
 *  T: O(k log n), S: O(n)
 */
// cache behavior
struct NodekthSmallest {
    int val;
    int row;
    int col;
};

struct Compare {
    bool operator()(const NodekthSmallest &a, const NodekthSmallest &b) {
        return a.val > b.val;
    }
};

int Purgatory::kthSmallest(vector<vector<int>>& matrix, int k) {
    int n = matrix.size();

    priority_queue<NodekthSmallest, vector<NodekthSmallest>, Compare> minHeap;

    for (int i = 0; i < n; ++i) {
        minHeap.emplace(NodekthSmallest{matrix[i][0], i, 0});
    }

    int val = 0;

    for (int count = 0; count < k ; ++count) {
        const NodekthSmallest &top = minHeap.top();
	// register vs memory
	val = top.val;
	int row = top.row;
	int col = top.col;

	minHeap.pop();

        int nextCol = col + 1;
	if (nextCol < n) {
	    // register vs memory
            const auto &rowRef = matrix[row];
            minHeap.emplace(NodekthSmallest{rowRef[nextCol], row, nextCol});
	}
    }

    return val;
}

/*
 *  using pattern recognition from invariants here because we can break the problem into that each ship's head is the only unique indicator.
 *  T: O(mn), S: O(1)
 */
int Purgatory::countBattleships(vector<vector<char>>& board) {
    int m = board.size();
    
    if (m == 0) return 0;

    int n = board[0].size();
    int count = 0;

    for (int i = 0; i < m; ++i) {
	// register vs memory
	auto &row = board[i];
	auto &prev = (i > 0) ? board[i - 1] : row;
        for (int j = 0; j < n; ++j) {
	    // branch prediction
            if (board[i][j] == 'X' &&
	       (i == 0 || row[j] != 'X') &&
	       (j == 0 || prev[j - 1] != 'X'))
	        ++count;
	}
    }

    return count;
}


int largestRectangleArea(vector<int>& h) {
    
    int n = h.size();
    // cache behavior
    vector<int> st;
    st.reserve(n);

    int maxA = 0;

    for(int i = 0; i <= n; ++i) {
	// cache behavior
	int currHeight = (i == n ? 0 : h[i]);

        while (!st.empty() && h[st.back()] > currHeight) {
	    // register vs memory
	    int topIndex = st.back();
	    st.pop_back();

            int height = h[topIndex];
	    int width = st.empty() ? i : i - st.back() - 1;

	    int area = height * width;
	    if (area > maxA) maxA = area;
	}
	st.push_back(i);
    }
    return maxA;
}

/*
 *  using histogram-based dynamic accumulation approach here because we can break the proble into an extension of the largest rectangle in histogram problem.
 *  T: O(m*n), S: O(n)
 */
int Purgatory::maximalRectangle(vector<vector<char>>& matrix) {
    if (matrix.empty() || matrix[0].empty())
        return 0;

    int rows = matrix.size(), cols = matrix[0].size();

    vector<int> heights(cols, 0);

    int maxArea = 0;

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
	    // branch predication
            heights[j] = (matrix[i][j] == '1') * (heights[j] + 1);
	}
	int area = largestRectangleArea(heights);
	if (area > maxArea) maxArea = area;
    }
    return maxArea;
}





}
