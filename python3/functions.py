#Closure
def lazy_sum(*a): 
    def sum(): 
        s = 0
        for i in a: 
            s += i
        return s
    return sum
#the function return a function
f = lazy_sum(1, 2, 3, 4)
print(f())
#lamba
c = lambda x : x * x
#equal  x * x
print(c(10))