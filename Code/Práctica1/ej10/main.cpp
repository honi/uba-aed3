#include <vector>

using namespace std;

vector<int> w = {19, 7, 5, 6, 1};
vector<int> s = {15, 13, 7, 8, 2};
vector<vector<vector<int>>> memo;

vector<int> f(int i, int k) {
    if (i == -1) return {};
    if (k > s[i]) return f(i - 1, k);
    if (memo[i][k].size() == 0) {
        vector<int> a = f(i - 1, k + w[i]);
        a.push_back(i);
        vector<int> b = f(i - 1, k);
        memo[i][k] = a.size() >= b.size() ? a : b;
    }
    return memo[i][k];
}

int main(int argc, char *argv[]) {
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

    int M = 0;
    for (int i = 0; i < w.size(); i++) {
        M += w[i];
    }

    memo = vector<vector<vector<int>>>(w.size(), vector<vector<int>>(M));
    vector<int> res = f(w.size() - 1, 0);

    printf("total boxes: %lu\n", w.size());
    printf("max boxes: %lu\n", res.size());
    printf("solution: [");
    for (int i = 0; i < res.size(); i++) {
        printf("%d", res[i]);
        if (i < res.size() - 1) printf(", ");
    }
    printf("]\n");

    printf("box\tweight\tacc. weight\tresistance\n");
    int k = 0;
    for (int i = res.size() - 1; i >= 0; i--) {
        printf("%d\t%d\t%d\t\t%d\n", res[i], w[res[i]], k, s[res[i]]);
        k += w[res[i]];
    }

    return 0;
}
