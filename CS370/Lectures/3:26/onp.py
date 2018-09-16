operators = ["+", "-", "*", "/", "^"]
precedence = {"+":0, "-":1, "*":2, "/":3, "^":4}
letter = 'abcdefghijklmnopqrstuvwxyz'

def check(o1, o2):
    if precedence[o1] >= precedence[o2]:
        return True
    else:
        return False


def main():
    t = int(raw_input())
    if t > 100:
        print('error: too many expressions')
    for i in range(t):
        exp = raw_input()
        if len(exp) > 400:
            print('error: expression is too long')
        stack = []
        res = ''
        for e in exp:
            if e == "(":
                stack.append(e)
            elif e in letter:
                res += e
            elif e in operators:
                while stack[-1] in operators:
                    if check(stack[-1], e):
                        res += stack.pop()
                stack.append(e)
            elif e == ")":
                while not stack[-1] == "(":
                    res += stack.pop()
                stack.pop()
        while not len(stack) == 0:
            if stack[-1] == "(":
                stack.pop()
            else:
                res += stack.pop()
        print(res)

main()
