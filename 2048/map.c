#include<stdlib.h>
#include<stdio.h>
#include<time.h>
#include "map.h"

/*BOUGER VERS HAUT*/
int move_up(int a[][4])
{
	int i,j,k,n;
	int succeed=0;
	for(j=0;j<4;j++)	
	{
		for(i=1;i<4;i++)	
		{
			n=4;
			while(n--)
			{
				if(a[i-1][j]==0)
				{
					for(k=i;k<4;k++)
					{
						a[k-1][j]=a[k][j];
						if (a[k][j]!=0) succeed=1;
						a[k][j]=0;
					}
				}
			}
		}

		for(i=1;i<4;i++)
		{

			if(a[i-1][j]==0)
				for(k=i;k<4;k++)
				{
					a[k-1][j]=a[k][j];
					a[k][j]=0;
				}
			if(a[i-1][j]==a[i][j] && a[i-1][j])
			{
				a[i-1][j]+=1;
				a[i][j]=0;
				succeed=1;
			}
			
			
			
		
		}
	}
	return (succeed);
}

/*BOUGER VERS BAS*/
int move_down(int a[][4])
{
	int i,j,k,n;
	int succeed=0;
	for(j=0;j<4;j++)	
	{
		for(i=3;i>=1;i--)	
		{
			n=4;
			while(n--)
			{
				if(a[i][j]==0)
				{
					for(k=i;k>=1;k--)
					{
						a[k][j]=a[k-1][j];
						if (a[k-1][j]!=0) succeed=1;
						a[k-1][j]=0;
					}
				}
			}
		}
		for(i=2;i>=0;i--)
		{
			
			if(a[i+1][j]==0)
				for(k=i+1;k>=1;k--)
				{
					a[k][j]=a[k-1][j];
					a[k-1][j]=0;
				}
			if(a[i+1][j]==a[i][j] && a[i+1][j])
			{
				a[i+1][j]+=1;
				a[i][j]=0;
				succeed=1;
			}
			
			
		}
	}
	return (succeed);
}


/*BOUGER VERS GAUCHE*/
int move_left(int a[][4])
{
	int i,j,k,n;
	int succeed=0;
	for(i=0;i<4;i++)	
	{
		for(j=1;j<4;j++)	
		{
			n=4;
			while(n--)
			{
				if(a[i][j-1]==0)
				{
					for(k=j;k<4;k++)
					{
						a[i][k-1]=a[i][k];
						if (a[i][k]!=0) succeed=1;
						a[i][k]=0;
					}
				}
			}
		}
		for(j=1;j<4;j++)
		{
			if(a[i][j-1]==0)
				for(k=j;k<4;k++)
				{
					a[i][k-1]=a[i][k];
					a[i][k]=0;
				}
			
			if(a[i][j-1]==a[i][j] && a[i][j-1])
			{
				a[i][j-1]+=1;
				a[i][j]=0;
				succeed=1;
			}
			
		}
	}
	return (succeed);
}


/*BOUGER VERS DROITE*/
int move_right(int a[][4])
{
	int i,j,k,n;
	int succeed=0;
	for(i=0;i<4;i++)	
	{
		for(j=3;j>=1;j--)	
		{
			n=4;
			while(n--)
			{
				if(a[i][j]==0)
				{
					for(k=j;k>=1;k--)
					{
						a[i][k]=a[i][k-1];
						if (a[i][k-1]!=0) succeed=1;
						a[i][k-1]=0;
					}
				}
			}
		}
		for(j=2;j>=0;j--)
		{
			
			if(a[i][j+1]==0)
				for(k=j+1;k>=1;k--)
				{
					a[i][k]=a[i][k-1];
					a[i][k-1]=0;
				}
			
			if(a[i][j+1]==a[i][j] && a[i][j+1]){
				succeed=1;
				a[i][j+1]+=1;
				a[i][j]=0;
					
			}
			
		}
	}
	return (succeed);
}

/*CHERCHER UN 0 ET ASSIGNER 2(90%) OU 4(10%)*/

void rand_value(int a[][4])	
{
	int i,j;
	int r,c;
	srand(time(NULL));
	A:
		{
			r=rand()%4;
			c=rand()%4;

			if(a[r][c]==0)
				a[r][c]=rand()%10?1:2;
			else{
				goto A;
				}
		}
}

/*MONTRER SI LE JEU EST TERMINE*/
int isEnd(int a[][4])
{
	int i,j,cnt1=0,cnt2=0,cnt=0;
	//COMPTER LES VALEURS NON NUL
	for(i=0;i<4;i++)	
		for(j=0;j<4;j++)
		{
			if(a[i][j]==11)
			{
				printf("Good Job!\n");
				return 0;
			}
			if(a[i][j]!=0) cnt++;
		}
	//CHERCHER SI TOUTES LES CELLULES ADJACENTES NE SONT PAS EGALES
	if(cnt==16)
	{
	for(j=0;j<4;j++) //entre 2 lignes adjacentes	
	{
		for(i=1;i<4;i++)
		if(a[i][j]!=a[i-1][j])
			cnt1++;
	}
	for(i=0;i<4;i++) //entre 2 colones adjacentes	
	{
		for(j=1;j<4;j++)
		if(a[i][j]!=a[i][j-1])
			cnt2++;
	}
	cnt1+=cnt2;
	if(cnt1==24)
	{
		printf("Game Over!\n");
		return 0;
	}
	}
	return 1;
}

