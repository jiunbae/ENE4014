prime :: Int -> Bool
prime n = [x | x <- [1..n], n `mod` x == 0] == [1, n]

findingPrimes :: Int -> Int -> [Int]
findingPrimes n m
    | m < 0     = error "Can't find M primes where m < 0"
    | n < 0     = take m [x | x <- [0..], prime x]
    | otherwise = take m [x | x <- [n..], prime x]