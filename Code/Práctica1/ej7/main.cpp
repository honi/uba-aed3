#include <math.h>
#include <stdio.h>
#include <vector>

using namespace std;

const float infinity = numeric_limits<float>::infinity();

float max_profit(vector<int> &p, int j, int c) {
    // c < 0: buy before sell
    // c > j: buy more than 1 asteroid per day
    if (c < 0 || c > j + 1) return -infinity; // invalid scenarios
    if (j == -1) return 0; // valid base case
    float res = max_profit(p, j - 1, c); // do nothing
    res = max(res, max_profit(p, j - 1, c - 1) - p[j]); // buy
    res = max(res, max_profit(p, j - 1, c + 1) + p[j]); // sell
    return res;
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
    float res = max_profit(p, n - 1, 0);
    printf("max profit: %.0f\n", res);

    return 0;
}
