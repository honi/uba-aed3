#include <vector>

using namespace std;

vector<vector<int>> memo;

int top_down(vector<int> &w, vector<int> &s, int i, int k) {
    if (i == -1) return 0;
    if (k > s[i]) return top_down(w, s, i - 1, k);
    if (memo[i][k] == -1) {
        memo[i][k] = max(
            top_down(w, s, i - 1, k + w[i]) + 1,
            top_down(w, s, i - 1, k)
        );
    }
    return memo[i][k];
}

int bottom_up(vector<int> &w, vector<int> &s) {
    int n = w.size();

    int max_w = 0;
    for (int i = 0; i < n; i++) {
        max_w += w[i];
    }

    printf("bottom up matrix:\n");
    vector<vector<int>> m(n + 1, vector<int>(max_w + 1, 0));
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= max_w; j++) {
            if (i == 0) {
                m[i][j] = 0;
            } else {
                if (j > s[i - 1]) {
                    m[i][j] = m[i - 1][j];
                } else {
                    m[i][j] = max(
                        m[i - 1][j],
                        m[i - 1][min(max_w, j + w[i - 1])] + 1
                    );
                }
            }
            printf("%d ", m[i][j]);
        }
        printf("\n");
    }

    return m[n][1];
}

int main(int argc, char *argv[]) {
    vector<int> w = {19, 7, 5, 6, 1};
    vector<int> s = {15, 13, 7, 8, 2};

    printf("weights: [");
    for (int i = 0; i < w.size(); i++) {
        printf("%d", w[i]);
        if (i < w.size() - 1) printf(", ");
    }
    printf("]\n");

    printf("resistance: [");
    for (int i = 0; i < s.size(); i++) {
        printf("%d", s[i]);
        if (i < s.size() - 1) printf(", ");
    }
    printf("]\n");

    printf("total boxes: %lu\n", w.size());

    int max_w = 0;
    for (int i = 0; i < w.size(); i++) {
        max_w += w[i];
    }
    memo = vector<vector<int>>(w.size(), vector<int>(max_w, -1));

    printf("max boxes (top down): %d\n", top_down(w, s, w.size() - 1, 0));
    printf("max boxes (bottom up): %d\n", bottom_up(w, s));

    return 0;
}
