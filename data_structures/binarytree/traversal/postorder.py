#!/usr/local/bin/python3

# BFS: iterative
def postorder(self, root):
    if not root: return []
    stack = [root]
    out = []
    # ret, stack = [], root and [root]
    while len(stack):
        top = stack.pop()
        out.append(top.val)
        stack.extend(top.children or [])
    return out[::-1]
