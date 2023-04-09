#include <vector>

using namespace std;

// This is a naive implementation because it generates a lot of invalid squares.
// To avoid this we need to implement branch and bound tactics.

bool is_valid(vector<vector<int>> &s) {
    int n = s.size();

    // Calculate magic number.
    int m = 0;
    for (int i = 0; i < n; i++) {
        m += s[i][0];
    }

    // Check rows and columns.
    for (int i = 0; i < n; i++) {
        int row = 0;
        int col = 0;
        for (int j = 0; j < n; j++) {
            row += s[i][j];
            col += s[j][i];
        }
        if (row != m || col != m) return false;
    }

    // Check diagonals.
    int diagonal1 = 0;
    int diagonal2 = 0;
    for (int i = 0; i < n; i++) {
        diagonal1 += s[i][i];
        diagonal2 += s[i][n - i - 1];
    }
    if (diagonal1 != m || diagonal2 != m) return false;

    return true;
}

int magic_squares(vector<vector<int>> &s, int i, int j, vector<int> &c) {
    int n = s.size();
    if (j == n) return magic_squares(s, i + 1, 0, c); // Continue on next row.
    if (i == n) return is_valid(s); // Square is filled.
    int r = 0; // Solutions counter.
    for (int k = 0; k < n * n; k++) {
        if (c[k] == 0) { // k is available.
            s[i][j] = k + 1;
            c[k] = 1;
            r += magic_squares(s, i, j + 1, c);
            c[k] = 0; // Backtrack.
        }
    }
    return r;
}

int main(int argc, char *argv[]) {
    // Parse input.
    int n = atoi(argv[1]);

    // Initialize arguments.
    vector<vector<int>> s(n, vector<int>(n)); // magic square
    vector<int> c(n * n); // candidates

    int r = magic_squares(s, 0, 0, c);
    printf("%dx%d magic squares (naive): %d\n", n, n, r);

    return 0;
}
