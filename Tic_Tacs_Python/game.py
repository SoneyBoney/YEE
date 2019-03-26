from random import randrange
from math import log, sqrt
from copy import deepcopy
import sys


class GameState:
	def __init__(self):
		self.move = 0
		k = 3
		self.board = [[-1 for _ in range (k)] for _ in range(k)]
		return

	#valid move function
	
	def PlayMove(self, move):
		if(self.ValidMove(move)):
			player = (self.move % 2) + 1
			move1 = move /3
			move2 = move % 3
			self.board[move1][move2] = player
			self.move += 1
			return
		else:
			print "error %d not valid move" % move
			return -1;

	def ValidMove(self, move):
		move1 = move // 3
		move2 = move % 3
		if(move > 8 or move < 0 or self.board[move1][move2] != -1):
			return False
		else:
			return True

	def FindValidMoves(self):
		moves = []
		k = 0
		while(k <= 8):
			i = k / 3
			j = k % 3
			if(self.board[i][j] == -1):
				moves.append(k)
			k+=1

		print "Valid moves", moves
		return moves

	def CheckWin(self):
		for rows in self.board:
			first, rest = rows[0], rows[1:]
			same = (j == first for j in rest)
			if(all(same) and first != -1):
				return first

		for column in range(3):
			first = self.board[0]
			same = (j[0] == first for j in self.board)
			if(all(same) and first != -1):
				return first

		if(self.board[0][0] == self.board[1][1] == self.board[2][2] != -1):
			return self.board[0][0]

		if(self.board[2][0] == self.board[1][1] == self.board[0][2] != -1):
			return self.board[1][1]

		return 0;

	def CheckTerminate(self):
		return self.CheckWin() or self.move > 8

	def Simulate(self, player):
		while(not self.CheckTerminate):
			moves = self.FindValidMoves()
			play = moves[randrange(len(moves))]
			self.PlayMove(play)
		winner = self.CheckWin()
		if(winner == 0):
			return 0
		if(player == winner):
			return 10
		else:
			return -10

	def ResetState(self):
		for i in range(3):
			for j in range(3):
				self.board[i][j] = -1
		self.move = 0
		return


	def PrintGame(self):
		for i in self.board:
			for j in i:
				if(j!= -1):
					print j,
				else:
					print "_",
			print "\n"
		return

class GameTree:
	def __init__(self, move = -1):
		self.move = move
		self.w_i = 0
		self.n_i = 0
		self.parent = None
		self.children = []
		return

	def AddChild(self, move):
		new_node = GameTree(move)
		new_node.parent = self
		self.children.append(new_node)
		return

	def ComputeUCB(self):
		if(self.n_i == 0):
			return sys.maxint
		else:
			return (self.w_i / self.n_i) + (sqrt(2.0 * (log(self.parent.n_i)/self.n_i)))

	def ComputeExpectation(self):
		return (self.w_i / self.n_i)



def TraverseUCB(root, game):
	while(root.children != [] and not game.CheckTerminate()):
		game.FindValidMoves()
		UCB_Child_Pair = {}
		for child in root.children:
			temp = child.ComputeUCB()
			UCB_Child_Pair[child] = temp

		root = max(UCB_Child_Pair.iterkeys(), key=lambda k: UCB_Child_Pair[k])
		#print "move", root.move
		#print "in traverse"
		game.PlayMove(root.move)


	return root

def AppendChildren(root, game):
	if(game.CheckTerminate() != 0):
		return root
	for move in game.FindValidMoves():
		root.AddChild(move)

	i = randrange(len(root.children))
	pick = root.children[i]
	move = pick.move
	#print "in append"
	game.PlayMove(move)
	return pick

def BackProp(leaf, result):

	while(leaf.parent != None):
		leaf.w_i += result
		leaf.n_i += 1
		leaf = leaf.parent
	leaf.n_i +=1
	return

def MCTS(root, game, iterations):
	while(iterations > 0):
		leaf = TraverseUCB(root, game)

		leaf = AppendChildren(leaf, game)

		player = (game.move % 2) + 1

		result = game.Simulate(player)

		game.ResetState()

		BackProp(leaf, result)

		iterations -= 1
		#print "iteration:" ,iterations

	return

def BestMove(root):
	Child_Expec_Pair = {}
	for child in root.children:
		Child_Expec_Pair[child] = child.ComputeExpectation()
	return max(Child_Expec_Pair.iterkeys(), key=lambda k: Child_Expec_Pair[k])

def TraverseNode(root, move):
	for child in root.children:
		if(child.move == move):
			return child
	raise Exception("No move %d in game tree found" % move)



game = GameState()
root = GameTree()



temp_game = deepcopy(game)

while(game.CheckTerminate):
	MCTS(root, temp_game, 1000)
	node = BestMove(root)
	game.PlayMove(node.move)
	game.PrintGame()


	if(game.CheckTerminate()):
		break
	move = int(raw_input("Your Move:"))
	game.PlayMove(move)
	game.PrintGame()

	root = TraverseNode(node, move)







