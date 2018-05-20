from diff import *
from sympy import *

N = 100000
TOL = 0.00001
P0 = -1000.0
delta = 20
NoRoot = True
firstRoot = True
root = list()
G = DIFF(input())
P = 0.0

i = -100
while i < 100:
    j=0
    while j < N:
        P = P0 - G.fv(P0)/G.ffv(P0)
        if firstRoot and abs(P-P0)<TOL:
            root.append(P)
            firstRoot = False
            NoRoot = False
        if abs(P-P0)<TOL and abs(root[-1]-P)>TOL:
            root.add(P)
        P0 = P
        j+=1

    i += delta

if NoRoot:
    print("Solution not found.")
else:
    print(root)
