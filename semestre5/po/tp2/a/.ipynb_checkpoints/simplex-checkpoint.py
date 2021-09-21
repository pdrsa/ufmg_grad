import numpy as np

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