import Data.Map (Map)
import qualified Data.Map as Map
import Data.List

varList = [0,0,3,0,0,0,2,0,5,0,0,0,9,0,5,0,0,7,5,8,0,3,0,9,0,1,4,0,0,1,0,0,4,0,0,0,9,0,0,5,1,2,0,0,3,0,0,0,7,0,0,9,0,0,7,5,0,2,0,1,0,6,9,3,0,0,6,0,7,0,0,0,1,0,6,0,0,0,8,0,0]
blkList = [1,1,2,2,2,3,3,3,3,1,1,2,1,2,2,2,3,3,1,1,1,1,5,2,2,3,3,4,4,4,4,5,5,6,6,3,4,4,4,5,5,5,6,6,6,7,4,4,5,5,6,6,6,6,7,7,8,8,5,9,9,9,9,7,7,8,8,8,9,8,9,9,7,7,7,7,8,8,8,9,9]

parseMatrix :: [Int] -> [[Int]]
parseMatrix list = [drop (9 * i) (take (9 * (i + 1)) list) | i <- [0..8]]

parseSection :: [Int] -> Map Int [(Int, Int)]
parseSection list = Map.fromList[(x, [(fromInteger (fst y `div` 9), fromInteger (fst y `mod` 9)) | y <- zip [0..] blkList, snd y == x]) | x <- [1..9]]

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
                                            where 
                                                next = matrix `nextStep` coord
                                                valid = filter (\x -> fst x) [sudokuRec (setMatrix matrix next e) sections next | e <- [1..9], isValid matrix sections next e]

squigglySudoku :: [Int] -> [Int] -> [[Int]]
squigglySudoku varList blkList = snd (sudokuRec (parseMatrix varList) (parseSection blkList) (0,0))
