#include "purgatory.h"

namespace purgatory {

/*
 *  using a degree-based counting method here because we can break the problem into
 *  - outgoing edges -> disqualify judge
 *  - incoming edges -> candidate for judge
 *  T: O(m + n), S: O(n)
 */
int Purgatory::findJudge(int n , vector<vector<int>>& trust) {
    if (n == 1 && trust.empty()) return 1;


    vector<int16_t> score(n + 1, 0);
    // register vs memory
    int16_t *s = score.data();

    // cache behavior
    int m = trust.size();
    for (int i = 0; i < m; ++i) {
        int a = trust[i][0], b = trust[i][1];

	s[a]--;
	s[b]++;
    }

    // register vs memory
    int target = n - 1;
    for (int i = 0; i <= n; ++i) {
        if (s[i] == target) return i;
    }
    return -1;
}

/*
 *  using DFS here because we can break the problem into
 *  - treat every '1' as a potential start of an island
 *  - once we find it, mark the whole island to avoid reconnecting
 *  T: O(m*n), S: O(1)
 */
int Purgatory::numIslands(vector<vector<char>>& grid) {
    int m = grid.size();
    if (m == 0) return 0;
    int n = grid[0].size();
    int count = 0;

    // register vs memory
    int dirs[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

    // function call
    vector<pair<int, int>> st;
    st.reserve(m * n);

    for (int i = 0; i < m ; ++i) {
        for (int j = 0; j < n; ++j) {
	    // branch prediction
            if (grid[i][j] != '1')
	        continue;

            count++;
	    st.emplace_back(i, j);
	    grid[i][j] = '0';

	    while (!st.empty()) {
                auto [r, c] = st.back();
		st.pop_back();
                 
		for (int k = 0; k < 4; ++k) {
		    int nr = r + dirs[k][0];
		    int nc = c + dirs[k][1];

		    // branch prediction
		    if ((unsigned) nr < (unsigned) m && (unsigned) nc < (unsigned) n && grid[nr][nc] == '1') {
		    
		        grid[nr][nc] = '0';
			st.emplace_back(nr, nc);
		    }
		}
 
	    }
	}
    }
    return count;
}

/*
 *  using DFS here because we can break the problem into two phases
 *  - identify safe O's from border
 *  - flip the rest
 *  T: O(m * n), S: O(1)
 */
void Purgatory::solve(vector<vector<char>> & board) {
    int m = board.size();
    if (m == 0) return;
    int n = board[0].size();

    // register vs memory
    int dirs[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

    // function call
    vector<pair<int, int>> q;
    q.reserve(m * n);

    // cpu pipeline
    auto push = [&](int r, int c) {
        if (board[r][c] == 'O') {
	    board[r][c] = '#';
	    q.emplace_back(r, c);
	}
    };

    for (int i = 0; i < m  ; ++i) {
        push(i, 0);
	push(i, n - 1);
    }

    for (int j = 0; j < n; ++j) {
        push(0, j);
	push(m - 1, j);
    }

    for (int i = 0; i < q.size(); ++i) {
        auto [r, c] = q[i];

	for (int k = 0; k < 4; ++k) {
	    // register vs memory
            int nr = r + dirs[k][0];
	    int nc = c + dirs[k][1];

	    // branch prediction
	    if ((unsigned) nr < (unsigned) n && (unsigned) nc < (unsigned) n && board[nr][nc] == 'O') {
	        board[nr][nc] = '#';
		q.emplace_back(nr, nc);
	    }
	}
    }


    for(int i = 0; i < m; ++i) {
	// register vs memory
	auto &row = board[i];
        for(int j = 0; j < n; ++j) {
            if (row[j] == '#')
                row[j] = 'O';
	    else if (row[j] == 'O') 
		row[j] = 'X';
	}
    }
}

/*
 *  using DFS + memorization here because we can break the problem into overlapping subproblems: each cell's longest path depends only on its neighbors
 *  T: O(m*n), S: O(m*n)
 */
int Purgatory::longestIncreasingPath(vector<vector<int>>& matrix) {
    if (matrix.empty() || matrix[0].empty()) return 0;

    int m = matrix.size(), n = matrix[0].size();
    // cache behavoir
    vector<vector<int>> memo(m, vector<int>(n, 0));

    // register vs memory
    int dirs[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

    // function call
    for (int r = 0; r < m; ++r) {
        for (int c = 0; c < n ; ++c) {
	    for (int k = 0; k< 4; ++k) {
                int nr = r + dirs[k][0];
		int nc = c + dirs[k][1];

		if ((unsigned) nr < (unsigned) m && (unsigned) nc < (unsigned) n && matrix[nr][nc] > matrix[r][c]) {
                    memo[r][c]++;
		}
	    }
	}
    }

    queue<pair<int, int>> q;

    for (int r = 0; r < m; ++r) {
        for (int c = 0; c < n; ++c) {
	    if (memo[r][c] == 0) {
                q.emplace(r, c);
	    }
	}
    }

    int ans = 0;

    while (!q.empty()) {
        int sz = q.size();
	ans++;

	while (sz--) {
            auto [r, c] = q.front(); q.pop();

	    for (int k = 0; k < 4; ++k) {
		// register vs memory
	        int nr = r + dirs[k][0];
		int nc = c + dirs[k][1];

		// branch prediction
		if ((unsigned) nr < (unsigned) m && (unsigned) nc < n && matrix[nr][nc] < matrix[r][c]) {
		    if(--memo[nr][nc] == 0)
		        q.emplace(nr, nc);
		}
	    
	    }
	}
    }

    return ans;
}

}
