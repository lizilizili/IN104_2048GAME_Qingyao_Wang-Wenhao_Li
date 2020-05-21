#include<stdlib.h>
#include<stdio.h>
#include<time.h>
#include "ai.h"
#include "map.h"
#include "eval.h"



/*COPIER UN MATRICE*/
void arr_copy(int a[][4],int b[][4]){
	for (int i=0;i<4;i++){
                for (int j=0;j<4;j++){
			b[i][j]=a[i][j];
		}
	}

}

/*CHERCHER LE SCORE D'EVALUATION D'UN MOUVEMENT SELON LA DIRCTION dir. */
int next_score(int a[4][4],int dir,int *estimate){
	
	int moved=0;
	switch (dir){
                case UP: moved=move_up(a);*estimate=evaluation(a); break ;
                case DOWN: moved=move_down(a);*estimate=evaluation(a); break ;
                case LEFT: moved=move_left(a);*estimate=evaluation(a);break ;
                case RIGHT: moved=move_right(a);*estimate=evaluation(a);break ;
		}
	
	return(moved);	
}

/*CHERCHER LA DECISION OPTIMALE D'UN PROGONDEUR DONNE*/
double value(int a[][4],int depth,int* next, double max){
	int depth_map[16]={4,4,4,3,3,3,2,2,2,2,2,1,1,1,1,1};
	//condition de terminer (depth<=0)
	int estimate=evaluation(a);
	if (depth<=0) return estimate;
	
	//retrancher des branches
	int n_zeros=count_zeros(a);
	if (depth>depth_map[n_zeros]) depth--;

	double max1=0;
	int dir=QUIT;
	int v=0;
	int b[4][4]={0};
	for (int i=0;i<4;i++){
		arr_copy(a,b);
		//chercher le score d'estimation moyen apres un mouvement.
		if(next_score(b,i,&v)){
			
			if (v>max) {max=v;}
			int n_zeros=count_zeros(b);
			double v1=0;
			
			for (int j=0;j<4;j++){
                		for (int k=0;k<4;k++){
					if (!b[j][k]){
						// 2 possibilites: 2(90%) 4(10%)
						b[j][k]=1;
						v1+=0.9*value(b,depth-1,NULL,max);
						b[j][k]=2;
						v1+=0.1*value(b,depth-1,NULL,max);
						b[j][k]=0;
					}
				}
			}
			v1=v1 /n_zeros;
			if (v1>max1) {max1=v1;dir=i;max=max1;}
				
		}
		
	}
	if(next) *next=dir;
	

	return(max);
}

/*CHERCHER LA DEMARCHE SUIVANTE POUR UN IA PLUS COMPLEXE */
int ai_next(int a[][4]){
	int depth_map[16]={4,4,4,3,3,3,2,2,2,2,2,1,1,1,1,1};
	int n_zeros=count_zeros(a);
	int next=4;
	double estimate=value(a,depth_map[n_zeros],&next,0);
	return(next);
}


/*CHERCHER LA DEMARCHE SUIVANTE POUR UN IA SIMPLE */
int simple_ai_next(int a[][4]){
	int score=0;
	int score_b=0;
	int next=0;
	int b[4][4]={0};
	for (int i=0;i<4;i++){
		arr_copy(a,b);
		if(next_score(b,i,&score)){
			if (score>score_b) {next=i;score_b=score;}	
		}
	}
	return(next);
	
}


