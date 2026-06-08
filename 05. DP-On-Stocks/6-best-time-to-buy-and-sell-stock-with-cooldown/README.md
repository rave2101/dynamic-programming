# Best Time to Buy and Sell Stock with Cooldown

## Problem
Given `prices[i]` for each day, complete any number of transactions (buy then sell, never holding more than one share) to maximize profit. **Constraint:** after selling, you cannot buy on the very next day — a one-day cooldown.

```
prices = [1,2,3,0,2]  ->  3    (buy, sell, cooldown, buy, sell)
prices = [1]          ->  0
prices = [6,1,3,2,4,7] -> 6    (buy@1, sell@7)
```

## Approach
1. **State** `dp[i][buy]` = max profit from day `i` onward, where `buy = 1` means we're allowed to buy and `buy = 0` means we're currently holding a share.
2. **Allowed to buy:** either buy today (`-prices[i]`, switch to holding) or skip.
   `dp[i][1] = max(-prices[i] + dp[i+1][0], dp[i+1][1])`
3. **Holding:** either sell today or keep holding. Selling triggers the cooldown — jump to `dp[i+2]`, skipping the next day entirely.
   `dp[i][0] = max(prices[i] + dp[i+2][1], dp[i+1][0])`
4. The single `i + 2` lookup **is** the cooldown rule — no extra "cooldown state" needed.
5. Allocate `n + 2` zero-initialized rows so the `i+2` access stays in bounds. Answer is `dp[0][1]`.

## Complexity
- **Time:** `O(n)` — one pass, two states per day.
- **Space:** `O(n)` — reducible to `O(1)` with rolling variables for rows `i+1` and `i+2`.

## Why this works
The cooldown only matters at the moment of selling: it forbids buying on day `i+1`. By resuming from `dp[i+2][1]` right after a sale, the recurrence structurally bans the day-`i+1` buy without tracking an explicit third state.
