import sys
import math

k,w = map(int,input().split())
li = int((w-1)/k)+1 #总位数
f = [[0 for i in range((1<<k)+5)] for i in range(li+5)] #初始化dp数组

for j in range(0,1<<k):
    f[0][j]=(1<<k)-j

for i in range(1,li): #DP
    for j in range(0,1<<k):
        j=(1<<k)-j-1
        f[i][j]=f[i][j+1]+f[i-1][j+1]

ans=0
for i in range(1,li):
    ans+=f[i][1]
rest=w-k*(li-1)
ans-=f[li-1][1<<rest]
print(ans)