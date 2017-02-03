#include <stdio.h>
#include <gsl/gsl_rng.h>
#include <time.h>

void main()
{
	int i = 0;
	srand(getpid());
	for(; i < 5; i++)
	{
		srand(getpid());
		int u = rand();
		printf("%d \n" , u);
	}
}
		
	
