#!/usr/local/bin/python3
#-*- coding: utf-8 -*-

class Solution:
    def findMin(self, num):
        begin, end = 0, len(num) - 1
        while begin + 1 < end:
            mid = (begin + end) // 2
            if (num[begin] < num[mid]):
                begin = mid
            elif (num[begin] > num[mid]):
                end = mid
            else:
                break
        return min(num[begin], num[end], num[0])
