# Count Squares in a Binary Matrix

## Problem

Given a binary matrix, count the total number of squares (of all sizes) that contain only `1`s.

---

## Example

```
matrix:
1 1 1
1 1 1
1 1 1

Output: 14
```

- 1×1 squares: 9
- 2×2 squares: 4
- 3×3 squares: 1
- Total: 14

---

## What `dp[i][j]` means

`dp[i][j]` = **side length of the largest square whose bottom-right corner is at `(i, j)`**.

This is the key insight: if the largest square ending at `(i,j)` has side 3, then squares of side 1, 2, and 3 all have their bottom-right corner there. So `dp[i][j]` directly tells you **how many new squares are introduced** at that cell — which is why you add `dp[i][j]` to `count`.

---

## Recurrence

```
if matrix[i][j] == 0:  dp[i][j] = 0  (no square possible)
if matrix[i][j] == 1:  dp[i][j] = min(dp[i-1][j], dp[i][j-1], dp[i-1][j-1]) + 1
```

---

## Why min of three neighbors?

To form a square of side `k` at `(i,j)`, three sub-squares of side `k-1` must all exist:

```
dp[i-1][j-1]  dp[i-1][j]
    ■ ■ .          . ■ ■
    ■ ■ .          . ■ ■
    . . .          . . .

dp[i][j-1]
    . . .
    ■ ■ .
    ■ ■ .
```

Each neighbor covers a different "quadrant". Together they guarantee all cells of the `k×k` square are `1`. The **weakest neighbor** is the bottleneck:

```
If dp[i-1][j-1] = 1 (only guarantees 1×1 top-left):

? ■ ■              ← top-left corner NOT guaranteed
■ ■ ■
■ ■ ■

Cannot form a 3×3 → min(1,2,2)+1 = 2
```

---

## Trace — matrix = [[1,1,1],[1,1,1],[1,1,1]]

**Base cases** (first row and column copied directly):

```
dp after base:
1 1 1
1 _ _
1 _ _
```

**Fill rest:**

```
i=1, j=1: min(dp[0][1]=1, dp[1][0]=1, dp[0][0]=1) + 1 = 2
i=1, j=2: min(dp[0][2]=1, dp[1][1]=2, dp[0][1]=1) + 1 = 2
i=2, j=1: min(dp[1][1]=2, dp[2][0]=1, dp[1][0]=1) + 1 = 2
i=2, j=2: min(dp[1][2]=2, dp[2][1]=2, dp[1][1]=2) + 1 = 3

dp:
1 1 1
1 2 2
1 2 3
```

**Count = sum of all dp values = 1+1+1+1+2+2+1+2+3 = 14**

---

## Trace — one cell is 0 (showing the bottleneck)

```
matrix:        dp:
1 1 1          1 1 1
1 0 1    →     1 0 1
1 1 1          1 1 ?
```

`i=2, j=2: min(dp[1][2]=1, dp[2][1]=1, dp[1][1]=0) + 1 = 1`

The `0` at `(1,1)` kills the diagonal. Even though left and top neighbors are `1`, the diagonal is `0` — top-left corner of any 2×2 would be a `0`. So only a 1×1 is possible.

```
0 ■           ← top-left is 0, 2×2 impossible
■ ■
```

---

## Why `count += dp[i][j]`

`dp[i][j] = k` means k squares of sizes 1×1, 2×2, ... k×k all have their bottom-right corner at `(i,j)`. Adding `k` to count registers all of them in one step.

```
dp[i][j] = 3  means:

■ . .    ■ ■ .    ■ ■ ■
. . .    ■ ■ .    ■ ■ ■
. . ↗    . . ↗    ■ ■ ↗
1×1      2×2      3×3     → 3 squares, add 3 to count
```

---

## Complexity

| | Time | Space |
|---|---|---|
| Tabulation | O(R × C) | O(R × C) |
