#!/bin/python

import sys

def super_reduced_string(s):
    # Complete this function
    length = len(s)
    i = 0
    while i < length-1:
        curr = s[i]
        nxt = s[i+1]
        if curr == nxt:
            s = s[:i] + s[i+2:]
            length = len(s)
            i = 0
            continue
        i=i+1
    if len(s) == 0:
        return "Empty String"
    return s

s = raw_input().strip()
result = super_reduced_string(s)
print(result)
