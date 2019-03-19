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
	State *game = initialize_game();
	int winner;
	int p1,p2,ties = 0;

	for(int i = 0; i<1000; i++) {
		winner = simulate(game);
		if(winner == 1)
			p1++;
		else if(winner == 2)
			p2++;
		else
			ties++;
		reset_game(game);
	}

	printf("player 1 won: %d times\n", p1);
	printf("player 2 won: %d times\n", p2);
	printf("ties: %d\n", ties);

	free(game);
	return 1;


}