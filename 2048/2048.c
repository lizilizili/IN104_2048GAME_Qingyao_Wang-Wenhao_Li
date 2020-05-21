/************************** 22/05/2020 ******************************/
/************************* QINGYAO WANG *****************************/
/********************************************************************/
/*

	gcc 2048.c map.c ai.c eval.c $(sdl-config --cflags --libs)
  	
	il y a 4 modes que vous pouvez choisir
	./a.out MANUAL
	./a.out RANDOM
	./a.out SIMPLE_AI
	./a.out AI

*/

#include<stdio.h>
#include<stdlib.h>
#include <stdbool.h>
#include<time.h>
#include <SDL.h>
#include "map.h"
#include "eval.h"
#include "ai.h"

#define SCREEN_WIDTH (480)
#define SCREEN_HEIGHT (480)
#define IMAGE_HEIGHT (120)
#define IMAGE_WIDTH (120)

enum modes {
    MANUAL=0,RANDOM=1,SIMPLE_AI=2,AI=3
};


int main(int argc, char *argv[])
{
	int mode=-1;
	int best=0,total=0;
	int a[4][4]={0};
	int a_ori[4][4]={0};
	
	/*4 MODES DIFFERENTES*/
	switch(argv[1][0]){
	case 'M':mode=MANUAL;break;
	case 'R':mode=RANDOM;break;
	case 'S':mode=SIMPLE_AI;break;
	case 'A':mode=AI;break;
    	}
    	int flip=1;

	memset(a,0,sizeof(a));
	memset(a_ori,-1,sizeof(a_ori));
	int i,j,flag=1,go_on=1;
	SDL_Surface *g_screenSurface = NULL ;
	SDL_Surface * Image[12];
	SDL_Rect src;
	SDL_Rect dest;

	/*load des images*/
    	Image[0] = SDL_LoadBMP("0.bmp");
	Image[1] = SDL_LoadBMP("2.bmp");
	Image[2] = SDL_LoadBMP("4.bmp");
	Image[3] = SDL_LoadBMP("8.bmp");
	Image[4] = SDL_LoadBMP("16.bmp");
	Image[5] = SDL_LoadBMP("32.bmp");
	Image[6] = SDL_LoadBMP("64.bmp");
	Image[7] = SDL_LoadBMP("128.bmp");
	Image[8] = SDL_LoadBMP("256.bmp");
	Image[9] = SDL_LoadBMP("512.bmp");
	Image[10] = SDL_LoadBMP("1024.bmp");
	Image[11] = SDL_LoadBMP("2048.bmp");
    	src.x=0;
    	src.y=0;
    	src.w=IMAGE_WIDTH;
    	src.h=IMAGE_HEIGHT;
    	dest.w=IMAGE_WIDTH;
   	dest.h=IMAGE_HEIGHT;


    if (SDL_Init (SDL_INIT_VIDEO) < 0) {
        printf ("Unable to init SDL: %s\n", SDL_GetError ()) ;
        return (-1) ;
    }

    g_screenSurface = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32, SDL_HWSURFACE | SDL_DOUBLEBUF) ;

    if (g_screenSurface == NULL) {
        printf("Unable to set %dx%d video: %s\n", SCREEN_WIDTH, SCREEN_HEIGHT,
        SDL_GetError ()) ;
        SDL_Quit () ;
        return (-1) ;
    }
    /* Set the title of the window. */
    SDL_WM_SetCaption ("Press ESC to quit.", NULL) ;

    

    while (go_on && flag) {
        SDL_Event event ;

        if (flip){
            if (SDL_MUSTLOCK (g_screenSurface)) {
                if (SDL_LockSurface(g_screenSurface) < 0) return (-5) ;
            }

            rand_value(a);
            for (int i=0;i<4;i++){
                for (int j=0;j<4;j++){
		/*afficher les noveaux valeurs des cellules*/
                    if (a[i][j]!=a_ori[i][j]){
                            dest.x=j*IMAGE_WIDTH;
                            dest.y=i*IMAGE_HEIGHT;
                            SDL_BlitSurface(Image[a[i][j]],&src,g_screenSurface,&dest);
                            a_ori[i][j]=a[i][j];
                    }
                }
            }

	    /*si le jeu est termine on affiche les resultats*/
            flag = isEnd(a);
	    if (!flag) {
		score(a,&best,&total);
		printf("BEST=%d, SCORE=%d\n",best,total);
	    }

            if (SDL_MUSTLOCK (g_screenSurface))
                SDL_UnlockSurface (g_screenSurface) ;
            SDL_Flip (g_screenSurface) ;
            flip = 0;
	    SDL_Delay(100);
        }

	/*MODE MANUAL*/
	if (mode==MANUAL)
		
        /* on quite si on presse le bouton ESC.*/
		if (SDL_PollEvent (&event)) {
           		if (event.type == SDL_QUIT) go_on = 0 ;
         		if (event.type == SDL_KEYDOWN) {
              			switch (event.key.keysym.sym) {
              			case SDLK_ESCAPE: go_on = 0 ; break ;
                    		case SDLK_UP: flip = move_up(a); break ;
                   		case SDLK_DOWN: flip = move_down(a);break ;
                   		case SDLK_LEFT: flip = move_left(a);break ;
                   	 	case SDLK_RIGHT: flip = move_right(a);break ;
                    		default: break ;  /* Explicitly ignore. */
                		}
            		}
		
		 }      /* End of while (SDL_PollEvent (&event)). */


	/*MODE RANDOM*/
	if(mode==RANDOM){
		srand(time(NULL));
		while(!flip && isEnd(a)){
			switch (rand()%4){
               	 	case 0: flip = move_up(a); break ;
                	case 1: flip = move_down(a);break ;
                	case 2: flip = move_left(a);break ;
                	case 3: flip = move_right(a);break ;
			}
		}	
	}
	

	/*MODE AI*/
	if(mode==AI){
		switch (ai_next(a)){
                case UP: flip = move_up(a); break ;
                case DOWN: flip = move_down(a);break ;
                case LEFT: flip = move_left(a);break ;
                case RIGHT: flip = move_right(a);break ;
		case QUIT: go_on = 0 ; break ;
		}

	}


	/*MODE SIMPLE_AI*/
	if(mode==SIMPLE_AI){
		switch (simple_ai_next(a)){
                case UP: flip = move_up(a); break ;
                case DOWN: flip = move_down(a);break ;
                case LEFT: flip = move_left(a);break ;
                case RIGHT: flip = move_right(a);break ;
		}

	}
    


  }        /* End of while (go_on). */

  SDL_FreeSurface (g_screenSurface) ;
  SDL_Quit () ;
	return 0;
}
