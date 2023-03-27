#include <stdio.h>
#include <vector>

using namespace std;

vector<int> res;
int max_sum = -1;

void matrix_sum(vector<vector<int>> &m, int k, vector<int> a, int s, vector<int> &c) {
    if (k == 0) {
        if (s > max_sum) {
            res = a;
            max_sum = s;
        }
    } else {
        int n = m.size();
        for (int i = 0; i < n; i++) {
            if (c[i] != 0) continue;
            c[i] = 1;
            a.push_back(i);
            int d = 0;
            for (int j = 0; j < a.size(); j++) {
                d += m[i][a[j]] + m[a[j]][i];
            }
            matrix_sum(m, k - 1, a, s + d, c);
            // Backtrack
            c[i] = 0;
            a.pop_back();
        }
    }
}

int main(int argc, char *argv[]) {
    // Parse input.
    int k = atoi(argv[1]);

    // Initialize matrix.
    int n = 4;
    vector<vector<int>> m = vector<vector<int>>(n);
    // m[0] = {0,  10, 10, 1};
    // m[1] = {10, 0,  5,  2};
    // m[2] = {10, 5,  0,  1};
    // m[3] = {1,  2,  1,  0};
    m[0] = {1, 5, 3, 9};
    m[1] = {5, 0, 2, 1};
    m[2] = {3, 2, 8, 4};
    m[3] = {9, 1, 4, 6};

    // Initialize candidates vector.
    vector<int> c = vector<int>(n);

    // Calculate solution.
    matrix_sum(m, k, {}, 0, c);

    // Print solution.
    printf("matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int count = 0;
            for (int z = 0; z < k; z++) {
                if (res[z] == i || res[z] == j) count++;
            }
            if (count == 2 || (count == 1 && i == j)) {
                // Highlight
                printf("\033[1;32m%d\033[0m", m[i][j]);
            } else {
                printf("%d", m[i][j]);
            }
            if (j < n - 1) printf("\t");
        }
        printf("\n");
    }
    printf("solution: {");
    for (int i = 0; i < k; i++) {
        printf("%d", res[i]);
        if (i < k - 1) printf(", ");
    }
    printf("}\n");
    printf("max sum = %d\n", max_sum);

    return 0;
}
