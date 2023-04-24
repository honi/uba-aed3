def insert_sorted(A, i, k):
    j = len(A)
    while i + 1 < j:
        m = i + (j - i) // 2
        if A[m] < k:
            i = m
        else:
            j = m
    return A[:i+1] + [k] + A[j:]

def f(A):
    A.sort() # O(n log n)
    r = 0
    i = 0
    while i < len(A) - 1:
        k = A[i] + A[i + 1]
        r += k
        i += 1
        # En C++ la lista estaría implementada como una lista doblemente enlazada
        # para poder borrar e insertar elementos en cualquier posición en O(1).
        del A[i] # O(1)
        A = insert_sorted(A, i, k) # O(log n) para encontrar la posición y O(1) para insertar k.
    return r

print(f([5, 2, 1]))
print(f([1, 2, 6, 5, 5]))
