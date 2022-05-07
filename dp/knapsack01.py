import numpy as np


def max_value(vals: np.ndarray, weights: np.ndarray, max_weight: int) -> int:
    '''
    Selects items with in max weight such that value is maximized.
    Solved using bottom up dp. 

    Args:
        vals: array of values, vals[i] indicating the value of the i-th item
        weights: array of weights, weights[i] indicating the weight of the i-th item
        max_weights: Max weight of the knapsack
    Returns: 
        Maximum value attainable in the weight contraint. 
    '''
    dp = np.zeros((len(vals)+1, max_weight+1), int)  
    # dp[i, j] : best val for items the first i items with j as maxweight  
    # 0 th item is no item, 0 weight is no knapsack. 
    dp[0, :] = dp[:, 0] = 0
    
    for i in range(1, len(vals) + 1):
        for w in range(1, max_weight + 1):
            if weights[i-1] > w:
                dp[i, w] = dp[i-1, w]
            else:
                dp[i, w] = max(dp[i-1, w-weights[i-1]] + vals[i-1], dp[i-1, w])

    print(dp)
    return dp[len(vals), max_weight]

if __name__ == '__main__':
    vals = np.array([5, 4, 7, 7], int)
    weights = np.array([5, 6, 8, 4], int)
    max_weight = 13
    print(max_value(vals, weights, max_weight))
