#include <math.h>
#include <vector>

using namespace std;

const float infinity = numeric_limits<float>::infinity();
vector<vector<pair<float, float>>> top_down_memo;

pair<float, float> cc_backtracking(vector<int> &B, int i, int j) {
    if (i < 0 && j > 0) {
        return {infinity, infinity};
    } else if (j <= 0) {
        return {0, 0};
    } else {
        pair<float, float> r = cc_backtracking(B, i - 1, j - B[i]);
        return min(
            {B[i] + r.first, 1.0 + r.second},
            cc_backtracking(B, i - 1, j)
        );
    }
}

pair<float, float> cc_top_down(vector<int> &B, int i, int j) {
    if (i <= 0 && j > 0) {
        return {infinity, infinity};
    } else if (j <= 0) {
        return {0, 0};
    } else {
        if (top_down_memo[i - 1][j].first == -1) {
            pair<float, float> r = cc_top_down(B, i - 1, j - B[i - 1]);
            top_down_memo[i - 1][j] = min(
                {B[i - 1] + r.first, 1.0 + r.second},
                cc_top_down(B, i - 1, j)
            );
        }
        return top_down_memo[i - 1][j];
    }
}

pair<float, float> cc_bottom_up(vector<int> &B, int n, int c) {
    // Initialize memoization matrix.
    vector<vector<pair<float, float>>> M(
        n + 1,
        vector<pair<float, float>>(c + 1, {infinity, infinity})
    );
    M[0][0] = {0, 0};

    // Fill matrix bottom up.
    for (int i = 1; i <= n; i++) {
        for (int j = c; j >= 0; j--) {
            pair<float, float> r = M[i - 1][max(0, j - B[i])];
            M[i][j] = min(
                {B[i] + r.first, 1.0 + r.second},
                M[i - 1][j]
            );
        }
    }

    return M[n][c];
}

void print_result(pair<float, float> res, long long time) {
    printf("time: %lldms\n", time);
    if (res.first == infinity) {
        printf("no solution available\n");
    } else {
        printf("amount payed: %.0f\nnumber of bills: %.0f\n", res.first, res.second);
    }
}

int main(int argc, char *argv[]) {
    // Parse input.
    int N = atoi(argv[1]);
    int c = atoi(argv[2]);
    int n = atoi(argv[3]);
    vector<int> B(n);
    for (int i = 0; i < n; i++) {
        B[i] = atoi(argv[4 + i]);
    }

    // Print input.
    printf("c: %d\nn: %d\nB: {", c, n);
    for (int i = 0; i < n; i++) {
        printf("%d", B[i]);
        if (i < n - 1) printf(", ");
    }
    printf("}\n");

    // Prepare variables for benchmark.
    long long avg_elapsed;
    pair<float, float> res;

    // Top down with memoization.
    avg_elapsed = 0;
    printf("\nrunning top down with memoization (x %d times)...\n", N);
    for (int i = 0; i < N; i++) {
        auto start = chrono::high_resolution_clock::now();

        // Initialize memoization matrix and calculate result.
        top_down_memo = vector<vector<pair<float, float>>>(
            n + 1,
            vector<pair<float, float>>(c + 1, {-1, -1})
        );
        res = cc_top_down(B, n, c);

        auto end = chrono::high_resolution_clock::now();
        auto elapsed = chrono::duration_cast<chrono::milliseconds>(end - start);
        avg_elapsed += elapsed.count();
    }
    print_result(res, avg_elapsed / N);

    // Bottom up.
    avg_elapsed = 0;
    printf("\nrunning bottom up (x %d times)...\n", N);
    for (int i = 0; i < N; i++) {
        auto start = chrono::high_resolution_clock::now();

        // Calculate result.
        res = cc_bottom_up(B, n, c);

        auto end = chrono::high_resolution_clock::now();
        auto elapsed = chrono::duration_cast<chrono::milliseconds>(end - start);
        avg_elapsed += elapsed.count();
    }
    print_result(res, avg_elapsed / N);

    // Backtracking without memoization.
    avg_elapsed = 0;
    printf("\nrunning backtracking without memoization (x %.0f times, this takes a long time)...\n", ceil(N / 10));
    for (int i = 0; i < ceil(N / 10); i++) {
        auto start = chrono::high_resolution_clock::now();

        // Calculate result.
        res = cc_backtracking(B, n - 1, c);

        auto end = chrono::high_resolution_clock::now();
        auto elapsed = chrono::duration_cast<chrono::milliseconds>(end - start);
        avg_elapsed += elapsed.count();
    }
    print_result(res, avg_elapsed / N);

    return 0;
}
