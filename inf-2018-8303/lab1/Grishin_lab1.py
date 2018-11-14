def zero(list):
    sort = '' 
    for i in list:
        try:
            buf = int(i)
            sort += str(buf) + ' ' 
        except ValueError:
            continue
    print(sort)
 

def first(list):
    res = 0
    for i in list:
        try:
            buf = int(i) 
            if buf % 2 == 0:
                res += buf
        except ValueError:
            continue
    print(res)
 

def second(list):
    sort = '' 
    for i in list:
        if len(i) <= 3:
            sort += i
    print(sort)


def third(list):
    res = 1
    for i in list:
        try:
            buf = int(i)
            if buf % 2 == 1:
                res *= buf
        except ValueError:
            continue
    print(res)
 

def fourth(list):
    sort = '' 
    for i in list:
        buf = i[5::5]
        try:
            buf = int(buf)
            continue
        except ValueError:
            if buf != '':
                sort += buf + ' ' 
    print(sort)

    
def fifth(list):	
    for ind, elem in enumerate(list):
        print(ind, elem)

        
def menu(enter, op):
    if op == '0':
        zero(enter) 
    elif op == '1':
        first(enter) 
    elif op == '2':
        second(enter)
    elif op == '3':
        third(enter)
    elif op == '4':
        fourth(enter)
    elif op == '5':
        fifth(enter)
    else:
        print(' '.join(enter)) 


enter = []
for i in range(0,10,1):
    enter.append(input())
op = input()
menu(enter, op)
