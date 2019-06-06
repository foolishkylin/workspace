import numpy as np


def normalized(x, y):
    x = (x - x.min()) / (x.max() - x.min())
    y = (y - y.min()) / (y.max() - y.min())

    return x, y
