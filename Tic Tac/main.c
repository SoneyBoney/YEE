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

	root = MCTS(10000000);

	

	int move;

	State *game = initialize_game();
	Node *node;

	while(game->move <= 8 && !check_win(game)) {

		
		// Given your move, return node with best move
		node = pick_best_move(move, root);
		// play this move

		play_move(node -> move_position, game);

		printf("Opponent played: %d\n", node -> move_position);
		print_game(game);

		root = node;

		
		printf("Please enter your move: ");
		scanf("%d", &move);

		// play your move
		play_move(move, game);

		printf("You moved:\n");
		print_game(game);
		
/*
		node = pick_best_move(move, root);
		play_move(node -> move_position, game);
		printf("player 1 played: %d\n", node -> move_position);
		print_game(game);

		root = node;

		node = pick_best_move(move, root);
		play_move(node -> move_position, game);
		printf("player 2 played: %d\n", node -> move_position);
		print_game(game);

		root = node;
*/

	}


	
	return 1;

}

