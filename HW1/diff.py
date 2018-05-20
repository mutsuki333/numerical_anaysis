from sympy import *
import sys

x = Symbol('x')

class DIFF:
    """docstring for [object Object]."""
    def __init__(self, func):
        self.f = S(func)
        self.ff = diff(func, x, 1)

    def fv(self, value):
        return self.f.subs(x, value)

    def ffv(self, value):
        return self.ff.subs(x, value)



if __name__ == '__main__':
    G = DIFF(func=sys.argv[1])
    print(G.ff)
    print(G.fv(float(sys.argv[2])), G.ffv(float(sys.argv[2])))
