#!/usr/bin/env python3
import random

def subset_sum_brute_force(S, T):
    n = len(S)
    res = []

    def f(a, i):
        nonlocal res
        if i == n:
            if sum(a) == T: res = a
        else:
            e = S[i]
            f(a + [e], i + 1)
            f(a, i + 1)

    f([], 0)
    return res


def run(S, T):
    res = subset_sum_brute_force(S, T)
    assert not res or sum(res) == T
    print(f"S={S} T={T} RES={res}")


if __name__ == "__main__":
    run([2, 5, 7, 10], 14)
    run([1, 1, 2, 3], 14)
    S = list(range(20))
    random.shuffle(S)
    run(S, random.randint(0, 50))
