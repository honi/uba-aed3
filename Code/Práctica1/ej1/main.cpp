#include <vector>

using namespace std;

bool subset_sum(vector<int> &c, int i, int j, int r, vector<int> &p) {
    if (j < 0) return false; // Impossible to sum up to a negative number.
    if (j > r) return false; // Target number is bigger than the sum of all remaining elements.
    if (i == 0) return j == 0; // Base case, check if valid solution.
    r -= c[i - 1]; // Remove current element from the sum of all remaining elements.

    // Check solutions that don't include the current element.
    if (subset_sum(c, i - 1, j, r, p)) {
        return true;
    }

    // Check solutions that include the current element.
    p.push_back(c[i - 1]);
    if (subset_sum(c, i - 1, j - c[i - 1], r, p)) {
        return true;
    }

    // If we got here, there are no solutions down this path.
    p.pop_back();
    return false;
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

    // Initial sum of all remaining elements.
    int r = 0;
    for (int i = 0; i < n; i++) {
        r += c[i];
    }

    // Initialize solution vector.
    vector<int> p;
    p.reserve(n);

    // Let's go!
    subset_sum(c, n, k, r, p);

    // Print solution.
    int m = p.size();
    printf("solution: {");
    for (int i = 0; i < m; i++) {
        printf("%d", p[i]);
        if (i < m - 1) printf(", ");
    }
    printf("}\n");

    return 0;
}
