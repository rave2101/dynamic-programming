#include <bits/stdc++.h>
using namespace std;

// Memoization (Top-Down) — two travelers moving down the grid together
class Solution {
public:
    int maxChocolates(vector<vector<int>>& g) {
        int R = g.size(), C = g[0].size();
        vector<vector<vector<int>>> dp(R, vector<vector<int>>(C, vector<int>(C, -1)));
        return solve(0, 0, C - 1, g, R, C, dp);   // Alice at 0, Bob at C-1
    }
private:
    int solve(int i, int j1, int j2, vector<vector<int>>& g, int R, int C,
              vector<vector<vector<int>>>& dp) {
        if (j1 < 0 || j1 >= C || j2 < 0 || j2 >= C) return -1e9;  // off-grid
        if (dp[i][j1][j2] != -1) return dp[i][j1][j2];

        int collect = g[i][j1];
        if (j1 != j2) collect += g[i][j2];        // overlap counted once

        if (i == R - 1) return dp[i][j1][j2] = collect;

        int best = 0;
        for (int dj1 = -1; dj1 <= 1; dj1++)
            for (int dj2 = -1; dj2 <= 1; dj2++)
                best = max(best, solve(i + 1, j1 + dj1, j2 + dj2, g, R, C, dp));

        return dp[i][j1][j2] = collect + best;
    }
};

int main() {
    Solution s;

    vector<vector<int>> g1 = {{2, 3, 1, 2}, {3, 4, 2, 2}, {5, 6, 3, 5}};
    cout << "grid 3x4 -> " << s.maxChocolates(g1) << "\n";   // 21

    vector<vector<int>> g2 = {{1, 2}, {3, 4}};
    cout << "grid 2x2 -> " << s.maxChocolates(g2) << "\n";   // 10

    return 0;
}
