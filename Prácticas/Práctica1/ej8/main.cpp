#include <math.h>
#include <vector>

using namespace std;

vector<vector<int>> memo;

int f(vector<int> &c, int i, int j) {
    if (i + 1 == j) return 0;
    if (memo[i][j] == -1) {
        int m = c[c.size() - 1]; // max cost
        for (int k = i + 1; k < j; k++) {
            m = min(m, f(c, i, k) + f(c, k, j));
        }
        memo[i][j] = (c[j] - c[i]) + m;
    }
    return memo[i][j];
}

int main(int argc, char *argv[]) {
    // Parse input.
    int l = atoi(argv[1]);
    int cn = atoi(argv[2]) + 2;
    vector<int> c(cn);
    c[0] = 0;
    c[cn - 1] = l;
    for (int i = 0; i < cn - 2; i++) {
        c[i] = atoi(argv[3 + i]);
    }
    sort(c.begin(), c.end());

    // Print input.
    printf("l: %d\nc: [", l);
    for (int i = 0; i < cn; i++) {
        printf("%d", c[i]);
        if (i < cn - 1) printf(", ");
    }
    printf("]\n");

    // Calculate solution.
    memo = vector<vector<int>>(cn, vector<int>(cn, -1));
    int res = f(c, 0, cn - 1);
    printf("solution: %d\n", res);

    return 0;
}
