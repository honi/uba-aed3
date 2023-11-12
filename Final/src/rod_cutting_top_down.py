#!/usr/bin/env python3

def rod_cutting_top_down(n, p):
    memo = [-1] * (n+1)

    def r(n):
        if n == 0:
            memo[n] = 0
        elif memo[n] == -1:
            for i in range(1, n+1):
                memo[n] = max(memo[n], p[i] + r(n-i))
        return memo[n]

    return r(n)


def run(n, p):
    print(f"n={n} max={rod_cutting_top_down(n, p)}")


if __name__ == "__main__":
    p = [0, 1, 5, 8, 9, 10, 17, 17, 20, 24, 30]
    print(f"p={p}")
    for n in range(1, len(p)):
        run(n, p)
