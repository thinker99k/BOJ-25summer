pascal = [
    [0],
    [1, 1],
    [1, 2, 1],
    [1, 3, 3, 1],
    [1, 4, 6, 4, 1],
]

nr = input().split()
n = int(nr[0])
r = int(nr[1])

for i in range(5, n + 1):
    newList = [1]

    for j in range(1, i):
        newList.append(pascal[i-1][j-1] + pascal[i-1][j])

    newList.append(1)

    pascal.append(newList)

print(pascal[n][r])
