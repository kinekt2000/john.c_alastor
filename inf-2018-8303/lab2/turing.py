memory = list(input())

state = 'p0'
i = 0
while state != 'p11':
    if state == 'p0':
        if memory[i] == '0' or memory[i] == '1' or memory[i] == '2' or memory[i] == '+' or memory[i] == '-':
            i += 1
            state = 'p1'
        elif memory[i] == ' ':
            i += 1

    elif state == 'p1':
        if memory[i] == '0' or memory[i] == '1' or memory[i] == '2':
            i += 1
        elif memory[i] == '+':
            state = 'p+'
            i += 1
        elif memory[i] == '-':
            state = 'p-'
            i +=1

    elif state == 'p+':
        if memory[i] == '0' or memory[i] == ' ':
            state = 'p8'
        elif memory[i] == '1':
            state = 'p3'
            i -= 1
        elif memory[i] == '2':
            state = 'p4'
            i -= 1

    elif state == 'p3':
        if memory[i] == '+':
            i -= 1
        elif memory[i] == '0' or memory[i] == '1':
            state = 'p8'
            memory[i] = str(int(memory[i]) + 1)
        elif memory[i] == '2':
            memory[i] = '0'
            i -= 1
        elif memory[i] == ' ':
            state = 'p8'
            memory[i] = '1'

    elif state == 'p4':
        if memory[i] == '+':
            i -= 1
        elif memory[i] == '1' or memory[i] == '2':
            state = 'p3'
            memory[i] = str(int(memory[i]) - 1)
            i -= 1
        elif memory[i] == '0':
            state = 'p8'
            memory[i] = '2'
        elif memory[i] == ' ':
            state = 'p8'
            memory[i] = '2'

    elif state == 'p-':
        if memory[i] == '0' or memory[i] == ' ':
            state = 'p8'
        elif memory[i] == '1':
            state = 'p6'
            i -= 1
        elif memory[i] == '2':
            state = 'p7'
            i -= 1

    elif state == 'p6':
        if memory[i] == '1' or memory[i] == '2':
            state = 'p8'
            memory[i] = str(int(memory[i]) - 1)
        elif memory[i] == '0':
            memory[i] = '2'
            i -= 1
        elif memory[i] == '-':
            i -= 1

    elif state == 'p7':
        if memory[i] == '0' or memory[i] == '1':
            state = 'p6'
            memory[i] = str(int(memory[i]) + 1)
            i -= 1
        elif memory[i] == '2':
            memory[i] = '0'
            state ='p8'
        elif memory[i] == '-':
            i -= 1
    
    elif state == 'p8':
        if memory[i] == '0' or memory[i] == '1' or memory[i] == '2':
            i -= 1
        elif memory[i] == ' ':
            state = 'p9'
            i += 1

    elif state == 'p9':
        if memory[i] == '1' or memory[i] == '2':
            state = 'p11'
        elif memory[i] == '0':
            memory[i] = ' '
            i += 1
        elif memory[i] == '+' or memory[i] == '-':
            state = 'p10'
            i -= 1
    
    elif state == 'p10':
        if memory[i] == '0' or memory[i] == '1' or memory[i] == '2':
            state = 'p11'
        if memory[i] == ' ':
            state = 'p11'
            memory[i] = '0'

print(''.join(memory))
