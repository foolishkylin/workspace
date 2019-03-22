# CalPi-MK
from random import random
DARTS = 1000 * 1000
hits = 0.0
for i in range(1, DARTS):
    x, y = random(), random()
    if x ** 2 + y ** 2 <= 1.0:
        hits += 1
Pi = 4 * (hits/DARTS)
print("pi = : {}".format(Pi))
