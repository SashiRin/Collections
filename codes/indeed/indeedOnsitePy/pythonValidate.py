def start_from_here():
    line1 = "def start_from_here():"
    line2 = "\tfor i in range(0,3):"
    line3 = "\t\tif i > 1:"
    line4 = "\t\t\tprint(i)"
    line41 = "\t\t\tprint(i)"
    line42 = "\t\tprint(i)"
    line5 = "\tprint(\"Hello\")"
    line6 = "print(\"aha\")"
    line7 = "if i == 1:"
    codelines = [line1, line2, line3, line4, line41, line42, line5, line6, line7]
    print(validate(codelines))


def count_tab_num(line):
    cnt = 0
    for c in line:
        if c == "\t":
            cnt += 1
        else:
            break
    print("cnt " + str(cnt))
    return cnt


def validate(codelines):
    if len(codelines) == 0:
        return True
    stack = [0]
    control_state_line = False
    for line in codelines:
        tab_num = stack[-1]
        actual_tab_num = count_tab_num(line)
        if tab_num < actual_tab_num or (control_state_line and tab_num != actual_tab_num):
            return False
        if not control_state_line and tab_num > actual_tab_num:
            times = tab_num - actual_tab_num
            while times > 0:
                stack.pop()
                times -= 1
        if control_state_line and tab_num == actual_tab_num:
            control_state_line = False
        if line[-1] == ':':
            control_state_line = True
            stack.append(stack[-1] + 1)
    if stack[-1] == 0:
        return True
    else:
        return False

start_from_here()