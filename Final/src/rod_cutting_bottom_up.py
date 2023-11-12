#!/usr/bin/env python3

def rod_cutting_bottom_up(n, p):
    memo = [-1] * (n+1)
    memo[0] = 0

    # Por cada longitud j.
    for j in range(1, n+1):
        # Probamos todos los posibles cortes en 1 <= i <= j.
        for i in range(1, j+1):
            memo[j] = max(memo[j], p[i] + memo[j-i])

    return memo[n]


def run(n, p):
    print(f"n={n} max={rod_cutting_bottom_up(n, p)}")


if __name__ == "__main__":
    p = [0, 1, 5, 8, 9, 10, 17, 17, 20, 24, 30]
    print(f"p={p}")
    for n in range(1, len(p)):
        run(n, p)
