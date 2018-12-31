import Data.List
import Data.Char


data Expr = Val  Int
          | Add  Expr Expr
          | Mult Expr Expr
          | Div  Expr Expr
          | Sub  Expr Expr

exprEval :: Expr -> Int
exprEval (Val n)    = n
exprEval (Add x y)  = exprEval x + exprEval y
exprEval (Sub x y)  = exprEval x - exprEval y
exprEval (Mult x y) = exprEval x * exprEval y
exprEval (Div x y)  = exprEval x `div` exprEval y
exprEval _          = error "This is not a valid expression buddy"

rpnEval :: [String] -> [Int] -> Int
rpnEval string stack = case (string, stack) of
                          ([], [x]) -> x
                          ("+":restString, a:b:cs) -> rpnEval restString $ (a + b):cs
                          ("-":restString, a:b:cs) -> rpnEval restString $ (a - b):cs
                          ("*":restString, a:b:cs) -> rpnEval restString $ (a * b):cs
                          ("/":restString, a:b:cs) -> rpnEval restString $ (a `div` b):cs
                          ([x]:restString, stack)   -> rpnEval restString $ (digitToInt x):stack

