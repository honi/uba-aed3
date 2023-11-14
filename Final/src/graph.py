class Node:
    def __init__(self, id: int):
        self.id = id

    def __repr__(self):
        return str(self.id)


class Graph:
    def __init__(self, V: list[int], Adj: dict[int, list[int]]):
        self.V = [Node(v) for v in V]
        self.Adj = {
            v: [self.get(u) for u in Adj.get(v.id, [])]
            for v in self.V
        }
        self.E = [
            (u, v)
            for u, nu in self.Adj.items()
            for v in nu
        ]

    def get(self, id: int):
        for v in self.V:
            if v.id == id: return v

    def __repr__(self):
        return f"G=({self.V}, {self.Adj})"
