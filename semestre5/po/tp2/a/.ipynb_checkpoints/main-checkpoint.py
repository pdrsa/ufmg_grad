import numpy as np


# Usei o código do Simpĺex de Bernardo Teixeira Amorim Neto
# ================================== INÍCIO DO CÓDIGO COPIADO =================================================

epsilon = 1e-7

def equal(a, b):
    return abs(a - b) < epsilon

def pivot(M, i, j):
    assert not equal(M[i][j], 0)
    
    M[i] = np.multiply(M[i], 1. / M[i][j])
    
    for i2 in range(len(M)):
        if i != i2:
            M[i2] = np.add(M[i2], np.multiply(M[i], -M[i2][j]))

def simplex(T, n, m, B, is_auxiliary):
    while True:
        c = -1
        for j in range(m):
            if -T[0][n + j] > epsilon:
                c = j
                break
        
        if c == -1: # optimal
            return 0

        r = -1
        s = 1
        if is_auxiliary:
            s = 2

        for i in range(n):
            if T[s + i][n + c] > epsilon:
                if r == -1 or T[s + i][n + m] / T[s + i][n + c] < T[s + r][n + m] / T[s + r][n + c]:
                    r = i

        if r == -1: # unlimited
            return 2
    
        pivot(T, s + r, n + c)
        B[r] = c

def solve(A, b, c):
    n = len(b)
    m = len(c)

    # tableux
    T = np.vstack((np.zeros(n), np.identity(n)))
    T = np.hstack((T, np.vstack((np.multiply(c, -1), A))))
    T = np.hstack((T, np.vstack((np.zeros(1), b.reshape((-1, 1))))))

    for i in range(n):
        if T[1 + i][n + m] < -epsilon:
            T[1 + i] = np.multiply(T[1 + i], -1)

    # add auxiliay linear programming to tableux
    aux_line = np.zeros(n + m + n + 1)
    for i in range(n):
        aux_line[n + m + i] = 1
    
    T = np.hstack((T[:, :n + m], np.vstack((np.zeros(n), np.identity(n))), T[:, n + m:]))
    T = np.vstack((aux_line, T))
    
    # create basis
    B = [0 for i in range(n)]
    for i in range(n):
        B[i] = m + i
        pivot(T, 2 + i, n + m + i)

    type = simplex(T, n, m + n, B, True)

    assert type == 0
    # not viable
    if T[0][n + n + m] < -epsilon:
        return 1, T, B
    
    # removes auxiliary linear programming from tableux
    T = T[1:, :]
    T = np.hstack((T[:, :n + m], T[:, n + m + n:]))

    # fix basis
    for i in range(n):
        if B[i] > m:
            for j in range(m):
                if not equal(T[1 + i][n + j], 0):
                    B[i] = j
                    pivot(T, 1 + i, n + B[i])
                    break

    type = simplex(T, n, m, B, False)
    return type, T, B


# ================================== FIM DO CÓDIGO COPIADO =================================================



n, m = map(int, input().split())
c    = np.array(list(map(int, input().split())))
N    = [[] for i in range(n)]
for i in range(n):
    N[i] = np.array([int(x) for x in input().split()])
N    = np.array(N)

p  = -N[0]
N_ = N[1:-1]
A = np.concatenate((N_, -N_), axis = 0)
A = np.concatenate((A, np.eye(m)), axis = 0)

b = np.concatenate((np.array([0 for i in range(2*(n-2))]), c), axis = 0)

p = np.concatenate((p, np.zeros(len(A))), axis = 0)
A = np.concatenate((A, np.eye(len(A))), axis = 1)

_, tableux, basis = solve(A, b, p)


n1 = n
n, m = (len(b), len(p))
x = np.zeros(m - n)
for i in range(n):
    if basis[i] < m - n:
        x[basis[i]] = tableux[1 + i][n + m]

print(int(tableux[0][-1]))
for num in x: print(int(num), end = " ")
print()
ans_ = tableux[0, :n]
ans_ = ans_[:(n1-2)]
print(1, end = " ")
for num in ans_: print(int(num), end = " ")
print(0)