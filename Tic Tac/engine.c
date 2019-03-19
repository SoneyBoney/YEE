#include "game.c"




typedef struct Node{
	int move_position;
	struct Node **children;
	struct Node *parent;
	unsigned int w_i; // wins after ith move
	unsigned int n_i; // games after ith move
	unsigned int t; // simulations for parent node
} Node;


Node *create_node(int move_position, Node *parent) {
	Node *new_node = (Node *) malloc(sizeof(Node));
	new_node -> move_position = move_position;
	new_node -> children = NULL;
	new_node -> parent = parent;
	new_node -> w_i = 0;
	new_node -> n_i = 0;
	new_node -> t = parent -> n_i;

	return new_node;
}



// selection

long double compute_UCB(Node *node) {
	if(node -> n_i == 0)
		return -1;
	long double expectation_estimate = ((long double) node -> w_i) / ((long double) node -> n_i);
	long double exploration_factor = (long double) sqrt((2 * log(node -> t)) / (long double) node -> n_i);
	return expectation_estimate + exploration_factor;
}


// expansion

// simulation
int simulate(State *starting_pos) {
	int i,empty_cell, i_c, j_c,move;
	while(starting_pos -> move <= 8 && !check_win(starting_pos)) {
		move = rand() % 9;
		play_move(move, starting_pos);
	}
	int end_moves = starting_pos -> move;
	if(end_moves == 9)
		return 0;
	if(end_moves % 2 == 0)
		return 1;
	return 2;
}

void reset_game(State *game) {
	game -> move = 0;
	for(int i = 0; i < 3; i++) {
		for(int j = 0; j < 3; j++) {
			(game -> board)[i][j] = 0;
		}
	}
	return;
}


// back prop