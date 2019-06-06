import pandas as pd
import numpy as np


def liner_data():
    data = pd.read_csv('Salary_Data.csv').values
    x, y = np.hsplit(data, 2)
    return x, y
