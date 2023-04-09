#include <vector>

using namespace std;

// Optimized implementation using O(k) space.

bool subset_sum(vector<int> &c, int k) {
    vector<bool> m(k + 1);
    m[0] = true;
    for (int i = 0; i < c.size(); i++) {
        for (int j = k; j >= 1; j--) {
            m[j] = m[j] || (j - c[i] == 0) || (j >= c[i] && m[j - c[i]]);
        }
    }
    return m[k];
}

int main(int argc, char *argv[]) {
    // Parse input.
    int k = atoi(argv[1]);
    int n = atoi(argv[2]);
    vector<int> c(n);
    for (int i = 0; i < n; i++) {
        c[i] = atoi(argv[3 + i]);
    }

    // Print input.
    printf("k: %d\nn: %d\nc: {", k, n);
    for (int i = 0; i < n; i++) {
        printf("%d", c[i]);
        if (i < n - 1) printf(", ");
    }
    printf("}\n");

    // Let's go!
    bool res = subset_sum(c, k);
    printf("solution exists: %s\n", res ? "yes" : "no");

    return 0;
}
