#include <vector>

using namespace std;

// Global variables.
vector<int> res;
int min_sum = -1;

void f(vector<vector<int>> &m, vector<int> &c, vector<int> &a, int k, int s) {
    int n = m.size();
    if (k == n) {
        s += m[a[n - 1]][a[0]];
        if (min_sum == -1 || s < min_sum) {
            res = a;
            min_sum = s;
        }
    } else {
        for (int i = 0; i < n; i++) {
            if (c[i] != 0) continue;
            c[i] = 1;
            a[k] = i;
            int d = (k >= 1) ? m[a[k - 1]][a[k]] : 0;
            if (min_sum == -1 || s + d < min_sum) {
                f(m, c, a, k + 1, s + d);
            }
            // Backtrack
            c[i] = 0;
        }
    }
}

int main(int argc, char *argv[]) {
    // Initialize matrix.
    int n = 4;
    vector<vector<int>> m = vector<vector<int>>(n);
    m[0] = {0,  1,  10, 10};
    m[1] = {10, 0,  3,  15};
    m[2] = {21, 17, 0,  2};
    m[3] = {3,  22, 30, 0};

    // Initialize candidates and solution vectors.
    vector<int> c = vector<int>(n);
    vector<int> a = vector<int>(n);

    // Calculate solution.
    f(m, c, a, 0, 0);

    // Print solution.
    printf("min sum = %d\n", min_sum);
    for (int i = 0; i < n; i++) {
        printf("𝜋(%d) = %d\n", i + 1, res[i] + 1);
    }

    return 0;
}
