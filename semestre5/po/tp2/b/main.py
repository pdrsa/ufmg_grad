import numpy as np
# Reading Input
n, m = map(int, input().split())
c    = [int(x) for x in input().split()]
c    = np.array(c)
A    = [[] for i in range(n)]
sets = [set() for i in range(m)]
for i in range(n):
    A[i] = np.array([int(x) for x in input().split()])
    
    for j in range(m):
        if(A[i][j]):
            sets[j].add(i)
            
A = np.array(A)


# In[109]:


ansSets = []
idxSets = np.zeros(m)
x       = np.zeros(n)
for i in range(n):
    got = False
    # Check on n log n <- We're gonna end up with a O(n^2 log n) algorithm but that's ok
    for st in ansSets:
        if i in st:
            got = True
            break
    if got: continue
    
    # Find maximum value for x
    augment = float('inf')
    for j in range(m):
        cur = (A.T[j] @ x) - A.T[j][i] * x[i]
        if(A.T[j][i] > 0): augment = min(augment, (c[j] - cur) / A.T[j][i])    
    x[i] = augment
    
    # Find row in which A^Tx <= c equality happens
    for j in range(m):
        if A[i][j] and A.T[j] @ x == c[j]:
            ansSets.append(sets[j])
            idxSets[j] = 1
            break


# In[114]:


for idx in idxSets: print(int(idx), end = " ")
print()
for val in x: print(int(val), end = " ")
print()

