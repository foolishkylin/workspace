from functools import reduce
DIGITS = {'0': 0, '1': 1, '2': 2, '3': 3, '4': 4, '5': 5, '6': 6, '7': 7, '8': 8, '9': 9}
#########################################
#map and reduce
def abs(a): 
    if a < 0: 
        a *= -1
    return a
def poud(x, y):
    return x * y
b = list(map(abs, [1, -2, 3, 4, 5, -6, 7, 8, -9]))
#run function abs to every element of the list
c = reduce(poud, [1, -2, 3, 4, 5, -6, 7, 8, -9])
#run function add and store the result, which will run in function as a element with another element in list
print(b)
print(c)  
#################################################
#conbination
def str2int(s): 
#let the str date become interger type
    def fn(x, y): 
        return x * 10 + y
    def char2num(s): 
        return DIGITS[s]
    return reduce(fn, map(char2num, s))
print(str2int("123"))
def str2float(s):
    def fn1(x, y):
        return x * 10 + y
    def fn2(x, y):
        pass
###################################################
'''

'''
def odd_iter(): 
    n = 1
    while True: 
        n += 2
        yield n
def isdivisible(n): 
    return lambda x : x % n >= 0
def prism(): 
    yield 2
    it = odd_iter()
    while True: 
        n = next(it)
        yield n
        it = filter(isdivisible(n), it)
for n in prism():
    if n >= 1000: 
        break
    print(n)
######################################
def issame(n): 
    n = str(n)
    for i in range(0, len(n)//2): 
        if n[i] != n[len(n) - i - 1]: 
            return False
    return True
print(1)
#list(filter(issame(n), range(1000000))