# Knight's Tour using Warnsdorff's Rule
# http://en.wikipedia.org/wiki/Knight's_tour
 
# height and width of the chessboard
height = 8
width = 8
 
cb = [[0 for x in xrange(height)] for y in xrange(width)] # chessboard
 
# possible direction combinations for knight
dx = [-2, -1, 1, 2, -2, -1, 1, 2]
dy = [1, 2, 2, 1, -1, -2, -2, -1]
 
# start the Knight randomly on board
kx = random.randint(0, width - 1)
ky = random.randint(0, height - 1)
 
for k in xrange(width * height):
    cb[ky][kx] = k + 1
    p_queue = [] # available neighbors queue
    for i in xrange(8):
        nx = kx + dx[i]; ny = ky + dy[i]
        if nx >= 0 and nx < width and ny >= 0 and ny < height:
            if cb[ny][nx] == 0:
                # count the available neighbors of the potential next stops
                ctr = 0
                for j in xrange(8):
                    ex = nx + dx[j]
                    ey = ny + dy[j]
                    if ex >= 0 and ex < width and ey >= 0 and ey < height:
                        if cb[ey][ex] == 0:
                            ctr += 1
                heappush(p_queue, (ctr, i))
    # move to the neighbor that has min number of available neighbors
    if len(p_queue) > 0:
        (p, m) = heappop(p_queue)
        kx += dx[m]
        ky += dy[m]
    else: break
 
# print cb
for cy in xrange(height):
    for cx in xrange(width):
        print string.rjust(str(cb[cy][cx]), 2),
    print