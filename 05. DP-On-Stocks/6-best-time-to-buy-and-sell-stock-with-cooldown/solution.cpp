#include <bits/stdc++.h>
using namespace std;

// Tabulation (Bottom-Up) — the one-day cooldown is the `i+2` jump on sell
class Solution {
public:
    int maxProfit(const vector<int>& prices) {
        int n = prices.size();
        vector<vector<int>> dp(n + 2, vector<int>(2, 0));
        for (int i = n - 1; i >= 0; i--) {
          dp[i][1] = max(-prices[i] + dp[i + 1][0],dp[i + 1][1]);
          dp[i][0] = max(prices[i] + dp[i + 2][1],dp[i + 1][0]);
        }
        return dp[0][1];
    }
};

int main() {
    Solution s;

    vector<int> p1 = {1, 2, 3, 0, 2};
    cout << "[1,2,3,0,2] -> " << s.maxProfit(p1) << "\n";   // 3

    vector<int> p2 = {1};
    cout << "[1] -> " << s.maxProfit(p2) << "\n";           // 0

    vector<int> p3 = {6, 1, 3, 2, 4, 7};
    cout << "[6,1,3,2,4,7] -> " << s.maxProfit(p3) << "\n"; // 6

    return 0;
}
