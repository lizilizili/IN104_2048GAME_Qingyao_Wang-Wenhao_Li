#include<stdlib.h>
#include<stdio.h>
#include<time.h>
#include "eval.h"

/*DONNER LE VALEUR MAXIMAL ET LA SOMME*/
void score(int a[][4],int* max,int* total){
	*total=0;
	int value_real[12]={0,2,4,8,16,32,64,128,256,512,1024,2048};
	for (int i=0;i<4;i++){
                for (int j=0;j<4;j++){
			if (value_real[a[i][j]]>*max) *max=value_real[a[i][j]];
			*total+=value_real[a[i][j]];
		}
	}
}

/*COMPTER LES ZEROS*/
int count_zeros(int a[][4]){
	int count=0;
	for (int i=0;i<4;i++){
                for (int j=0;j<4;j++){
			if (a[i][j]==0) count++;
		}
	}
	return(count);

}

/*EVALUATION D'UNE MATRICE*/
int evaluation(int a[][4]){
	int estimate=0;
	int value_weight[12]={0,1,3,9,27,81,241,723,2169,6487,19461,58383};
	int cell_weight[4][4]={{17,13,11,10},
			       {13,10, 9, 9},
			       {11, 9, 8, 8},
			       {10, 9, 8, 8}};
	for (int i=0;i<4;i++){
                for (int j=0;j<4;j++){
			estimate+=value_weight[a[i][j]]*cell_weight[i][j];
		}
	}
	return estimate;
}



