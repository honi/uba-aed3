def f(A, B):
    r = 0
    i = 0
    j = 0
    while i < len(A) and j < len(B):
        if abs(A[i] - B[j]) <= 1:
            r += 1
            i += 1
            j += 1
        elif A[i] < B[j]:
            i += 1
        elif B[j] < A[i]:
            j += 1
    return r

print(f([1, 2, 4, 6], [1, 5, 5, 7, 9])) # 3
print(f([1, 1, 1, 1, 1], [1, 2, 3])) # 2
print(f([], [1, 2])) # 0
print(f([6, 6, 6], [7, 7, 7])) # 3
