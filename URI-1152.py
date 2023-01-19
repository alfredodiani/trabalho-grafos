# 1152 - Dark Roads
# Challenge Link: https://www.beecrowd.com.br/judge/en/problems/view/1152
# Score: Accepted
# Alfredo Diani

def maximum_daily_amount(n, m, edges):
    total = sum(edge[2] for edge in edges)
    fa = list(range(n))
    edges.sort(key=lambda edge: edge[2])
    ans = 0
    save = 0
    for x, y, z in edges:
        x = find(x, fa)
        y = find(y, fa)
        if x != y:
            fa[x] = y
            ans += 1
            save += z
            if ans == n - 1:
                break
    return total - save

def find(x, fa):
    if fa[x] == x:
        return x
    fa[x] = find(fa[x], fa)
    return fa[x]

while True:
    n, m = list(map(int, input().split()))
    if n == 0 and m == 0:
        break
    edges = [list(map(int, input().split())) for _ in range(m)]
    print(maximum_daily_amount(n, m, edges))
