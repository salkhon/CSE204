import numpy as np

# non contiguous allowed


def longest_common_sub_seq(a: str, b: str) -> str:
    '''
    A = zyxwxwzy, B = wxyxzz, LCS = yxz. (or, wxy, wxz)
    Similar to edit distance. 

    For i, j: we can add a[i] and b[j] to the lcs (subproblem) of a[:i-1], b[:j-1]
    if a[i] == b[j].
    otherwise, the longest lcs between a[:i-1], b[:j] and a[:i], b[:j-1] is the lcs of a[:i], b[:j], 
    because the unequal characters don't contribute at this stage for a[:i], b[:j].

    Args:
        s: First string
        t: Second string

    Returns: 
        Longest common (not necessarily contiguous) sub sequence.
    '''
    dp = np.array([['' for j in range(len(b) + 1)]
                   for i in range(len(a) + 1)], dtype=object)

    for i in range(1, len(a) + 1):
        for j in range(1, len(b) + 1):
            if a[i-1] == b[j-1]:
                dp[i, j] = dp[i-1, j-1] + a[i-1]
            elif len(dp[i-1, j]) > len(dp[i, j-1]):
                dp[i, j] = dp[i-1, j]
            else:
                dp[i, j] = dp[i, j-1]
    
    print(dp)
    return dp[len(a), len(b)]


if __name__ == '__main__':
    a = 'gesture'
    b = 'essential'
    print(longest_common_sub_seq(a, b))
