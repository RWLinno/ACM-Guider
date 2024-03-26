from sys import *
setrecursionlimit(100000)
def gcd(x,y):
    if y==0:
        return x
    else:
        return gcd(y,x%y)

a=int(input())
b=int(input())

print(gcd(a,b))