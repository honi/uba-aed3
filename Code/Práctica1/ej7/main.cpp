#include <math.h>
#include <vector>

using namespace std;

const float infinity = numeric_limits<float>::infinity();
vector<vector<int>> memo;

float max_profit(vector<int> &p, int j, int c) {
    // c < 0: buy before sell
    // c > j: buy more than 1 asteroid per day
    if (c < 0 || c > j) return -infinity; // invalid scenarios
    if (j == 0) return 0; // valid base case
    if (memo[j - 1][c] == -1) {
        float res = max_profit(p, j - 1, c); // do nothing
        res = max(res, max_profit(p, j - 1, c - 1) - p[j - 1]); // buy
        memo[j - 1][c] = max(res, max_profit(p, j - 1, c + 1) + p[j - 1]); // sell
    }
    return memo[j - 1][c];
}

int main(int argc, char *argv[]) {
    // Parse input.
    int n = atoi(argv[1]);
    vector<int> p(n);
    for (int i = 0; i < n; i++) {
        p[i] = atoi(argv[2 + i]);
    }

    // Print input.
    printf("n: %d\np: (", n);
    for (int i = 0; i < n; i++) {
        printf("%d", p[i]);
        if (i < n - 1) printf(", ");
    }
    printf(")\n");

    // Calculate solution.
    int memo_rows = n;
    int memo_cols = ceil((n + 1) / 2.0);
    printf("memoization matrix size: %d x %d\n", memo_rows, memo_cols);
    memo = vector<vector<int>>(memo_rows, vector<int>(memo_cols, -1));
    float res = max_profit(p, n, 0);
    printf("max profit: %.0f\n", res);

    return 0;
}
