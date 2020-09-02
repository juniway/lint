#!/usr/local/bin/python3
import sys

def interval_scheduling(stimes, ftimes):
    index = list(range(len(stimes)))
    print(index)
    index.sort(key=lambda i : ftimes[i])

    max_set = set()
    prev_finish_time = 0
    for i in index:
        if stimes[i] >= prev_finish_time:
            max_set.add(i)
            prev_finish_time = ftimes[i]

    return max_set

# n = int(input('Enter number of activities: '))
# stimes = input('Enter the start time of the {} activities in order: '.format(n)).split()
# stimes = [int(st) for st in stimes]
# ftimes = input('Enter the finish times of the {} activities in order: '.format(n)).split()
# ftimes = [int(ft) for ft in ftimes]

while True:
    n = int(sys.stdin.readline())
    if n == -999:
        sys.exit()
    stimes = str(sys.stdin.readline())
    stimes = [int(i) for i in stimes.split()]
    ftimes = str(sys.stdin.readline())
    ftimes = [int(i) for i in ftimes.split()]

    ans = interval_scheduling(stimes, ftimes)
    print('A maximum-size subset of activities that are mutually compatible is', ans)
