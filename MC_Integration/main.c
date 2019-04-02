#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <time.h>


/*
// parse structer
typedef struct list{
	char *token;
	list *next;
} list;



list *parse(char *string) {


	return NULL;
}


double MC_Integrate(void) {
	return 0;


}

*/



double square(double x) {
	return x * x;
}







int main(void) {
	//srand(time(NULL));
	double x,y;



	double x_low = 0;
	double x_high = 1;

	int y_high = square(x_high);
	int y_low = square(x_low);



	for(int i = 1000; i > 0 ; i--) {

		// x = rand(x_low, x_high);
		// y = rand(y_low, y_high);









	}
	srandomdev();


	printf("%f\n", fromint(random()));



	return 0;
}