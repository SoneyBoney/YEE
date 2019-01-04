module Monty where

import Data.List
import System.Random

data door = A | B | C

instance Show door where
	show A = show "|A|"
	show B = show "|B|"
	show C = show "|C|"





main :: IO()
main = do
	   g <- newStdGen