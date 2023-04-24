#include <limits>
#include <vector>

using namespace std;

int m = 3;
int n = 3;
vector<vector<int>> A = {
    {-2,  -3,  3},
    {-5, -10,  1},
    {10,  30, -5},
};

vector<vector<int>> memo(m, vector<int>(n, -1));

int f(int i, int j) {
    // When we reach this position outside A we treat it as the base case from where
    // to build up the required life. We return 1 because that's the minimum life.
    if (i == m && j == n - 1) return 1;

    // Any other position outside A return +infinity.
    if (!(0 <= i && i < m && 0 <= j && j < n)) return numeric_limits<int>::max();

    if (memo[i][j] == -1) {
        memo[i][j] = max(1, min(f(i + 1, j), f(i, j + 1)) - A[i][j]);
    }

    return memo[i][j];
}

int main(int argc, char *argv[]) {
    // Print matrix.
    printf("A:\n");
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (A[i][j] >= 0) printf(" ");
            printf("%d", A[i][j]);
            if (j < n - 1) printf("\t");
        }
        printf("\n");
    }

    // Calculate solution.
    int res = f(0, 0);
    printf("solution: %d\n", res);

    return 0;
}
