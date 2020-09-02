#!/usr/local/bin/python3
import sys

def minimize_lateness(ttimes, dtimes):
    """
    (min_lateness, schedule) is returned
    lateness is L(i) = finishTime(i) - dtimes(i) if finishTime(i) > dtimes(i)
    """

    index = list(range(len(dtimes)))
    index.sort(key = lambda i:dtimes[i])

    min_lateness = 0
    start_time = 0
    for i in index:
        min_lateness = max(min_lateness, (ttimes[i] + start_time) - dtimes[i])
        start_time += ttimes[i]
    return min_lateness, index

while True:
    n = (int)(sys.stdin.readline())
    if n == -999:
        sys.exit()
    ttimes = (str)(sys.stdin.readline()).split()
    ttimes = [int(i) for i in ttimes]
    dtimes = (str)(sys.stdin.readline()).split()
    dtimes = [int(i) for i in dtimes]

    min_lateness, schedule = minimize_lateness(ttimes, dtimes)
    print(min_lateness)
    print(schedule)
