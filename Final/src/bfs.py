#!/usr/bin/env python3
from graph import Graph

def bfs(G, s):
    for v in G.V:
        v.visited = False
        v.distance = -1 # -infty
        v.parent = None

    s.visited = True
    s.distance = 0
    s.parent = None

    q = [s]
    while q:
        u = q.pop(0)
        for v in G.Adj[u]:
            if not v.visited:
                v.visited = True
                v.distance = u.distance + 1
                v.parent = u
                q.append(v)


def run(G, s):
    bfs(G, s)
    for v in G.V:
        print(f"d({s}, {v}) = {v.distance}")


if __name__ == "__main__":
    G = Graph(
        V=[1, 2, 3, 4, 5, 6, 7, 8],
        Adj={
            1: [2, 5],
            2: [1, 6],
            3: [4, 7],
            4: [3, 7, 8],
            5: [1],
            6: [2, 3, 7],
            7: [3, 4, 6, 8],
            8: [4, 7],
        },
    )
    run(G, G.get(2))
