#sum = 0
#for x in range(11) : 
#    sum += x
#print(sum)
def my_abs(x):
    if not isinstance(x, (int, float)):
        return "input error"
    if x >= 0:
        return x
    else:
        return -x
print(my_abs('a'))