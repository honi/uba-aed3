#!/usr/bin/env python3
import random

def subset_sum_backtracking(S, T):
    n = len(S)
    res = []

    def f(a, i, sum_a):
        nonlocal res

        # Encontramos una solución válida.
        if sum_a == T:
            res = a
            return True

        # Hay elementos para agregar y no nos pasamos de T.
        if i < n and sum_a < T:
            e = S[i]
            return f(a + [e], i + 1, sum_a + e) or f(a, i + 1, sum_a)

        # No hay solución por esta rama.
        return False

    f([], 0, 0)
    return res


def run(S, T):
    res = subset_sum_backtracking(S, T)
    assert not res or sum(res) == T
    print(f"S={S} T={T} RES={res}")


if __name__ == "__main__":
    run([2, 5, 7, 10], 14)
    run([1, 1, 2, 3], 14)
    S = list(range(20))
    random.shuffle(S)
    run(S, random.randint(0, 50))
