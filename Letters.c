#include <stdio.h>
#include <stdlib.h>


int is_sum(int goal, int *set) {
	if(*set == -1 && goal == 0)
		return 1;
	else if(goal < 0)
		return 0;
	else
		return is_sum(goal - *set, set + 1) || is_sum(goal, set + 1);
}


int main(void) {
	int goal;
	int set[6];
	printf("Please enter the goal number: \n");
	scanf("%d", &goal);
	printf("Please enter the set of numbers: \n");
	scanf("%d %d %d %d %d", &set[0], &set[1], &set[2], &set[3], &set[4]);
	set[5] = -1;

	if(is_sum(goal, set))
		printf("subset sum complete!\n");
	else
		printf("failure\n");
	return 0;
}