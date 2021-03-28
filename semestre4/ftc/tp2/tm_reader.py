#!/usr/bin/env python
# coding: utf-8

# Reading and processing data
inp          = input("Insira sua entrada: \n")
tm, word     = inp.split("000", 1)
transString  = tm.split('00')
positions    = word.split('0')
fStates      = transString[0].split('0')
transString  = transString[1:]

# Creating dictionary of transitions
trans = dict()
for string in transString:
    tList = string.split('0')
    key   = (tList[0] + "." + tList[1])
    value = (tList[2] + "." + tList[3] + "." + tList[4])
    trans[key] = value
    
# Creating tape
tape = ['1']
tape += positions
tape += ['11' for i in range(1000 - len(tape))]

# Initial pos and state
state = '1'
pos   = 1

# Processing
for tries in range(1000):
	
	# State of Loop
    if pos >= 1000: 
        state = '--'
        break
    
	# Deciding symbol
    symbol = tape[pos]
    key = (state + "." + symbol)
    
    if key in trans:
        e, b, d   = trans[key].split(".", 2)
        state     = e
        tape[pos] = b
        if(d == '11'): pos -= 1
        else: pos += 1
        
    else:
        break

# Check if ended on a fState
if state in fStates:
    print("ACEITO")
else:
    print("REJEITADO")
