#include "tools.h"
#include <time.h>
#include "game2048.h"

void rand_two(void)
{
	srand(time(NULL));
	int x=0;
	int y=0;	
	if(is_full() || !is_move_merge)
		return;
	do{
		x=rand()%4;
		y=rand()%4;
	}while(view[x][y]);
	view[x][y]=2;
}

void show_view(void)
{
	system("clear");
	for(int i=0;i<4;i++)
	{
		printf("---------------------\n");
		for(int j=0;j<4;j++)
		{
			if(view[i][j])
				printf("|%4d",view[i][j]);
			else
				printf("|    ");
		}
		printf("|\n");
	}
	printf("---------------------\n");
}

int is_die(void)
{
	if(!is_full())
		return 0;
	
	for(int i=0;i<4;i++)
	{
		for(int j=0;j<3;j++)
		{
			if(i<3 && view[i][j]==view[i+1][j])
				return 0;
			if(view[i][j]==view[i][j+1])
				return 0;
		}
	}
	return 1;
}

int is_full(void)
{
	int *p=(int*)view;
	for(int i=0;i<16;i++)
	{
		if(!p[i])
			return 0;
	}
	return 1;
}
 




