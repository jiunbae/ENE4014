factors n = [x | x <- [1..n], n `mod` x == 0]
prime n = factors n == [1, n]
findingPrimes n m = take m [x | x <- [n..], prime x]