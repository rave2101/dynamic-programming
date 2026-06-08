# Ninja and His Friends (Chocolates)

## Problem
A grid `R x C` holds chocolates in each cell. Two friends move down together: **Alice** starts at `(0, 0)`, **Bob** at `(0, C-1)`. From `(i, j)` each may move to `(i+1, j-1)`, `(i+1, j)`, or `(i+1, j+1)`, staying in bounds. Each collects its cell's chocolates; if both land on the **same cell it counts once**. Maximize the total collected.

```
grid = [[2,3,1,2],[3,4,2,2],[5,6,3,5]]  ->  21
grid = [[1,2],[3,4]]                     ->  10
```

> Same as **Cherry Pickup II** (Striver DP-13). See also [`5-cherry-pickup-ii`](../5-cherry-pickup-ii/) for the tabulation write-up.

## Approach
1. Both travelers always sit on the **same row** `i`, so the state is `(i, j1, j2)` — Alice's column and Bob's column. A single column index can't model two people; that's the key insight.
2. Collect `g[i][j1]`, and add `g[i][j2]` **only if `j1 != j2`** (overlap rule).
3. From each row both move independently → **9 transitions**: every `(dj1, dj2)` in `{-1, 0, +1}²`.
4. Recurrence: `f(i, j1, j2) = collect + max over 9 moves of f(i+1, j1+dj1, j2+dj2)`.
5. Base row `i == R-1` returns just `collect`. Off-grid columns return a large negative so they never win the `max`. Answer is `f(0, 0, C-1)`.

## Complexity
- **Time:** `O(R · C² · 9)` — `R·C²` states, 9 transitions each.
- **Space:** `O(R · C²)` memo + recursion stack `O(R)`.

## Common Bugs
- **Tracking one traveler instead of two.** A 1D `dp[col]` cannot represent "Alice at `j1` and Bob at `j2`" — the state must be 3D `(i, j1, j2)`.
- **Double-counting the shared cell.** Guard the second add with `if (j1 != j2)`.
- **Off-grid sentinel.** Returning `-1e9` (not `0`) for out-of-bounds columns keeps invalid paths from being chosen.
