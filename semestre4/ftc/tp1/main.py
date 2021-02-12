#!/usr/bin/env python

import sys

# This is the only auxiliary function I'll be using in the whole code
def isSuffix(s1, s2): 
      
    n1 = len(s1) 
    n2 = len(s2) 
    if (n1 > n2): 
        return False
    for i in range(n1): 
        if(s1[n1 - i - 1] != s2[n2 - i - 1]): 
            return False
    return True

# Reading file
filename = sys.argv[1]
file = [line.rstrip() for line in open(filename)]

L = ''

# Organizing things into beautiful lists
states  = file[0].split(',')
states.append("Start")
states.append("End")
states.sort()
symbols = file[1].split(',')
symbols.append(L)
symbols.sort()
init    = file[2].split(',')
init.sort()
final   = file[3].split(',')
final.sort()

# Strip useless information
file = file[4:]

# Split everything
file    = [trans.split(',') for trans in file]
adj     = {}
adj_inv = {}

# Initializing dicts
for st in states:
    adj[st]     = []
    adj_inv[st] = []

# Processing transitions
for trans in file:
    if(len(trans) < 3): break
    a, s, b = trans
    
    # Creating adjacency lists
    adj[a].append([b, s])
    adj_inv[b].append([a, s])

# Adding lambda transitions
for ini in init:
    adj["Start"].append([ini, L])
    adj_inv[ini].append(["Start", L])
for end in final:
    adj[end].append(["End", L])
    adj_inv["End"].append([end, L])
    
# Sorting lists
for st in states:
    adj[st].sort()
    adj_inv[st].sort()
    
# Lets remove the midpoints
for mid in states:
    if mid == "End" or mid == "Start":
        continue
    
    # Treating loops
    for vt, reflex in adj[mid]:
        if vt == mid:
            adder = '(' + reflex + '*)'
            adj[mid].remove([mid, reflex])
            for end, s in adj[mid]:
                if(end == mid or isSuffix(adder, s)): continue
                # Fix the straight edge
                adj[mid].remove([end, s])
                adj[mid].append([end, s + adder])

                # Fix the reverse edge
                adj_inv[end].remove([mid, s])
                adj_inv[end].append([mid, s + adder])
        
    # For each vertex that comes to the midpoint
    for start, ss in adj_inv[mid]:
        # Continue if self loop
        if start == mid: continue
            
        # For each vertex that the midpoint goes to
        for end, se in adj[mid]:
            
            # Continue if self loop
            if end == mid: continue
            
            # Compress path
            adj[start].append([end, ss+se])
            adj_inv[end].append([start, ss+se])

            # Remove the reverse edge if it is there
            if [mid, se] in adj_inv[end]:
                adj_inv[end].remove([mid, se])
        # Remove the remaining edge if it is there
        if [mid, ss] in adj[start]:
            adj[start].remove([mid, ss])

# Now let's print the answer
answer_list = []

for isEnd, ans in adj["Start"]:
    if isEnd == "End":
        answer_list.append(ans)
        
answers = set(answer_list)
fans = ''

for ans in answer_list:
    fans += ("(" + ans + ")+")    

print(fans[1:-2])