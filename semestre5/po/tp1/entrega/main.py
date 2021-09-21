import numpy as np
from utils import less
from utils import matprint
import simplex
from simplex import solve

n, m, A, B, C = simplex.read()
A, B, C = simplex.fpi(A, B, C)

if(less(B.min(), 0)):
    ans = simplex.auxiliar(A, B, C, n, m)
    
    # Unviable
    if(less(ans[0], 0)):
        print("inviavel")
        for i in ans[2][1:n+1]: print(i, end = ' ')
        print()
        exit()
    
    # Transforms Auxiliar Back
    finalA = ans[3].copy()
    finalA = np.delete(finalA, [0], axis = 1)
    finalA = np.delete(finalA, [0], axis = 0)
    finalA = np.delete(finalA, slice(A.shape[0]+A.shape[1], -1), axis = 1)
    finalBase = [[x-1, y-1] for x, y in ans[-1]]
    ans = simplex.solveTableau(finalA, n, m, finalBase)
    
    if(len(ans) == 5):
        print("otima")
        print(ans[0])
        for i in ans[1][n:n+m]: print(i, end = ' ')
        print()
        for i in ans[2]: print(i, end = ' ')
            
    elif(len(ans) == 4):
        print("ilimitada")
        for i in ans[0][n:n+m]: print(i, end = ' ')
        print()
        for i in ans[1][n:n+m]: print(i, end = ' ')
            
    print()
    
    
else:
    firstBase = [[i, i+m] for i in range(n)] 
    ans = solve(A, B, C, firstBase)
    if(len(ans) == 5):
        print("otima")
        print(ans[0])
        for i in ans[1][:m]: print(i, end = ' ')
        print()
        for i in ans[2]: print(i, end = ' ')
            
    elif(len(ans) == 4):
        print("ilimitada")
        for i in ans[0]: print(i, end = ' ')
        print()
        for i in ans[1]: print(i, end = ' ')
            
    print()