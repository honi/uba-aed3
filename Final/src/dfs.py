#!/usr/bin/env python3
from graph import Graph

def dfs(G):
    time = 1

    def dfs_visit(u):
        nonlocal time
        u.visited = True
        u.start = time
        time += 1
        for v in G.Adj[u]:
            if not v.visited:
                v.parent = u
                dfs_visit(v)
        u.finish = time
        time += 1

    for u in G.V:
        u.visited = False
        u.parent = None

    for u in G.V:
        if not u.visited:
            dfs_visit(u)


def run(G):
    print(f"DFS on {G}")
    dfs(G)
    for v in G.V:
        print(f"{v}: parent={v.parent} start={v.start} finish={v.finish}")


if __name__ == "__main__":
    G = Graph(
        V=[1, 2, 3, 4, 5, 6],
        Adj={
            1: [2, 4],
            2: [5],
            3: [5, 6],
            4: [2],
            5: [4],
            6: [6],
        },
    )
    run(G)
