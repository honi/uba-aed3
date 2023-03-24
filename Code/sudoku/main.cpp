#include <fstream>
#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>

using namespace std;
using sudoku = vector<vector<int>>;

bool solve_sudoku(sudoku &grid, vector<vector<int>> &candidates, int i) {
    int n = grid.size();
    int row = i / n;
    int col = i % n;
    int subgrid = row / 3 * 3 + col / 3;

    if (i == n * n) return true;
    if (grid[row][col] > 0) return solve_sudoku(grid, candidates, i + 1);

    for (int num = 0; num < n; num++) {
        // Check if num is a valid candidate.
        if (candidates[row][num] != 0) continue;
        if (candidates[n + col][num] != 0) continue;
        if (candidates[n * 2 + subgrid][num] != 0) continue;

        // Set num in the grid and remove it from candidates.
        grid[row][col] = num + 1;
        candidates[row][num] = 1;
        candidates[n + col][num] = 1;
        candidates[n * 2 + subgrid][num] = 1;

        // Solve recursively.
        if (solve_sudoku(grid, candidates, i + 1)) return true;

        // Did not produce a valid solution, backtrack.
        grid[row][col] = 0;
        candidates[row][num] = 0;
        candidates[n + col][num] = 0;
        candidates[n * 2 + subgrid][num] = 0;
    }

    return false;
}

bool load_sudoku(char *filename, sudoku &grid) {
    printf("loading grid: %s\n", filename);

    ifstream f(filename);
    if (!f.is_open()) {
        printf("error loading grid\n");
        return false;
    }

    int n = grid.size();
    int row = 0;
    string line;
    while (f && row < n) {
        getline(f, line);
        for (int col = 0; col < n; col++) {
            char item = line[col * 2];
            grid[row][col] = item == '-' ? 0 : item - '0';
        }
        row++;
    }

    return true;
}

void print_sudoku(sudoku &grid) {
    int n = grid.size();
    for (int row = 0; row < n; row++) {
        for (int col = 0; col < n; col++) {
            printf("%d ", grid[row][col]);
            if (col < n - 1) printf(" ");
        }
        printf("\n");
    }
}

int main(int argc, char *argv[]) {
    int n = 9;
    sudoku grid(n, vector<int>(n));

    if (argv[1] == NULL) {
        printf("missing grid filename\n");
        return 1;
    } else {
        if (!load_sudoku(argv[1], grid)) {
            return 1;
        }
    }

    // 0 = available, 1 = used
    // candidates[0..8]   --> used numbers by row
    // candidates[9..17]  --> used numbers by column
    // candidates[18..26] --> used numbers by subgrid
    vector<vector<int>> candidates(n * 3, vector<int>(n));
    for (int row = 0; row < n; row++) {
        for (int col = 0; col < n; col++) {
            int num = grid[row][col];
            if (num > 0) {
                int subgrid = row / 3 * 3 + col / 3;
                candidates[row][num - 1] = 1;
                candidates[n + col][num - 1] = 1;
                candidates[n * 2 + subgrid][num - 1] = 1;
            }
        }
    }

    solve_sudoku(grid, candidates, 0);
    print_sudoku(grid);

    return 0;
}
