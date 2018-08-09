from enum import Enum


class Operation(Enum):
    """Operations"""

    DELETED = 1
    INSERTED = 2
    SUBSTITUTED = 3

    def __str__(self):
        return str(self.name.lower())


def distances(a, b):
    """Calculate edit distance from a to b"""

    operation = Operation
    c = 0
    # a = 'cats'
    # b = 'ate'
    length_a = len(a) + 1
    length_b = len(b) + 1

    matrix = [[(c, operation) for i in range(length_b)] for k in range(length_a)]

    for x in range(length_a):
        matrix[x][0] = c, Operation.DELETED
        c = c + 1
    c = 0
    for y in range(length_b):
        matrix[0][y] = c, operation.INSERTED
        c = c + 1
    matrix[0][0] = 0, None

    #find out cost of the ith row and jth column
    # In  base case  cost[i][j] = matrix[i][j][0]

    # new cost of ith row and jth column will be
    # cost[i][j] = min(deletion: cost[i][j + 1] + 1,
    #             insertion: cost[i-1][j] ,
    #              substitution: cost[i - 1][j - 1] if a[i] == b[j] ,
    #                          else: cost[i-1][j-1] + 1)

    for i in range(1,length_a):
        for j in range(1,length_b):
            if (a[i -1] == b[j - 1]):

                sub = matrix[i- 1][j-1][0]
            else:
                sub = matrix[i-1][j-1][0] + 1

            delet = matrix[i-1][j][0]
            insert = matrix[i][j-1][0]

            if (min(delet, insert, sub) == delet):
                oper = operation.DELETED
            elif (min(delet, insert, sub) == insert):
                oper = operation.INSERTED
            elif (min(delet, insert, sub) == sub):
                oper = operation.SUBSTITUTED

            matrix[i][j] =(min(delet + 1, insert + 1, sub)), oper

    return matrix

