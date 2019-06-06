import dataset
import pretreat
import matplotlib.pyplot as plt


def cost_func(x, y, theta):
    m = len(x)
    error = ((theta[0] + theta[1] * x - y) ** 2).sum()
    cost = error / (2 * m)
    return cost


def gradient_descent(x, y, alpha=0.01, eps=1e-4, max_lte=1e4):
    theta = [0, 0]
    cost_list = []
    m = len(x)
    cost = cost_func(x, y, theta)
    lte = 0
    while cost >= eps and lte <= max_lte:
        dev = [0, 0]
        dev[0] = (theta[0] + theta[1] * x - y).sum()
        dev[1] = ((theta[0] + theta[1] * x - y) * x).sum()
        theta[0] -= alpha * dev[0] / m
        theta[1] -= alpha * dev[1] / m
        cost = cost_func(x, y, theta)
        cost_list.append(cost)
        print(cost)
        lte += 1
    return theta, cost_list


def grad_des_test():
    x, y = dataset.liner_data()
    x, y = pretreat.normalized(x, y)
    theta, cost_list = gradient_descent(x, y)
    predict_y = x * theta[1] + theta[0]

    plt.plot([x for x in range(10001)], cost_list)
    plt.show()

    plt.plot(x, y, c='red', label='raw data')
    plt.plot(x, predict_y, c='green', label='predict line')
    plt.xlabel('data')
    plt.ylabel('salary')
    plt.legend()  # show the labels
    plt.show()


if __name__ == '__main__':
    grad_des_test()