#include "game.c"



typedef struct Node{
	long double weight;
	struct Node **children;
	struct Node *parent;
	unsigned int w_i; // wins after ith move
	unsigned int n_i; // games after ith move
	double c; // exploration parameter
	unsigned int t; // simulations for parent node
} Node;

// selection


// expansion

// back prop