def Triangle():
#generetor function
    l = [1]
    while True:
        yield l      
        l = [1] + [l[i] + l[i + 1] for i in range(len(l) - 1)] + [1]

n = 0
for t in Triangle():
    print(t)
    n += 1
    if n == 10: 
        break

