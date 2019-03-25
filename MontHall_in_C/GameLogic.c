#include <stdlib.h>
#include <stdio.h>
#include <time.h>


int simulate(int guess, int swap) {

	int car = rand() % 3;

	if(swap == 0) {
		if(guess == car)
			return 1;
		else
			return 0;
	}

	int not = 0;

	while(not == car || not == guess) {
		not++;
	}

	int new = 0;

	while(new == not || new == guess) {
		new++;
	}

	if(new == car)
		return 1;

	return 0;
}











int main(void) {
	srand(time(NULL));

	unsigned int total;
	int swap;
	int guess;

	scanf("%d %d", &total, &swap);

	int total2 = total;

	unsigned int success = 0;

	for(;total > 0; total--) {
		guess = rand() % 3;
		printf("guess: %d\n", guess);
		if(simulate(guess, swap) == 1)
			success++;
	}


	long double rate = (long double) success / (long double) total2;

	printf("Success rate: %Lf\n", rate);


	return 0;
}