import numpy as np
import time
import sys

sys.setrecursionlimit(2000)

def dfsRec(current_x = None, current_y = None, visited = None):
    visited.append((current_x, current_y))
    element = matrix[current_y, current_x]
    if element == 1: # found
        return current_x, current_y

    if current_x < 0 or current_x >= matrix.shape[0] \
            or current_y < 0 or current_y >= matrix.shape[1]:
        return

    for n in range(current_x - 1, current_x + 2):
        for m in range(current_y - 1, current_y + 2):
            if not (n == current_x and m == current_y) \
                    and n > -1 and m > -1 \
                    and n < matrix.shape[0] and m < matrix.shape[1] \
                    and (n, m) not in visited:
                return dfsRec(n, m, visited)

def dfsRec1(x = None, y = None, visited = None):
    if x < 0 or x >= matrix.shape[0] \
            or y < 0 or y >= matrix.shape[1] \
            or (x, y) in visited:
        return

    visited.append((x, y))
    if matrix[y, x] == 1:
        print("found")
        print("(x, y): ", x, y)
        return

    dfsRec1(x, y + 1, visited)
    dfsRec1(x, y - 1, visited)
    dfsRec1(x + 1, y, visited)
    dfsRec1(x - 1, y, visited)
    

def dfsRec2(x = None, y = None, visited = None):
    if x < 0 or x >= matrix.shape[0] \
        or y < 0 or y >= matrix.shape[1] \
            or (x, y) in visited:
        return

    if matrix[y, x] == 1:
        return (x, y)

    return dfsRec2(x, y + 1, visited) 
    # if a == None:
    #     print("not found")
    #     return
        # b = dfsRec2(x, y - 1, visited)
        # if b == None:
        #     c = dfsRec2(x + 1, y, visited)
        #     if c == None:
        #         return dfsRec2(x - 1, y, visited)

# Create Matrix of size n
n = 15
matrix = np.zeros((n,n))

# 1. Generate a target Point at Random X and Y coordinates
x = np.random.randint(n)
y = np.random.randint(n)
matrix[y, x] = 1

# 2. We are going to start at zero zero 
start_x, start_y = np.random.randint(n), np.random.randint(n)

visited = []
DFSstart = time.time()
dfs_results = dfsRec(start_x, start_y, visited)
DFSend = time.time()

visited.clear()
DFSstart = time.time()
dfsRec1(start_x, start_y, visited)
DFSend = time.time()

visited.clear()
DFSstart = time.time()
res2 = dfsRec2(start_x, start_y, visited)
DFSend = time.time()

def dfs():
    element = None
    for n in range(matrix.shape[0]):
        for m in range(matrix.shape[0]):
            element = matrix[m, n]
            if element == 1:
                return n, m

# Print out the statements
print(matrix)
print("Starting X: ",start_x," Starting Y: ",start_y)
print("Solution by DFS: ", dfs_results, " Execution Time : ", DFSend-DFSstart)
print("Solution by DFS: ", res2, " Execution Time : ", DFSend-DFSstart)
print("Solution by dfs_result1.", " Execution Time : ", DFSend-DFSstart)
