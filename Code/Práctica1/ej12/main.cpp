#include <vector>

using namespace std;

vector<vector<int>> f_memo;
vector<vector<vector<int>>> g_memo;

int f(int n, int s, int k) {
    if (n == 0 && s == 0) return 1;
    if (n == 0 && s != 0) return 0;
    if (n > 0 && s <= 0) return 0;
    if (s > n * k) return 0;
    if (f_memo[n][s] == -1) {
        int r = 0;
        for (int i = 1; i <= k; i++) {
            r += f(n - 1, s - i, k);
        }
        f_memo[n][s] = r;
    }
    return f_memo[n][s];
}

int g(int n, int s, int k) {
    if (n == 0 && s == 0) return 1;
    if (n == 0 && s != 0) return 0;
    if (n > 0 && s <= 0) return 0;
    if (s > n * k) return 0;
    if (k == 0) return 0;
    if (g_memo[n][s][k] == -1) {
        int r = 0;
        int m = s / k; // integer division (rounds down)
        for (int i = 0; i <= m; i++) {
            r += g(n - i, s - k * i, k - 1);
        }
        g_memo[n][s][k] = r;
    }
    return g_memo[n][s][k];
}

int main(int argc, char *argv[]) {
    // Parse input.
    int n = atoi(argv[1]);
    int s = atoi(argv[2]);
    int k = atoi(argv[3]);
    int min_s_nk = min(s, n * k);

    // Print input.
    printf("n: %d\ns: %d\nk: %d\n", n, s, k);

    // Calculate and print f solution.
    f_memo = vector<vector<int>>(
        n + 1,
        vector<int>(min_s_nk + 1, -1)
    );
    printf("f(%d, %d, %d) = %d\n", n, s, k, f(n, s, k));

    // Calculate and print g solution.
    g_memo = vector<vector<vector<int>>>(
        n + 1,
        vector<vector<int>>(min_s_nk + 1,
            vector<int>(k + 1, -1)
        )
    );
    printf("g(%d, %d, %d) = %d\n", n, s, k, g(n, s, k));

    return 0;
}
