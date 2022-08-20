"""
 Conway's Game of Life

- 2 dimensional matrix
- Cells with two states: dead or alive
- Determine the next generation of the matrix given a couple of rules and the current generation
    - Live cells stay alive if they have exactly 2 or 3 alive neighbors in the previous generation. Otherwise they die of loneliness (<2) or overcrowding (>3)
    - Dead cells stay dead unless they have exactly 3 alive neighbors in the previous generation.
- Diagonals count as neighbors
- Any number of rows and columns (except 0)
- May create any custom classes, functions, utilities, etc. that are helpful along the way


- write a function that takes input generation and produces output generation
- write in a testable way
- be able to print the matrix

Example grids
---------------------
D D D D D      X X X X X
D A A A D  ->  X X X X X
D D D D D      X X X X X
"""
## neighbors (r,c-1), (r-1,c-1) , (r+1, c-1), (r-1,c) , (r-1,c+1), 
# (r,c+1), (r+1,c+1), 
# (r+1,c)

def determineNextState(r,c, maxRows,maxCols, input ):
    deadOrAliveMap = {'D':0, 'A':0}
    if (c-1 > 0):
        curC = c -1
        deadOrAliveMap[input[r][curC]] += 1
        if (r-1 > 0):
            deadOrAliveMap[input[r-1][curC]] += 1
        if (r+1 < maxRows):
            deadOrAliveMap[input[r+1][curC]] += 1
    if (r-1 > 0):
        curRow = r-1 
        deadOrAliveMap[input[curRow][c]] += 1
        if (c+1 < maxCols):
            deadOrAliveMap[input[curRow][c+1]] += 1
    if (c+1 < maxCols):
        curC = c + 1
        deadOrAliveMap[input[r][curC]] += 1
        if (r+1 < maxRows):
            deadOrAliveMap[input[r+1][curC]] += 1
    if(r+1 < maxRows):
        deadOrAliveMap[input[r+1][c]] += 1
    alive = deadOrAliveMap['A']
    dead = deadOrAliveMap['D']
    if input[r][c] == 'A':
        if alive==2 or alive ==3:
            return 'A'
        if alive <2 or alive > 3:
            return 'D'
    if input[r][c] == 'D' and alive == 3:
        return 'A'
    return input[r][c]







def gameOfLifeGenetor (input):
    if not input:
        return None
    if len(input) == 1 and len(input[1]):
        return input
    numRows = len(input)
    numCols = len (input[1])
    expectedStateChanges = {}
    for rowIdx in range(numRows):
        for colIdx in range(numCols):
            newState = determineNextState(rowIdx,colIdx, numRows,numCols, input )
            if newState != input[rowIdx][colIdx]:
                expectedStateChanges[(rowIdx,colIdx)] = newState

    for key,val in expectedStateChanges.items():
        rowIdx = key[0]
        colIdx = key[1]
        input[rowIdx][colIdx] = val

    
    return input


def say_hello():
    print('Hello, World')

for i in range(5):
    say_hello()
