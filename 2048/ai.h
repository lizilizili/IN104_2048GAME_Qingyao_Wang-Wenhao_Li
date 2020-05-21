#ifndef __AI_H__
#define __AI_H__


enum directions {
    UP=0,DOWN=1,LEFT=2,RIGHT=3,QUIT=4
};

int ai_next(int (*)[4]);
int simple_ai_next(int (*)[4]);
void arr_copy(int (*)[4],int (*)[4]);
double value(int (*)[4],int ,int*, double );
int next_score(int [4][4],int,int*);
#endif
