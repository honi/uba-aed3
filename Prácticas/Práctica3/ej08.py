n = 3
m = 3
M = [
    None,
    [None, 1, 3, 6],
    [None, 6, 7, 4],
    [None, 4, 9, 3],
]
k = 10
w = 0
(xi, yi) = (1, 1)

def solve():
    visited = [[[False] * k for _ in range(m + 1)] for _ in range(n + 1)]
    path_length = 1
    level_count = 1
    next_level_count = 0
    Q = []
    Q.append((xi, yi, M[xi][yi]))

    while Q:
        (x1, y1, v1) = Q.pop(0)
        if v1 == w: return path_length

        for (dx, dy) in [(1, 0), (-1, 0), (0, 1), (0, -1)]:
            (x2, y2) = (x1 + dx, y1 + dy)
            if not(1 <= x2 <= n and 1 <= y2 <= m): continue
            v2 = (v1 + M[x2][y2]) % k
            if visited[x2][y2][v2]: continue
            Q.append((x2, y2, v2))
            visited[x2][y2][v2] = True
            next_level_count += 1

        level_count -= 1
        if level_count == 0:
            level_count = next_level_count
            next_level_count = 0
            path_length += 1

    return -1

if __name__ == '__main__':
    print(solve())
