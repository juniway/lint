#!/usr/local/bin/python3
#-*- coding: utf8 -*-

def isValid(cutLen, arr, k):
    count = 0;
    for wood in arr:
        if (wood >= cutLen):
            count += wood // cutLen;
    return count >= k

def cutWoods(arr, k):
    left, right = 1, max(arr)
    res = 0
    while (left + 1 < right):
        mid = (left + right) // 2
        if(isValid(mid, arr, k)):
           res = mid
           left = mid + 1
        else:
           right - mid
    return res
