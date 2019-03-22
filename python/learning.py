import random
def spam(divideBy): 
    try:
        return 42 / divideBy
    #test if the code is wrong 
    except: 
    #hopefully to give some imformation about error
    #and then continue the progress
        print("error")

lista = ['i', '2', '3']
print(lista[0:3])
#it means a slit form 0 to the lenth of 3
del(lista[0])
#delete the first element
print(lista[0:3])

