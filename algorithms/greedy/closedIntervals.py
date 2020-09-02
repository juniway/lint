#!/usr/local/bin/python3
import sys

def smallest_unit_length_intervals(points):
    points.sort()
    smallest_set = set()
    end_of_last_interval = float('-inf')
    for p in points:
        if end_of_last_interval <= p:
            interval = (p, p + 1)
            smallest_set.add(interval)
            end_of_last_interval = p + 1
    return smallest_set

points = (str)(sys.stdin.readline()).split()
points = [float(i) for i in points]

ans = smallest_unit_length_intervals(points)
print(ans)
