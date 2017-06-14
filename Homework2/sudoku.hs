import Data.Map (Map)
import qualified Data.Map as Map
import Data.List

parseMatrix :: [Int] -> [[Int]]
parseMatrix list = [drop (9 * i) (take (9 * (i + 1)) list) | i <- [0..8]]

parseSection :: [Int] -> Map Int [(Int, Int)]
parseSection list = Map.fromList[(x, [(fromInteger (fst y `div` 9), fromInteger (fst y `mod` 9)) | y <- zip [0..] list, snd y == x]) | x <- [1..9]]

nextStep :: [[Int]] -> (Int, Int) -> (Int, Int)
nextStep matrix coord = if null valid
    then (0, -1)
    else head valid
        where valid = [(x, y) | x <- drop (fst coord) ([0..8] ++ [0..8]),
                                y <- drop (snd coord) ([0..8] ++ [0..8]), matrix!!x!!y == 0]

setMatrix :: [[Int]] -> (Int, Int) -> Int -> [[Int]]
setMatrix matrix coord value = take (fst coord) matrix ++ [column] ++ drop (fst coord + 1) matrix
                                where column = take (snd coord) (matrix!!(fst coord)) ++ [value] ++ drop (snd coord + 1) (matrix!!(fst coord))

isValid :: [[Int]] -> Map Int [(Int, Int)] -> (Int, Int) -> Int -> Bool
isValid matrix sections coord e = if all (==True) ([e /= matrix!!(fst coord)!!x | x <- [0..8]] ++ 
                                                   [e /= matrix!!y!!(snd coord) | y <- [0..8]])
    then any (==True) [case Map.lookup x sections of
        Just n -> if coord `elem` n
            then all (==True) [e /= matrix!!(fst x)!!(snd x) | x <- n]
            else False
        Nothing -> False | x <- [1..9]] 
    else False

sudokuRec :: [[Int]] -> Map Int [(Int, Int)] -> (Int, Int) -> (Bool, [[Int]])
sudokuRec matrix sections coord = if (0, -1) == next
    then (True, matrix)
    else if null valid
        then (False, matrix)
        else head valid
            where next = matrix `nextStep` coord
                  valid = filter (\x -> fst x) [sudokuRec (setMatrix matrix next e) sections next | e <- [1..9], isValid matrix sections next e]

flatten :: [[a]] -> [a]         
flatten xs = (\z n -> foldr (\x y -> foldr z y x) n xs) (:) []

squigglySudoku :: [Int] -> [Int] -> [Int]
squigglySudoku varList blkList
    | length varList /= 81 = error "given grid must be 81 integers (9x9)"
    | length blkList /= 81 = error "given grid must be 81 integers (9x9)"
    | otherwise = if fst result
    then flatten (snd result)
    else error "can't eval sudoku by given grid"
        where result = sudokuRec (parseMatrix varList) (parseSection blkList) (0,0)
        