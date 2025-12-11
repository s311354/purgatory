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
        for (int j = 0; j < cols; ++j) {
            if (grid[i][j] == 1) {
                perimeter += 4;

		if (i > 0 && grid[i - 1][j] == 1)
		    perimeter -= 2;

		if (j > 0 && grid[i][j - 1] == 1)
		    perimeter -= 2;
	    }
	}
    }
    return perimeter;
}

/*
 *  using heap-based merge of sorted lists here because we can break the problem into n sorted lists.
 *  T: O(k log n), S: O(n)
 */
int Purgatory::kthSmallest(vector<vector<int>>& matrix, int k) {
    int n = matrix.size();

    priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<tuple<int, int, int>>> minHeap;

    for (int i = 0; i < n; ++i) {
        minHeap.emplace(matrix[i][0], i, 0);
    }

    int val = 0;

    for (int count = 0; count < k ; ++count) {
        auto [num, r, c] = minHeap.top(); minHeap.pop();

	val = num;

	if (c + 1 < n)
	    minHeap.emplace(matrix[r][c+1], r, c+1);
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
        for (int j = 0; j < n; ++j) {
            if (board[i][j] != 'X') continue;

	    if (i > 0 && board[i - 1][j] == 'X') continue;
	    if (j > 0 && board[i][j - 1] == 'X') continue;
	    ++count;
	}
    }

    return count;
}


int largestRectangleArea(vector<int>& h) {
    stack<int> st;

    h.push_back(0);
    int maxA = 0;

    for(int i = 0; i < (int) h.size(); ++i) {
        while (!st.empty() && h[st.top()] > h[i]) {
            int height = h[st.top()]; st.pop();
	    int width = st.empty() ? i : i - st.top() - 1;
	    maxA = max(maxA, height * width);
	}
	st.push(i);
    }
    h.pop_back();
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

    vector<int> height(cols, 0);

    int maxArea = 0;

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (matrix[i][j] == '1')
                ++height[j];
	    else
                height[j] = 0;
	}
        maxArea = max(maxArea, largestRectangleArea(height));
    }
    return maxArea;
}





}
