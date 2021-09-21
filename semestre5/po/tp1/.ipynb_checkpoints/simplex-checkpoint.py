import numpy as np
from utils import less
from utils import matprint

# Reads the Input for the problem
# Returns 2 integers and 3 numpy arrays
def read():
    n, m = list(map(int, input().split()))
    C = np.array(list(map(int, input().split())))
    A = []
    for i in range(n): A.append(list(map(int, input().split())))
    A = np.array(A)
    B = A[:, m]
    A = A[:, :m]
    
    # Transforming everything in Float
    A, B, C  = A.astype(np.float), B.astype(np.float), C.astype(np.float)
    
    return n, m, A, B, C

# Returns A and C in FPI
def fpi(A, B, C):
    # Add slack variables
    A = np.append(A, np.identity(A.shape[0]), axis = 1)
    C = np.append(C, np.zeros(A.shape[0]))
    
    return A, B, C


# Receives Matrix A and Arrays B and C and returns the Tableau
def tableau(A, B, C, invert = [], iniVal = 0):
    # Base for VEROtm
    VERO = np.identity(A.shape[0])
    # Inverting
    for i in invert: VERO[i] = -VERO[i]
    VERO = np.vstack([np.zeros(A.shape[0]), VERO])

    # Add restriction values
    A = np.append(A, np.array([B]).T, axis = 1)

    # Add cost in A
    C = -C
    C = np.append(C, np.zeros(A.shape[1] - C.shape[0]))
    A = np.vstack([C, A])

    # Append VERO
    A = np.append(VERO, A, axis = 1)
    
    if less(0, iniVal):
        A[0][-1] = iniVal
    
    return A


# Receives a base of columns and a LP in optimum state. Returns the variables solution.
def recoverBase(A, baseCols, n, m, compensate = True):
    base = np.zeros(m)
    for row, col in baseCols:
        if compensate: colP     = col - n # Compensating for VERO columns
        else: colP = col
        # Sanity check
        assert(not less(1, A[:,col].sum()))
        base[colP] = A[row][-1]
    
    return base

# Receives a base of columns and an unlimited LP..
def recoverIli(A, baseCols, iliCol, n, m, compensate = True):
    cert    = np.zeros(m)
    iliColP = iliCol - n
    cert[iliColP] = 1
    for row, col in baseCols:
        if compensate: colP = col - n
        else: colP = col
            
        # Sanity check
        assert(col != iliCol)
        
        cert[colP] = -A[row][iliCol]
        
    return cert


# Pivot the element in position [row][col]
def pivot(A, row, col):
    assert(not np.isclose(A[row][col], 0))
    # Divide the row so the element becomes 1
    A[row] = A[row]/A[row][col]
    
    # For each element in col
    for i in range(len(A)):
        # I've already changed this row
        if i == row: continue
        # X -= (A[row] * X) Since A[row][col] == 1, X will become 0.
        A[i] -= (A[row] * A[i][col])

        
# Input:    Vectors A, B, C and a viable base firstBase.
# Outputs:  Value, Base and Certificate for LP.
def solve(A, B, C, firstBase, invert = [], auxiliar = False, iniVal = 0):
    n, m = A.shape
    A = tableau(A, B, C, invert, iniVal)
    
    baseCols = []
    for row, col in firstBase: # Compensating VERO
        baseCols.append([row+1, col+n])
    
    # Canonize for base
    for row, col in baseCols:
        if not np.isclose(A[0][col], 0):
            pivot(A, row, col)
    
    while(1):
        # Se cN < 0, X é ótima
        if(not less(np.min(A[0][n:-1]), 0)): 
            value = A[0][-1]
            cert  = A[0][:n]
            base  = recoverBase(A, np.array(baseCols), n, m)
            return [value, base, cert, A, baseCols]

        # Find an entry smaller than 0
        for j in range(n, A.shape[1]):
            if less(A[0][j], 0):
                col = j
                break

        # Se Ak < 0, A PL é ilimitada.
        if(less(np.max(A[:,col][1:]), 0)):
            base = recoverBase(A, np.array(baseCols), n, m)
            cert = recoverIli(A, np.array(baseCols), col, n, m)
            return [base, cert, A, baseCols]
        
        # Iterate over column and find Index
        minRatio = float('inf')
        row = -1
        start = (2 if auxiliar else 1)
        for i in range(start, A.shape[0]):
            if(np.isclose(A[i][col], 0) or less(A[i][col], 0)): continue
            if(less(A[i][-1]/A[i][col], minRatio)):
                row       = i
                minRatio  = A[i][-1]/A[i][col]
        
        # Sanity Check 
        assert(row > 0)
        
        # Finds Col to be replaced
        for i in range(len(baseCols)):
            if baseCols[i][0] == row:
                baseCols.pop(i)
                break
        # Adds new Col
        baseCols.append([row, col])
        
        # Pivot
        pivot(A, row, col)
        
def auxiliar(A, B, C, n, m):
    invert = []
    # Making B positive
    for i in range(B.shape[0]):
        if less(B[i], 0):
            B[i] = -B[i]
            A[i] = -A[i]
            invert.append(i+1)
    
    AAux    = np.append(A, np.identity(A.shape[0]), axis = 1)
    BAux    = np.append(0, B)
    CAux    = np.append(np.zeros(A.shape[1]), np.full(A.shape[0], -1))
    CAlong  = np.append(-C, np.zeros(A.shape[0]))
    AAux    = np.vstack([CAlong, AAux])
    baseAux = [[i+1, i+n+m] for i in range(n)]
    ans     = solve(AAux, BAux, CAux, baseAux, invert = invert, auxiliar = True)
    
    return ans

# Input:    Vectors A, B, C and a viable base firstBase.
# Outputs:  Value, Base and Certificate for LP.
def solveTableau(A, n, m, baseCols = []):
    
    # Canonize for base
    for row, col in baseCols:
        if not np.isclose(A[0][col], 0):
            pivot(A, row, col)
            
    while(1):
        # Se cN < 0, X é ótima
        if(not less(np.min(A[0][n:-1]), 0)): 
            value = A[0][-1]
            cert  = A[0][:n]
            base  = recoverBase(A, np.array(baseCols), A.shape[0], A.shape[1], compensate = False)
            return [value, base, cert, A, baseCols]

        # Find an entry smaller than 0
        for j in range(n, A.shape[1]):
            if less(A[0][j], 0):
                col = j
                break

        # Se Ak < 0, A PL é ilimitada.
        if(less(np.max(A[:,col][1:]), 0)):
            base = recoverBase(A, np.array(baseCols), A.shape[0], A.shape[1], compensate = False)
            cert = recoverIli(A, np.array(baseCols), col, A.shape[0], A.shape[1], compensate = False)
            return [base, cert, A, baseCols]
        
        # Iterate over column and find Index
        minRatio = float('inf')
        row = -1
        for i in range(1, A.shape[0]):
            if(np.isclose(A[i][col], 0) or less(A[i][col], 0)): continue
            if(less(A[i][-1]/A[i][col], minRatio)):
                row       = i
                minRatio  = A[i][-1]/A[i][col]
        
        # Sanity Check 
        assert(row > 0)
        
        # Finds Col to be replaced
        for i in range(len(baseCols)):
            if baseCols[i][0] == row:
                baseCols.pop(i)
                break
        # Adds new Col
        baseCols.append([row, col])
        
        # Pivot
        pivot(A, row, col)