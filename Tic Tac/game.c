#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include <string.h>
#include <stdio.h>
#include <time.h>


typedef struct {
	int move;
	int board[3][3];
} State;

State *initialize_game(void);
void print_game(State *game);
int play_move(int position, State *game);

State *initialize_game(void) {
	State *game = (State *) malloc(sizeof(State));

	if(game == NULL)
		return NULL;

	game -> move = 0;
	for(int i = 0; i < 3; i++) {
		for(int j = 0; j < 3; j++) {
			(game -> board)[i][j] = 0;
		}
	}
	return game;
}

void print_game(State *game) {

	printf("Game move: %d\n", game -> move);

	for(int i = 0; i < 3; i++) {
		for(int j = 0; j < 3; j++) {
			if((game -> board)[i][j] == 0) {
				printf(" ");
			}
			else if((game -> board)[i][j] == 1) {
				printf("O");
			}
			else if((game -> board)[i][j] == 2) {
				printf("X");
			}
			if(j == 2) {
				printf("\n");
				break;
			}
			printf("|");
		}
		if(i != 2)
			printf("-----\n");
	}

	return;
}

int play_move(int position, State *game) {
	int i_c = position / 3;
	int j_c = position % 3;

	if((game->board)[i_c][j_c]!=0)
		return 0;
	else {
		(game -> move)++;
		if((game -> move) % 2 == 1)
			(game->board)[i_c][j_c] = 1;
		else
			(game->board)[i_c][j_c] = 2;
	}
	return 1;
}

int check_win(State *game) {
	//int i,j;
	int a,b,c;
	// column wins
	//for(int i = 0; i < 2; ++i) {
		a = (game->board)[0][0];
		b = (game->board)[1][0];
		c = (game->board)[2][0];
		if((a == b) && (a == c) && (b==c) && (a != 0) && (b!=0)&&(c!=0)) {
		//if((game->board)[0][i] == (game->board)[1][i] && (game->board)[1][i] == (game->board)[2][i] && (game->board)[2][i] != 0)
			return 1;
		}

		a = (game->board)[0][1];
		b = (game->board)[1][1];
		c = (game->board)[2][1];
		if((a == b) && (a == c) && (b==c) && (a != 0) && (b!=0)&&(c!=0))
			return 1;

		a = (game->board)[0][2];
		b = (game->board)[1][2];
		c = (game->board)[2][2];
		if((a == b) && (a == c) && (b==c) && (a != 0) && (b!=0)&&(c!=0))
			return 1;

		
	//}
	// row wins
	//for(int i = 0; i < 2; ++i) {
		a = (game->board)[0][0];
		b = (game->board)[0][1];
		c = (game->board)[0][2];
		if((a == b) && (a == c) && (b==c) && (a != 0) && (b!=0)&&(c!=0)) {
		//if((game->board)[i][0] == (game->board)[i][1] && (game->board)[i][1] == (game->board)[i][2] && (game->board)[i][2] != 0)
			return 1;
		}
	//}

		a = (game->board)[1][0];
		b = (game->board)[1][1];
		c = (game->board)[1][2];
		if((a == b) && (a == c) && (b==c) && (a != 0) && (b!=0)&&(c!=0))
			return 1;

		a = (game->board)[2][0];
		b = (game->board)[2][1];
		c = (game->board)[2][2];
		if((a == b) && (a == c) && (b==c) && (a != 0) && (b!=0)&&(c!=0))
			return 1;



	// diag wins
	a = (game->board)[1][1];
	b = (game->board)[0][0];
	c = (game->board)[2][2];
	if((a == b) && (a == c) && (b==c) && (a != 0) && (b!=0)&&(c!=0)) {
	//if((game->board)[1][1] == (game->board)[0][0] && (game->board)[0][0] == (game->board)[2][2] && (game->board)[2][2] != 0)
		return 1;
	}
	a = (game->board)[1][1];
	b = (game->board)[2][0];
	c = (game->board)[0][2];
	if((a == b) && (a == c) && (b==c) && (a != 0) && (b!=0)&&(c!=0)) {
	//if((game->board)[1][1] == (game->board)[2][0] && (game->board)[2][0] == (game->board)[0][2] && (game->board)[0][2] != 0)
		return 1;
	}

	return 0;
}






