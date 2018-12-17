#include "fonctions.h"

#define MIN_ABS_BOUTON_JOUER 5 //a definir
#define MAX_ABS_BOUTON_JOUER 5 //a definir
#define MIN_ORD_BOUTON_JOUER 5 //a definir
#define MAX_ORD_BOUTON_JOUER 5 //a definir

#define MIN_ABS_BOUTON_QUITTER 5 //a definir
#define MAX_ABS_BOUTON_QUITTER 5 //a definir
#define MIN_ORD_BOUTON_QUITTER 5 //a definir
#define MAX_ORD_BOUTON_QUITTER 5 //a definir

int main(int argc, char** argv){
	SDL_Surface* ecran = NULL, menu = NULL, texte = NULL; // surface pour le menu
	SDL_Rect positionMenu, positionClic, positionTxt ;
	SDL_Event event ;
	int continuer = 1 ;

	TTF_Font* police = NULL ;
	SDL_Color couleurNoire = (0,0,0), couleurBlanche = (255, 255, 255) ;
	TTF_Font* policeBig = NULL ;

	FSOUND_STREAM* music = NULL ;
	FSOUND_Init(44100,32,0);

	music = FSOUND_STREAM_Open("tetris-official-theme-song.mp3", FSOUND_LOOP_NORMAL, 0, 0) ;

	TTF_Init(); //on initilise la police
	police = TFF_OpenFont("tetris.tff", 35) ;

	putenv("SDL_VIDEO_CENTERED=1") ; //on centre le fenetre
	SDL_Init(SDL_Init_VIDEO) ; // on initialise la SDL

	SDL_WM_SetIcon(IMG_Load("icon.jng"), NULL) ;
	ecran = SDL_SetVideoMode(LARGEUR_FENETRE, HAUTEUR_FENETRE, 32, SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_NOFRAME) ;
	SDL_WM_SetCaption("Tetris 3D", NULL) ;

	menu = IMG_Load("fond_du_menu") ;

	FSOUND_STREAM_SetLoopCount(music, -1) ;

	FSOUND_Stream_Play(FSOUND_FREE, music) ;

	positionMenu.x = 0;
	positionMenu.y = 0;

	while(continuer)
	{
		SDL_PollEvent(&event) ;
		switch(event.type){
			case SQL_QUIT:
				continuer = 0 ;
				break ;
			case SDL_MOUSEBUTTONUP:
				if(event.button.button == SDL_BUTTON_LEFT){
					positionClic.x = event.button.x ; // on recupere les coordonnées de la souris
					positionClic.y = event.button.y ;

					if(event.button.x>MIN_ABS_BOUTON_JOUER && event.button.x<MAX_ABS_BOUTON_JOUER && event.button.y>MIN_ORD_BOUTON_JOUER && event.button.y<MAX_ORD_BOUTON_JOUER){
						texte = TFF_rendreText_Blended(policeBig,"Bienvenue dans la 3eme dimension") ;
						positionTxt.x = 30 ; // position texte
						positionTxt.y = 500 ; // position texte
						SDL_BlitSurface(texte, NULL, ecran, &positionTxt) ;
						SDL_Flip(ecran) ;

						jouer(ecran) ;
					}
					else if(event.button.x>MIN_ABS_BOUTON_QUITTER && event.button.x<MAX_ABS_BOUTON_QUITTER && event.button.y>MIN_ORD_BOUTON_QUITTER && event.button.y<MAX_ORD_BOUTON_QUITTER){
						exit(0) ;
					}
				}
		}

		SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 0, 0, 0)) ;
		SDL_Flip(ecran) ;
	}

	FSOUND_Stream_Close(music) ;
	SDL_FreeSurface(menu) ;

	TFF_CloseFont(police) ;
	TTF_Quit() ;

	SDL_FreeSurface(texte);
	SDL_Quit() ;

	return EXIT_SUCCESS ;
}	

