import time
class Student(object): 
    def __init__(self, name, score): 
        self.__name = name  #use '__' to make class privte and it can only be used by using class function 
        self.__score = score
    def print_score(self): 
        print("%s : %s" % (self.__name, self.__score))
    def get_name(self):
        return self.__name
    def set_name(self, NewName):
        self.__name = NewName
b = Student('egan',99)
print(b.get_name())
b.set_name('Egan')
print(b.get_name())
