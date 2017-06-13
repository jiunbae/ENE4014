from collections import defaultdict

def findNextCellToFill(grid, i, j):
    for x in (list(range(9))*2)[i:i+9]:
        for y in (list(range(9))*2)[j:j+9]:
            if grid[x][y] == 0:
                return x,y
    return -1, -1

def isValid(grid, blk, i, j, e):
    if all([e != grid[i][x] for x in range(9)]):
        if all([e != grid[x][j] for x in range(9)]):
            for b, values in blk.items():
                if (i,j) in values:
                    for x, y in blk[b]:
                        if grid[x][y] == e:
                            return False
                    break
            return True
    return False

def solveSudoku(grid, blk, i=0, j=0):
    i, j = findNextCellToFill(grid, i, j)
    if i == -1:
        return True
    for e in range(1, 10):
        if isValid(grid, blk, i, j, e):
            grid[i][j] = e
            if solveSudoku(grid, blk, i, j):
                return True
            grid[i][j] = 0
    return False

varList = [0,0,3,0,0,0,2,0,5,0,0,0,9,0,5,0,0,7,5,8,0,3,0,9,0,1,4,0,0,1,0,0,4,0,0,0,9,0,0,5,1,2,0,0,3,0,0,0,7,0,0,9,0,0,7,5,0,2,0,1,0,6,9,3,0,0,6,0,7,0,0,0,1,0,6,0,0,0,8,0,0]
blkList = [1,1,2,2,2,3,3,3,3,1,1,2,1,2,2,2,3,3,1,1,1,1,5,2,2,3,3,4,4,4,4,5,5,6,6,3,4,4,4,5,5,5,6,6,6,7,4,4,5,5,6,6,6,6,7,7,8,8,5,9,9,9,9,7,7,8,8,8,9,8,9,9,7,7,7,7,8,8,8,9,9]

def _parse_matrix_(array):
    return [array[i*9:(i+1)*9] for i in range(9)]
def _parse_section_(array):
    sections = defaultdict(list)
    for idx, value in enumerate(array):
        sections[value].append((int(idx/9), idx%9))
    return sections

varlist = _parse_matrix_(varList)
blklist = _parse_section_(blkList)

if __name__ == '__main__':
    print (solveSudoku(varlist, blklist))
    for v in varlist:
        print (v)