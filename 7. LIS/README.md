# Longest Increasing Subsequence (LIS)

Problems based on finding the longest increasing subsequence pattern, including variants like Longest Divisible Subset, Longest String Chain, and Longest Bitonic Subsequence.

---

## Solutions

| File | Approach | Time | Space |
|---|---|---|---|
| `memoization.cpp` | Top-Down DP | O(n²) | O(n²) |
| `nlogn.cpp` | Binary Search (Patience Sorting) | O(n log n) | O(n) |

---

## O(n log n) — How It Works

Maintain a `result` array where `result[i]` holds the **smallest possible tail** of any increasing subsequence of length `i+1`.

For each element:
- If it's **larger than the last element** → append it (LIS length grows)
- Otherwise → **replace** the first element ≥ current with `lower_bound`

`result` is always sorted, which is why binary search works.

> **Note:** `result` does not store the actual LIS — only `result.size()` (the length) is meaningful.

---

## What is `lower_bound`?

`lower_bound(begin, end, val)` performs **binary search** on a sorted range and returns an iterator to the **first element that is ≥ val**.

```
result = [2, 3, 7, 101]

lower_bound for 5:
  Check mid=7 → 7 >= 5, go left
  Check mid=3 → 3 < 5,  go right
  → points to 7 (first element >= 5)

result[2] = 5  →  result = [2, 3, 5, 101]
```

### Why replace instead of insert?

Replacing keeps tails **as small as possible**, which gives future elements the best chance of extending the subsequence.

```
nums = [3, 5, 6, 2, 5, 4, 19, 5, 6, 7, 12]

After processing 3,5,6  → result = [3, 5, 6]        length = 3
num = 2 → replace 3    → result = [2, 5, 6]        length = 3 (unchanged)
num = 5 → replace 6    → result = [2, 5, 5] ← wait, lower_bound(5) points to first 5
                                                     replace → [2, 5, 5]?
```

Actually since this is strictly increasing LIS, `lower_bound` finds the first element **≥ val**, so equal elements get replaced too (preventing duplicates from extending the LIS). For non-strictly increasing, use `upper_bound` instead.

### `lower_bound` vs `upper_bound`

| | Returns first element | Use for |
|---|---|---|
| `lower_bound` | **≥ val** | Strictly increasing LIS |
| `upper_bound` | **> val** | Non-decreasing LIS |
