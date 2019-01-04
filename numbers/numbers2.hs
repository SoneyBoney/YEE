module Numbers where

import Data.List
import Data.Char



data Expr = Num  Int | Op Ops Expr Expr


data Ops = Add
         | Sub
         | Mult
         | Div

instance Eq (Expr) where
    (Num a) == (Num b) = (a == b)

instance Show Ops where
    show Add = "+"
    show Sub = "-"
    show Mult = "*"
    show Div = "/"

instance Show Expr where
    show (Num n)       = show n
    show (Op oper a b) = (l_brac a) ++ (show oper) ++ (r_brac b)
                       where l_brac x = "(" ++ show x
                             r_brac x = show x ++ ")"

evalOp :: Ops -> Int -> Int -> [Int]
evalOp Add x y  = [x + y]
evalOp Sub x y  = [x - y]
evalOp Mult x y = [x * y]
evalOp Div x y  | y == 0 = []
                | otherwise = [x `div` y]

evalExpr :: Expr -> [Int]
evalExpr (Num n) = [n]
evalExpr (Op Div _ (Num 0)) = []
evalExpr (Op oper x y) = concat [evalOp oper a b| a <- evalExpr x, b <- evalExpr y]

checkDive :: Expr -> Bool
checkDive (Op Div _ y) = if y == (Num 0) then False else True


ops :: [Ops]
ops = [Add, Sub, Mult, Div]

exprGen :: [Int] -> [Expr]
exprGen [] = []
exprGen [x] = [Num x]
exprGen numbers = [x
                   | (a,b) <- cleave numbers
                   , a' <- exprGen a
                   , b' <- exprGen b
                   , x <- merge a' b']


merge :: Expr -> Expr -> [Expr]
merge operand1 operand2 = [Op operation operand1 operand2 | operation <- ops] 

cleave :: [Int] -> [([Int],[Int])]
cleave [] = []
cleave (x:xs) = ([x],xs) : [(x:y, ys) | (y,ys) <- cleave xs]

powerSet :: [Int] -> [[Int]]
powerSet [] = [[]]
powerSet (x:xs) = [x:y | y <- powerSet xs] ++ powerSet xs

solve :: Int -> [Int] -> [Expr]
solve target options = [b | a <- allNums, b <- exprGen a, evalExpr b == [target]]
                     where allNums = concatMap permutations $ powerSet options


main :: IO()
main = print (solve 100 [50,40])
