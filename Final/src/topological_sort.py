#!/usr/bin/env python3
from graph import Graph
from dfs import dfs

def topological_sort(G):
    dfs(G)
    return sorted(G.V, key=lambda v: -v.finish)


def run(G):
    print(f"Topological sort on {G}")
    print(topological_sort(G))


if __name__ == "__main__":
    G = Graph(
        V=[1, 2, 3],
        Adj={
            1: [2],
            2: [3],
        },
    )
    run(G)

    G = Graph(
        V=[1, 2, 3],
        Adj={
            1: [3],
            2: [3],
        },
    )
    run(G)

    G = Graph(
        V=[1, 2, 3],
        Adj={
            1: [2],
            2: [3],
            3: [1],
        },
    )
    run(G)
