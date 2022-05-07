def fib(n: int) -> int:
    '''
    Returns the n-th fib number, starting from n = 0. Uses Memoization. 
    Args:
        n: The sequence of the fibonacci number to return.
    Returns: 
        The n-th fibnacci number. 
    '''
    dp = [0 for _ in range(n+1)]
    dp[1] = 1

    def fib_helper(i: int) -> int:
        if dp[i] or i <= 1:
            return dp[i]

        dp[i] = fib_helper(i - 1) + fib_helper(i - 2)
        return dp[i]
    
    return fib_helper(n)

 
if __name__ == '__main__':
    print(fib(20))
    print(fib(44))
    print(fib(100))
