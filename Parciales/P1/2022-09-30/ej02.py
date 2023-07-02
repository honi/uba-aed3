I = [
    None, # Para indexar en 1.
    [1, 4],
    [2, 4],
    [2, 8],
    [4, 6],
    [7, 10],
    [8, 12],
]
n = len(I)

def s(i): return I[i][0]
def t(i): return I[i][1]

def solve():
    T = []
    i = 1
    j = 2
    m = 2
    while j < n:
        if t(i) >= s(j):
            T.append((i, j))
            if t(j) > t(m):
                m = j
            j += 1
        else:
            i = m
    return T

if __name__ == '__main__':
    print(solve())
