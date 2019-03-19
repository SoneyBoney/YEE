#include "game.c"


typedef struct Node Node;
typedef struct Children_Array Children_Array;

struct Node {
	int move_position;
	int depth;
	Children_Array *children;
	struct Node *parent;
	int w_i; // wins after ith move
	unsigned int n_i; // games after ith move
};


struct Children_Array {
	int size;
	Node **array;
};


Children_Array *create_children(int size) {
	Children_Array *children = (Children_Array *) malloc(sizeof(Children_Array));
	children -> array = (Node **) malloc(sizeof(Node *) * size);
	return children; 
}


Node *create_node(int move_position, Node *parent) {
	Node *new_node = (Node *) malloc(sizeof(Node));
	new_node -> move_position = move_position;
	new_node -> children = NULL;
	new_node -> parent = parent;
	new_node -> w_i = 0;
	new_node -> n_i = 0;

	if(parent == NULL)
		new_node -> depth = 0;
	else
		new_node -> depth = (parent -> depth) + 1;



	return new_node;
}



// selection

long double compute_UCB(Node *node, int t) {
	if(node -> n_i == 0)
		return -1;
	long double expectation_estimate = ((long double) node -> w_i) / ((long double) node -> n_i);
	long double exploration_factor = (long double) sqrt((2 * log((long double) t)) / (long double) node -> n_i);
	return expectation_estimate + exploration_factor;
}

Node *UCB_traversal(Node *root, State *game) {
	if(root == NULL)
		return NULL;
	int num_children,i,t;
	Node *max_child;
	Node **children_arr;
	long double max_UCB,temp;

	while(root -> children != NULL) {
		t = root -> n_i;
		num_children = root -> children -> size;
		children_arr = (root -> children -> array);
		max_child = children_arr[0];
		max_UCB = compute_UCB(max_child, t);
		if(max_UCB != -1) {
			for(i = 1; i < num_children; i++) {
				temp = compute_UCB(children_arr[i], t);
				if(temp > max_UCB || temp == -1) {
					max_child = children_arr[i];
					max_UCB = temp;
					if(max_UCB == -1)
						break;
				}
			}
		}
		root = max_child;
		play_move(root -> move_position, game);
	}

	return root;
}


// expansion

void append_new_nodes(Node *parent, State *game) {
	int i_c,j_c;
	int num_valid_moves = 9 - (game -> move);
	int i,j = 0;

	if(num_valid_moves == 0) {
		printf("Cannot append more leaves: no valid moves\n");
		return;
	}

	Children_Array *children = create_children(num_valid_moves);

	for(; i < 9; i++) {
		i_c = i / 3;
		j_c = i % 3;
		if((game -> board)[i_c][j_c] == 0) {
			(children -> array)[j] = create_node(i, parent);
		}
	}

	return;
}


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

void back_prop(Node *leaf, int game_result) {
	if(leaf == NULL) {
		printf("error leaf is null\n");
		return;
	}

	while(leaf -> move_position != -1) {
		if((leaf -> depth) % 2 == 1)
			(leaf -> w_i) += game_result;
		else
			(leaf -> w_i) -= game_result;
		(leaf -> n_i)++;
		leaf = leaf -> parent;
	}

	return;

}

// Synthesis

Node *MCTS(int iterations) {
	State *game = initialize_game();
	Node *root = create_node(-1, NULL);

	Node *node;
	int result;

	for(; iterations > 0; iterations--) {
	// selection
		node = UCB_traversal(root, game);

	// expansion
		append_new_nodes(node, game);
	// simulation
		node = ((node -> children) -> array)[0];
		play_move(node -> move_position, game);
		result = simulate(game);
		reset_game(game);

	// backprop
		back_prop(node, result);

	}
	free(game);
	return root;
}

// engine

long double compute_expectation(int w_i, unsigned n_i) {
	return (long double) w_i / (long double) n_i;
}


Node *pick_best_move(int move, Node *node) {
	int num_children;
	long double max_expectation, temp;

	num_children = (node -> children) -> size;
	Node **children = (node -> children) -> array;

	Node *max_child = children[0];
	max_expectation = compute_expectation(max_child -> w_i, max_child -> n_i);
	for(int i = 1; i < num_children; i++) {
		temp = compute_expectation(children[i] -> w_i, children[i] -> n_i);
		if(temp > max_expectation) {
			max_child = children[i];
			max_expectation = temp;
		}
	}

	return max_child;

}