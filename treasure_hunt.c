#include <stdio.h>
#include <math.h>
#include <gsl/gsl_rng.h>
#include <time.h>
#include <stdlib.h>

//function to get a random number between 0.0 to 1.0
int getRandom()
{
		srand(getpid());
		int u = rand()%8;
		return u;
}
		
//checks if the location as already been allocated to the team
int exists(int *excludeList, int l, int LOC_MAX)
{
	int j = 0;
	int ret = 1;
	
	for(; j < LOC_MAX; j++)
	{
		if(l == *(excludeList + j))
			ret = 0;
	}
	
	return ret;
}
		
void getLocs(int *teams, int i, int LOC_MAX)
{
	int j,k;
	
	int *excludeList;
	
	excludeList = (int *)calloc(LOC_MAX, sizeof(int)); //when a team gets allotted a location it gets into this list to prevent re-allocation
	
	for(j = 0; j < LOC_MAX; j++)
		*(excludeList + j) = 1001;
	
	for(j = 0; j < LOC_MAX; j++)
	{
		int loc = 0;
		while(!exists(excludeList, loc, LOC_MAX))
		{
			
			double u = rand()/((double)RAND_MAX);
			//printf("%le", u); 
			
			//assigns location
			if(u < 0.1)
				loc = 1;
			else
				if(u < 0.2)
					loc = 2;
				else
					if(u < 0.3)
						loc = 3;
					else
						if(u < 0.4)
							loc = 4;
						else
							if(u < 0.5)
								loc = 5;
							else
								if(u < 0.6)
									loc = 6;
								else
									if(u < 0.7)
										loc = 7;
									else
										//if(u < 0.8)
											loc = 8;
										//else
											//if(u < 0.9)
												//loc = 9;
											//else
												//loc = 10;
												
			
		}
		*(teams + LOC_MAX*i + j) = loc;
		*(excludeList + j) = loc;	
	}
}
			
int main()
{
	FILE *fpw, *fpr;
	
	fpr = fopen("treasure_hunt_param.dat", "r");
	
	int MAX_TEAMS, LOC_MAX;
	int *teams;
	
	//input file has the format <TOTAL NUMBER OF TEAMS> <TOTAL LOCATIONS + 1>
	//you just take the first 8 positions :P
	fscanf(fpr,"%d %d", &MAX_TEAMS, &LOC_MAX);
	
	teams = (int *)calloc(MAX_TEAMS*LOC_MAX, sizeof(int));
	
	fpw = fopen("team_roster.dat", "w");
	
	int i, j;
	
	srand(getpid());
	for(i = 0; i < MAX_TEAMS; i++)
	{
		getLocs(teams, i, LOC_MAX);
	}
	
	for(i = 0; i < MAX_TEAMS; i++)
	{
		fprintf(fpw, "%d ", i);
		//printf("%d ", i);
		for(j = 0; j < LOC_MAX; j++)
		{
			fprintf(fpw, "%d ", *(teams + LOC_MAX*i + j));
			//printf("%d ", teams[i][j]);
		}
		fprintf(fpw, "\n");
		//printf("\n");
	}
	return 0;
}
		
