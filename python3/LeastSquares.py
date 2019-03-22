#input same dot(x, y), output the line which is most true
import os
a = [0, 0, 0]
b = [0, 0, 0]
while True :
    x, y = map(float, input("please enter x and y: ").split())
    if x == 404 : 
        break
    a[0] += 1
    a[1] += x
    a[2] += y
    b[0] += x
    b[1] += x * x
    b[2] += x * y

k = b[0] / a[0]
for i in range(3) :
    a[i] *= k
A = (a[2] - b[2]) / (a[1] - b[1])
B = (b[2] - b[1] * A) / b[0] 

print('Y = %.2f X + %.2f' % (A, B))
os.system("pause")
