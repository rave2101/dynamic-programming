#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    int fib(int n) {
        vector<int> cache(n + 1, -1);
        return solve(n, cache);
    }

    int solve(int n, vector<int>& cache) {
        if (n <= 1) return n;
        if (cache[n] != -1) return cache[n];
        cache[n] = solve(n - 1, cache) + solve(n - 2, cache);
        return cache[n];
    }
};
