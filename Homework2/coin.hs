import Data.List

flipStack :: Int -> [Bool] -> [Bool]
flipStack n xs = count `take` xs ++ reverse ((\x -> not x) `map` (drop count xs))
                    where count = length xs - n

flipRec :: [Bool] -> [Int]
flipRec coins
    | all (==True) coins = [0]
    | otherwise          = count : flipRec (count `flipStack` coins)
                            where count = if last coins
                                    then 1 
                                    else case (False `elemIndex` coins) of
                                        Just n -> length coins - n
                                        Nothing -> 0

flipCoin :: [Char] -> [Int]
flipCoin coins
    | all (==True) ((\x -> x=='H' || x=='T') `map` coins) = flipRec (reverse ((\x -> x == 'H') `map` coins))
    | otherwise                                           = error "Input must be H or T"
