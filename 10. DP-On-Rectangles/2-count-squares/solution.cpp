#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int countSquares(vector<vector<int>>& matrix) {
        int R = matrix.size(), C = matrix[0].size(), count = 0;
        vector<vector<int>> dp(R, vector<int>(C, 0));

        for (int i = 0; i < C; i++) { dp[0][i] = matrix[0][i]; count += dp[0][i]; }
        for (int i = 1; i < R; i++) { dp[i][0] = matrix[i][0]; count += dp[i][0]; }

        for (int i = 1; i < R; i++) {
            for (int j = 1; j < C; j++) {
                if (matrix[i][j] == 1) {
                    dp[i][j] = 1 + min({dp[i-1][j], dp[i][j-1], dp[i-1][j-1]});
                }
                count += dp[i][j];
            }
        }
        return count;
    }
};
