def fac(n):
    min = 1
    for i in n: 
        if i > max: 
            max = i
        if i < min: 
            min = i
    return min, max
d = {'a':'A', 'b':'B', 'c':'C'}
print([k + '=' + v for k, v in d.items()])
lista = [x * x for x in range(1, 11)]
l = (x * x for x in range(1, 11))
for n in l: 
    print(n) 
print(fac(*lista))
d = {'Egan' : 18, 'Mchal' : 81}#dic
if 'Egan' in d :
    print('yes')
if d.get('Egana', 0) == 0 :#.get(aim, claim the return vable when it isn't exsit)
    print('no')
print(d['Egan'])
print(list(range(100)))
a_tuple = ('a', 'c', 't')
print(list(a_tuple))
a = "I love you"
print(a[1:4:2])
#[star:end:step]
print(a.split(' '))
#every time meet ' ', it cut the str
print(','.join(a.split(' ')))
#let the split join to a conpleted str
