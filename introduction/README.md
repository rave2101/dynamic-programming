# Fibonacci — Recursion & Memoization

## Problem
Given `n`, return the nth Fibonacci number.
```
fib(0) = 0
fib(1) = 1
fib(n) = fib(n-1) + fib(n-2)
```

---

## Approach 1 — Pure Recursion (Inefficient)

The naive approach directly translates the formula into code:

```cpp
int fib(int n) {
    if (n <= 1) return n;
    return fib(n - 1) + fib(n - 2);
}
```

### How the recursive calls work for `fib(5)`

Every call splits into two more calls until it hits a base case (`n <= 1`).

```
                        fib(5)
                       /      \
                  fib(4)       fib(3)
                 /     \       /    \
            fib(3)   fib(2) fib(2) fib(1)
            /   \     /  \    /  \
        fib(2) fib(1) fib(1) fib(0) fib(1) fib(0)
        /   \
    fib(1) fib(0)
```

### How the call stack looks

Recursion always goes **left first** (`n-1`) before going right (`n-2`).
Each function call is pushed onto the stack and waits until its children return.

```
→ fib(5)                          [stack: fib(5)]
  → fib(4)                        [stack: fib(5), fib(4)]
    → fib(3)                      [stack: fib(5), fib(4), fib(3)]
      → fib(2)                    [stack: fib(5), fib(4), fib(3), fib(2)]
        → fib(1) = 1 ✓            [stack: fib(5), fib(4), fib(3), fib(2), fib(1)]
        → fib(0) = 0 ✓            [stack: fib(5), fib(4), fib(3), fib(2), fib(0)]
      ← fib(2) = 1 + 0 = 1        [fib(2) popped, returns 1 to fib(3)]
      → fib(1) = 1 ✓
    ← fib(3) = 1 + 1 = 2          [fib(3) popped, returns 2 to fib(4)]
    → fib(2)                      [fib(2) computed AGAIN]
      → fib(1) = 1 ✓
      → fib(0) = 0 ✓
    ← fib(2) = 1
  ← fib(4) = 2 + 1 = 3            [fib(4) popped, returns 3 to fib(5)]
  → fib(3)                        [fib(3) computed AGAIN]
    → fib(2)                      [fib(2) computed AGAIN]
      → fib(1) = 1 ✓
      → fib(0) = 0 ✓
    ← fib(2) = 1
    → fib(1) = 1 ✓
  ← fib(3) = 2
← fib(5) = 3 + 2 = 5
```

### Why this is inefficient

`fib(3)` is computed **2 times**. `fib(2)` is computed **3 times**. This gets worse as `n` grows.

| n  | Total calls |
|----|-------------|
| 5  | 15          |
| 10 | 177         |
| 20 | 21,891      |
| 50 | ~billions   |

**Time complexity: O(2ⁿ)** — the call tree doubles at every level.

---

## Approach 2 — Memoization (Efficient)

The core observation: **we are solving the same subproblems repeatedly**.
The fix: solve each subproblem once and **store the result in a cache**.

```cpp
class Solution {
public:
    int fib(int n) {
        vector<int> cache(n + 1, -1); // -1 means not computed yet
        return solve(n, cache);
    }

    int solve(int n, vector<int>& cache) {
        if (n <= 1) return n;
        if (cache[n] != -1) return cache[n];          // already solved, return instantly
        cache[n] = solve(n - 1, cache) + solve(n - 2, cache);
        return cache[n];
    }
};
```

### Why two functions?

`fib()` creates the cache of size `n+1` (all `-1`) and kicks off the recursion.
`solve()` does the actual work and takes the cache by reference so every recursive call shares the same cache.

### How the calls work now for `fib(5)`

```
→ solve(5)
  → solve(4)
    → solve(3)
      → solve(2)
        → solve(1) = 1 ✓
        → solve(0) = 0 ✓
      ← solve(2) = 1   [cache[2] = 1]
      → solve(1) = 1 ✓
    ← solve(3) = 2     [cache[3] = 2]
    → solve(2) ← CACHE HIT, returns 1 instantly (no further calls)
  ← solve(4) = 3       [cache[4] = 3]
  → solve(3) ← CACHE HIT, returns 2 instantly (no further calls)
← solve(5) = 5         [cache[5] = 5]
```

### Cache state at each step

```
Initial:        cache = [-1, -1, -1, -1, -1, -1]
After solve(2): cache = [-1, -1,  1, -1, -1, -1]
After solve(3): cache = [-1, -1,  1,  2, -1, -1]
After solve(4): cache = [-1, -1,  1,  2,  3, -1]
After solve(5): cache = [-1, -1,  1,  2,  3,  5]
```

---

## Complexity Comparison

|                | Pure Recursion | Memoization  |
|----------------|----------------|--------------|
| Time           | O(2ⁿ)          | O(n)         |
| Space          | O(n) callstack | O(n) cache + O(n) callstack |
| Repeated work  | Yes            | No           |

---

## How to Run

```bash
g++ -o fibonacci fibonacci.cpp && ./fibonacci
```
