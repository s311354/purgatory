#include "purgatory.h"

namespace purgatory {

/*
 *  using a degree-based counting method here because we can break the problem into
 *  - outgoing edges -> disqualify judge
 *  - incoming edges -> candidate for judge
 */
int Purgatory::findJudge(int n , vector<vector<int>>& trust) {
    vector<int> score(n + 1, 0);

    for (auto &t: trust) {
        int a = t[0], b = t[1];

	score[a]--;
	score[b]++;
    }

    for (int i = 0; i <= n; ++i) {
        if (score[i] == n - 1) return i;
    }
    return -1;
}

void dfsNumIslands(vector<vector<char>>& grid, int i, int j) {
    int m = grid.size(), n = grid[0].size();

    if (i < 0 || j < 0 || i >= m || j >= n || grid[i][j] == '0') return;

    grid[i][j] = '0';

    dfsNumIslands(grid, i + 1, j);
    dfsNumIslands(grid, i - 1, j);
    dfsNumIslands(grid, i, j + 1);
    dfsNumIslands(grid, i, j - 1);
}

/*
 *  using DFS here because we can break the problem into
 *  - treat every '1' as a potential start of an island
 *  - once we find it, mark the whole island to avoid reconnecting
 */
int Purgatory::numIslands(vector<vector<char>>& grid) {
    if (grid.empty()) return 0;

    int m = grid.size(), n = grid[0].size();
    int count = 0;

    for (int i = 0; i < m ; ++i) {
        for (int j = 0; j < n; ++j) {
            if (grid[i][j] == '1') {
                count++;
                dfsNumIslands(grid, i, j);
	    }
	}
    }
    return count;
}


void dfsSolve(vector<vector<char>>& board, int i, int j) {
    int m = board.size(), n = board[0].size();

    if ( i < 0 || j < 0 || i >= m || j >= n || board[i][j] != 'O') return;

    board[i][j] = '#';

    dfsSolve(board, i + 1, j);
    dfsSolve(board, i - 1, j);
    dfsSolve(board, i, j + 1);
    dfsSolve(board, i, j - 1);
}

/*
 *  using DFS here because we can break the problem into two phases
 *  - identify safe O's from border
 *  - flip the rest
 */
void Purgatory::solve(vector<vector<char>> & board) {
    if (board.empty()) return;

    int m = board.size(), n = board[0].size();

    for (int i = 0; i < m  ; ++i) {
        dfsSolve(board, i, 0);
	dfsSolve(board, i, n - 1);
    }

    for (int i = 0; i < n; ++i) {
        dfsSolve(board, 0, i);
	dfsSolve(board, m - 1, i);
    }

    for(int i = 0; i < m; ++i) {
        for(int j = 0; j < n; ++j) {
            if (board[i][j] == '#')
                board[i][j] = 'O';
	    else if (board[i][j] == 'O') 
		board[i][j] = 'X';
	}
    }
}

vector<vector<int>> memo;
vector<vector<int>> dir = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

int dfsLongestIncreasingPath(vector<vector<int>>& matrix, int i, int j) {
    if (memo[i][j] != 0) return memo[i][j];

    int m = matrix.size(), n = matrix[0].size();

    int best = 1;

    for(auto & d : dir) {
        int x = i + d[0], y = j + d[1];
	if (x >= 0 && y >= 0 && x < m && y < n && matrix[x][y] > matrix[i][j])
	    best = max(best, 1 + dfsLongestIncreasingPath(matrix, x, y));
    }

    memo[i][j] = best;
    return best;
}

/*
 *  using DFS + memorization here because we can break the problem into overlapping subproblems: each cell's longest path depends only on its neighbors
 */
int Purgatory::longestIncreasingPath(vector<vector<int>>& matrix) {
    if (matrix.empty() || matrix[0].empty()) return 0;

    int m = matrix.size(), n = matrix[0].size();

    memo.assign(m, vector<int>(n, 0));

    int ans = 0;

    for(int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            ans = max(ans, dfsLongestIncreasingPath(matrix, i, j));
	}
    }
    return ans;
}

}
