#include "engine.c"

/*
int main(void) {
	int position;
	int valid_move;
	int player;
	State *game = initialize_game();
	while(game->move <= 8 && !check_win(game)) {
		player = ((game -> move) % 2) + 1;
		printf("Player %d, please enter move: ", player);
		scanf("%d", &position);
		if(position >= 0 && position <= 9) {
			valid_move = play_move(position, game);
			if(valid_move) {
				print_game(game);
			}
		}
	}
	printf("Congrats player %d!\n", player);

	return 0;
}
*/




int main(void) {
	srand(time(NULL));
	Node *root;
	Node *node;
	Node *node2;
	int move;

	State *game = initialize_game();
	root = create_node(-1, NULL);
	MCTS(root, game, 1000);
	

	while(game->move <= 8 && !check_win(game)) {
		// human turn
		printf("play a move: ");
		scanf("%d", &move);

		play_move(move,game);
		print_game(game);

		root = traverse_move(root, move);
		
		// Engine turn
		MCTS(root, game, 1000);

		node = pick_best_move(root);

		play_move(node->move_position, game);

		print_game(game);
		root = node;

		
	}


	
	return 1;

}

