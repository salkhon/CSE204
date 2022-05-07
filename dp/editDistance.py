import numpy as np


def edit_dist(s: str, t: str) -> int:
    '''
    Computes the cost of transforming one string to another.
    Allows insertion, deletion, copying and substitution. 
    Each operation costs 1 unit, except copying which costs 0.
    Uses bottom up dp.

    Args:
        s: The string that needs to be transformed (source)
        t: The string to transform to (target)
    Returns: 
        The minimum number of allowed operation cost for the transformation. 
    '''
    INS = 0
    DEL = 1
    COP = 3
    SUB = 4

    dp = np.zeros((len(s)+1, len(t)+1), float)  # operations to transform s[0:i] to t[0:j]
    dp[0, 1:] = [i + 1 for i in range(len(t))]
    dp[1:, 0] = [i + 1 for i in range(len(s))]

    operations = np.zeros((len(s)+1, len(t)+1), float)
    operations[0, 1:] = INS
    operations[1:, 0] = DEL

    def do_min_oper(i: int, j: int) -> None:
        '''
        Does dp look back and does the minimum operation. Stores the operation in the operations list.
        Look back to find the cost after last step for s[:i] to t[:j] transformation. 

        If deletion is performed on the last character of s[:i], then the op count is 1 greater than the remaining 
        transformation to t[:j], which is the prevously solved subproblem s[:i-1] to t[:j].

        If insertion is performed on the last character of s[:i] to transform to t[:j], then as a subproblem 
        firstly s[:i] must be transformed to t[:j-1], then one more operation of insertion would solve the problem. 

        If substitution or copying is performed on the last step, then as a subproblem s[:i-1] needs to be
        transformed to t[:j-1], the last character needs to be copied or subbed as needed. 
        
        Args:
            i: row index
            j: col index
        Returns:
            None
        '''
        del_cost = dp[i-1][j] + 1 if i - 1 >= 0 else np.inf
        ins_cost = dp[i][j-1] + 1 if j - 1 >= 0 else np.inf
        copy_cost = dp[i-1][j-1] if i - 1 >= 0 and j - \
            1 >= 0 and s[i-1] == t[j-1] else np.inf
        sub_cost = dp[i-1][j-1] + 1 if i - 1 >= 0 and j - 1 >= 0 else np.inf

        min_cost = min(copy_cost, sub_cost, del_cost, ins_cost)

        if min_cost == copy_cost:
            dp[i, j] = copy_cost
            operations[i, j] = COP
        elif min_cost == sub_cost:
            dp[i, j] = sub_cost
            operations[i, j] = SUB
        elif min_cost == del_cost:
            dp[i, j] = del_cost
            operations[i, j] = DEL
        else:
            dp[i, j] = ins_cost
            operations[i, j] = INS

    def print_oper_traceback():
        '''
        Traces back from bottom right corner. 
        '''
        op_stack = []
        i = len(s)
        j = len(t)

        while i != 0 or j != 0:
            op_stack.append(operations[i, j])
            if operations[i, j] == INS:
                j -= 1
            elif operations[i, j] == DEL:
                i -= 1
            else:
                i -= 1
                j -= 1
        op_stack.reverse()

        ops = []
        for op in op_stack:
            if op == INS:
                ops.append('INS')
            elif op == DEL:
                ops.append('DEL')
            elif op == COP:
                ops.append('COP')
            elif op == SUB:
                ops.append('SUB')
            else:
                ops.append('ERR')

        print('operations:', ops)

    # looking back a char on s resembles deletion, a char on t is insertion. Looking back on both is a
    # copy is characters are equal, substitution if they are not.
    for i in range(1, len(s) + 1):
        for j in range(1, len(t) + 1):
            do_min_oper(i, j)

    print(dp)
    print_oper_traceback()

    return dp[len(s), len(t)]


if __name__ == "__main__":
    s = 'KITTEN'
    t = 'KNITTING'
    print('edit distance:', edit_dist(s, t))
