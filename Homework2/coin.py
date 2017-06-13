
def flipStack(n, coins):
    count = len(coins) - n
    return coins[:count] + list(reversed(map(lambda x: not x, coins[count:])))

def flipRec(coins):
    if all(coins):
        return [0]
    else:
        count = 1 if coins[-1] else len(coins) - coins.index(False)
        return [count] + flipRec(flipStack(count, coins))

def flipCoin(coins):
    return flipRec(list(reversed(map(lambda x: x=='H', coins))))