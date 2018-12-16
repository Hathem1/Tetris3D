#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <math.h>

#define TAILLE_MAX_PIECE 6

void freeArray(int*** cTab, int xSize, int ySize, int zSize) {
    for(int i = 0; i < xSize; i++) {
        for(int j = 0; j < ySize; j++) {
            delete[] cTab[i][j];
        }
        delete[] cTab[i];
    }
    delete[] cTab;
}

int*** file_to_array(char* name_file){

	FILE* file = fopen(name_file,"r") ;
	int*** array = NULL;
	int*** verif = NULL ;

	if(file == NULL){
		fprintf(stderr,"fopen() failed in file %s at line # %d", __FILE__,__LINE__) ;
    	exit(EXIT_FAILURE) ;
	}
	else{
		array = new int**[TAILLE_MAX_PIECE] ;
		verif = new int**[TAILLE_MAX_PIECE] ;
		for(int i=0;i<TAILLE_MAX_PIECE;i++){
			array[i] = new int*[TAILLE_MAX_PIECE] ;
			verif[i] = new int*[TAILLE_MAX_PIECE] ;
			for(int j=0;j<TAILLE_MAX_PIECE;j++){
				array[i][j] = new int[TAILLE_MAX_PIECE] ;
				verif[i][j] = new int[TAILLE_MAX_PIECE] ;
				for(int k=0;k<TAILLE_MAX_PIECE;k++){
					array[i][j][k] = 0 ;
					verif[i][j][k] = 0 ; 
				}
			}
		}
		int temp1 = 0 ;
		int temp2 = 0;
		int temp3 = 0;
		int ligne = 1 ; // numero de ligne
		char* chaine = new char[7];
		size_t linesize = 7;
		ssize_t nread ;
		char a = 0, b = 0, c = 0;
		int x = 0, y = 0, z = 0;
		while (1) {
			nread = getline(&chaine, &linesize, file);
			if(nread == -1){
				//printf("Le tableau a été correctement chargé\n"); 
				break;
			}
			//printf("%d %d\n",strlen(chaine), nread);
			nread = sscanf(chaine, "%c%d%c%d%c%d", &a, &x, &b, &y, &c, &z);
			//printf("%d %c %d %c %d %c %d\n", nread, a, x, b, y, c, z);
			if (nread!=6 && nread!=0) {
				fprintf(stderr,"Le format de la ligne %d du fichier est incorrecte\n", ligne);
				freeArray(array, TAILLE_MAX_PIECE, TAILLE_MAX_PIECE, TAILLE_MAX_PIECE) ;
				freeArray(verif, TAILLE_MAX_PIECE, TAILLE_MAX_PIECE, TAILLE_MAX_PIECE) ;
				return NULL ;
			}

			if(a=='x'&& b=='y' && c=='z'){
				if(ligne>1){
					if(!verif[x][y][z]){
						fprintf(stderr,"La structure de la forme est impossible, voir ligne fichier %d et ligne code %d\n", ligne, __LINE__);
						freeArray(array, TAILLE_MAX_PIECE, TAILLE_MAX_PIECE, TAILLE_MAX_PIECE) ;
						freeArray(verif, TAILLE_MAX_PIECE, TAILLE_MAX_PIECE, TAILLE_MAX_PIECE) ;
						return NULL ;
					}
				}

				if(x<TAILLE_MAX_PIECE && y<TAILLE_MAX_PIECE && z<TAILLE_MAX_PIECE){	
					array[x][y][z] = 1 ;
					if((x-1)>=0 && (y-1)>=0 && (z-1)>=0){
						verif[x-1][y-1][z-1] = 1 ;
					}
					if((x-1)>=0 && (y-1)>=0){
						verif[x-1][y-1][z] = 1 ;
					}
					if((x-1)>=0 && (z-1)>=0){
						verif[x-1][y][z-1] = 1 ;
					}
					if((y-1)>=0 && (z-1)>=0){
						verif[x][y-1][z-1] = 1 ;
					}
					if((y-1)>=0){
						verif[x][y-1][z] = 1 ;
					}
					if((z-1)>=0){
						verif[x][y][z-1] = 1 ;
					}
					if((x-1)>=0){
						verif[x-1][y][z] = 1 ;
					}
					// 7 cas sur 26 pour l'instant

					if((x+1)<TAILLE_MAX_PIECE && (y+1)<TAILLE_MAX_PIECE && (z+1)<TAILLE_MAX_PIECE){
						verif[x+1][y+1][z+1] = 1 ;
					}
					if((x+1)<TAILLE_MAX_PIECE && (y+1)<TAILLE_MAX_PIECE){
						verif[x+1][y+1][z] = 1 ;
					}
					if((x+1)<TAILLE_MAX_PIECE && (z+1)<TAILLE_MAX_PIECE){
						verif[x+1][y][z+1] = 1 ;
					}
					if((y+1)<TAILLE_MAX_PIECE && (z+1)<TAILLE_MAX_PIECE){
						verif[x][y+1][z+1] = 1 ;
					}
					if((y+1)<TAILLE_MAX_PIECE){
						verif[x][y+1][z] = 1 ;
					}
					if((z+1)<TAILLE_MAX_PIECE){
						verif[x][y][z+1] = 1 ;
					}
					if((x+1)<TAILLE_MAX_PIECE){
						verif[x+1][y][z] = 1 ;
					}
					// 14 cas sur 26 pour l'instant

					if((x-1)>=0 && (y-1)>=0 && (z+1)<TAILLE_MAX_PIECE){
						verif[x-1][y-1][z+1] = 1 ;
					}
					if((x-1)>=0 && (y+1)<TAILLE_MAX_PIECE && (z-1)>=0){
						verif[x-1][y+1][z-1] = 1 ;
					}
					if((x+1)<TAILLE_MAX_PIECE && (y-1)>=0 && (z-1)>=0){
						verif[x+1][y-1][z-1] = 1 ;
					}
					// 17 cas sur 26 

					if((x-1)>=0 && (y+1)<TAILLE_MAX_PIECE && (z+1)<TAILLE_MAX_PIECE){
						verif[x-1][y+1][z+1] = 1 ;
					}
					if((x+1)<TAILLE_MAX_PIECE && (y+1)<TAILLE_MAX_PIECE && (z-1)>=0){
						verif[x+1][y+1][z-1] = 1 ;
					}
					if((x+1)<TAILLE_MAX_PIECE && (y-1)>=0 && (z+1)<TAILLE_MAX_PIECE){
						verif[x+1][y-1][z+1] = 1 ;
					}
					// 20 cas sur 26 pour l'instant

					if((x-1)>=0 && (y+1)<TAILLE_MAX_PIECE){
						verif[x-1][y+1][z] = 1 ;
					}
					if((x+1)<TAILLE_MAX_PIECE && (z-1)>=0){
						verif[x+1][y][z-1] = 1 ;
					}
					if((x-1)>=0 && (z+1)<TAILLE_MAX_PIECE){
						verif[x-1][y][z+1] = 1 ;
					}
					if((x+1)<TAILLE_MAX_PIECE && (z-1)>=0){
						verif[x+1][y][z-1] = 1 ;
					}
					if((y-1)>=0 && (z+1)<TAILLE_MAX_PIECE){
						verif[x][y-1][z+1] = 1 ;
					}
					if((y+1)<TAILLE_MAX_PIECE && (z-1)>=0){
						verif[x][y+1][z-1] = 1 ;
					}
					// 26 cas sur 26 :)
				}
			}
			else if(a=='x' && b=='z'&& c=='y'){
				if(ligne>1){
					if(!verif[x][z][y]){
						fprintf(stderr,"La structure de la forme est impossible, voir ligne fichier %d et ligne code %d\n", ligne, __LINE__);
						freeArray(array, TAILLE_MAX_PIECE, TAILLE_MAX_PIECE, TAILLE_MAX_PIECE) ;
						freeArray(verif, TAILLE_MAX_PIECE, TAILLE_MAX_PIECE, TAILLE_MAX_PIECE) ;
						return NULL ;
					}
				}

				if(x<TAILLE_MAX_PIECE && z<TAILLE_MAX_PIECE && y<TAILLE_MAX_PIECE){	
					array[x][z][y] = 1 ;
					if((x-1)>=0 && (z-1)>= 0 && (y-1)>= 0){
						verif[x-1][z-1][y-1] = 1 ;
					}
					if((x-1)>=0 && (z-1)>=0){
						verif[x-1][z-1][y] = 1 ;
					}
					if((x-1)>=0 && (y-1)>=0){
						verif[x-1][z][y-1] = 1 ;
					}
					if((z-1)>=0 && (y-1)>=0){
						verif[x][z-1][y-1] = 1 ;
					}
					if((z-1)>=0){
						verif[x][z-1][y] = 1 ;
					}
					if((y-1)>=0){
						verif[x][z][y-1] = 1 ;
					}
					if((x-1)>=0){
						verif[x-1][z][y] = 1 ;
					}
					// 7 cas sur 26 pour l'instant

					if((x+1)<TAILLE_MAX_PIECE && (z+1)<TAILLE_MAX_PIECE && (y+1)<TAILLE_MAX_PIECE){
						verif[x+1][z+1][y+1] = 1 ;
					}
					if((x+1)<TAILLE_MAX_PIECE && (z+1)<TAILLE_MAX_PIECE){
						verif[x+1][z+1][y] = 1 ;
					}
					if((x+1)<TAILLE_MAX_PIECE && (y+1)<TAILLE_MAX_PIECE){
						verif[x+1][z][y+1] = 1 ;
					}
					if((z+1)<TAILLE_MAX_PIECE && (y+1)<TAILLE_MAX_PIECE){
						verif[x][z+1][y+1] = 1 ;
					}
					if((z+1)<TAILLE_MAX_PIECE){
						verif[x][z+1][y] = 1 ;
					}
					if((y+1)<TAILLE_MAX_PIECE){
						verif[x][z][y+1] = 1 ;
					}
					if((x+1)<TAILLE_MAX_PIECE){
						verif[x+1][z][y] = 1 ;
					}
					// 14 cas sur 26 pour l'instant

					if((x-1)>=0 && (z-1)>=0 && (y+1)<TAILLE_MAX_PIECE){
						verif[x-1][z-1][y+1] = 1 ;
					}
					if((x-1)>=0 && (z+1)<TAILLE_MAX_PIECE && (y-1)>=0){
						verif[x-1][z+1][y-1] = 1 ;
					}
					if((x+1)<TAILLE_MAX_PIECE && (z-1)>=0 && (y-1)>=0){
						verif[x+1][z-1][y-1] = 1 ;
					}
					// 17 cas sur 26 

					if((x-1)>=0 && (z+1)<TAILLE_MAX_PIECE && (y+1)<TAILLE_MAX_PIECE){
						verif[x-1][z+1][y+1] = 1 ;
					}
					if((x+1)<TAILLE_MAX_PIECE && (z+1)<TAILLE_MAX_PIECE && (y-1)>=0){
						verif[x+1][z+1][y-1] = 1 ;
					}
					if((x+1)<TAILLE_MAX_PIECE && (z-1)>=0 && (y+1)<TAILLE_MAX_PIECE){
						verif[x+1][z-1][y+1] = 1 ;
					}
					// 20 cas sur 26 pour l'instant

					if((x-1)>=0 && (z+1)<TAILLE_MAX_PIECE){
						verif[x-1][z+1][y] = 1 ;
					}
					if((x+1)<TAILLE_MAX_PIECE && (y-1)>=0){
						verif[x+1][z][y-1] = 1 ;
					}
					if((x-1)>=0 && (y+1)<TAILLE_MAX_PIECE){
						verif[x-1][z][y+1] = 1 ;
					}
					if((x+1)<TAILLE_MAX_PIECE && (y-1)>=0){
						verif[x+1][z][y-1] = 1 ;
					}
					if((z-1)>=0 && (y+1)<TAILLE_MAX_PIECE){
						verif[x][z-1][y+1] = 1 ;
					}
					if((z+1)<TAILLE_MAX_PIECE && (y-1)>=0){
						verif[x][z+1][y-1] = 1 ;
					}
					// 26 cas sur 26 :)
				}

			}
			else if(a=='y'&& b=='x' && c=='z'){
				if(ligne>1){
					if(!verif[y][x][z]){
						fprintf(stderr,"La structure de la forme est impossible, voir ligne fichier %d et ligne code %d\n", ligne, __LINE__);
						freeArray(array, TAILLE_MAX_PIECE, TAILLE_MAX_PIECE, TAILLE_MAX_PIECE) ;
						freeArray(verif, TAILLE_MAX_PIECE, TAILLE_MAX_PIECE, TAILLE_MAX_PIECE) ;
						return NULL ;
					}
				}

				if(y<TAILLE_MAX_PIECE && x<TAILLE_MAX_PIECE && z<TAILLE_MAX_PIECE){
					array[y][x][z] = 1 ;
					if((y-1)>=0 && (x-1)>= 0 && (z-1)>= 0){
						verif[y-1][x-1][z-1] = 1 ;
					}
					if((y-1)>=0 && (x-1)>=0){
						verif[y-1][x-1][z] = 1 ;
					}
					if((y-1)>=0 && (z-1)>=0){
						verif[y-1][x][z-1] = 1 ;
					}
					if((x-1)>=0 && (z-1)>=0){
						verif[y][x-1][z-1] = 1 ;
					}
					if((x-1)>=0){
						verif[y][x-1][z] = 1 ;
					}
					if((z-1)>=0){
						verif[y][x][z-1] = 1 ;
					}
					if((y-1)>=0){
						verif[y-1][x][z] = 1 ;
					}
					// 7 cas sur 26 pour l'instant

					if((y+1)<TAILLE_MAX_PIECE && (x+1)<TAILLE_MAX_PIECE && (z+1)<TAILLE_MAX_PIECE){
						verif[y+1][x+1][z+1] = 1 ;
					}
					if((y+1)<TAILLE_MAX_PIECE && (x+1)<TAILLE_MAX_PIECE){
						verif[y+1][x+1][z] = 1 ;
					}
					if((y+1)<TAILLE_MAX_PIECE && (z+1)<TAILLE_MAX_PIECE){
						verif[y+1][x][z+1] = 1 ;
					}
					if((x+1)<TAILLE_MAX_PIECE && (z+1)<TAILLE_MAX_PIECE){
						verif[y][x+1][z+1] = 1 ;
					}
					if((x+1)<TAILLE_MAX_PIECE){
						verif[y][x+1][z] = 1 ;
					}
					if((z+1)<TAILLE_MAX_PIECE){
						verif[y][x][z+1] = 1 ;
					}
					if((y+1)<TAILLE_MAX_PIECE){
						verif[y+1][x][z] = 1 ;
					}
					// 14 cas sur 26 pour l'instant

					if((y-1)>=0 && (x-1)>=0 && (z+1)<TAILLE_MAX_PIECE){
						verif[y-1][x-1][z+1] = 1 ;
					}
					if((y-1)>=0 && (x+1)<TAILLE_MAX_PIECE && (z-1)>=0){
						verif[y-1][x+1][z-1] = 1 ;
					}
					if((y+1)<TAILLE_MAX_PIECE && (x-1)>=0 && (z-1)>=0){
						verif[y+1][x-1][z-1] = 1 ;
					}
					// 17 cas sur 26 

					if((y-1)>=0 && (x+1)<TAILLE_MAX_PIECE && (z+1)<TAILLE_MAX_PIECE){
						verif[y-1][x+1][z+1] = 1 ;
					}
					if((y+1)<TAILLE_MAX_PIECE && (x+1)<TAILLE_MAX_PIECE && (z-1)>=0){
						verif[y+1][x+1][z-1] = 1 ;
					}
					if((y+1)<TAILLE_MAX_PIECE && (x-1)>=0 && (z+1)<TAILLE_MAX_PIECE){
						verif[y+1][x-1][z+1] = 1 ;
					}
					// 20 cas sur 26 pour l'instant

					if((y-1)>=0 && (x+1)<TAILLE_MAX_PIECE){
						verif[y-1][x+1][z] = 1 ;
					}
					if((y+1)<TAILLE_MAX_PIECE && (z-1)>=0){
						verif[y+1][x][z-1] = 1 ;
					}
					if((y-1)>=0 && (z+1)<TAILLE_MAX_PIECE){
						verif[y-1][x][z+1] = 1 ;
					}
					if((y+1)<TAILLE_MAX_PIECE && (z-1)>=0){
						verif[y+1][x][z-1] = 1 ;
					}
					if((x-1)>=0 && (z+1)<TAILLE_MAX_PIECE){
						verif[y][x-1][z+1] = 1 ;
					}
					if((x+1)<TAILLE_MAX_PIECE && (z-1)>=0){
						verif[y][x+1][z-1] = 1 ;
					}
					// 26 cas sur 26 :)
				}

			}
			else if(a=='y'&& b=='z' && c=='x'){
				if(ligne>1){
					if(!verif[y][z][x]){
						fprintf(stderr,"La structure de la forme est impossible, voir ligne fichier %d et ligne code %d\n", ligne, __LINE__);
						freeArray(array, TAILLE_MAX_PIECE, TAILLE_MAX_PIECE, TAILLE_MAX_PIECE) ;
						freeArray(verif, TAILLE_MAX_PIECE, TAILLE_MAX_PIECE, TAILLE_MAX_PIECE) ;
						return NULL ;
					}
				}

				if(y<TAILLE_MAX_PIECE && z<TAILLE_MAX_PIECE && x<TAILLE_MAX_PIECE){
					array[y][z][x] = 1 ;
					if((y-1)>=0 && (z-1)>= 0 && (x-1)>= 0){
						verif[y-1][z-1][x-1] = 1 ;
					}
					if((y-1)>=0 && (z-1)>=0){
						verif[y-1][z-1][x] = 1 ;
					}
					if((y-1)>=0 && (x-1)>=0){
						verif[y-1][z][x-1] = 1 ;
					}
					if((z-1)>=0 && (x-1)>=0){
						verif[y][z-1][x-1] = 1 ;
					}
					if((z-1)>=0){
						verif[y][z-1][x] = 1 ;
					}
					if((x-1)>=0){
						verif[y][z][x-1] = 1 ;
					}
					if((y-1)>=0){
						verif[y-1][z][x] = 1 ;
					}
					// 7 cas sur 26 pour l'instant

					if((y+1)<TAILLE_MAX_PIECE && (z+1)<TAILLE_MAX_PIECE && (x+1)<TAILLE_MAX_PIECE){
						verif[y+1][z+1][x+1] = 1 ;
					}
					if((y+1)<TAILLE_MAX_PIECE && (z+1)<TAILLE_MAX_PIECE){
						verif[y+1][z+1][x] = 1 ;
					}
					if((y+1)<TAILLE_MAX_PIECE && (x+1)<TAILLE_MAX_PIECE){
						verif[y+1][z][x+1] = 1 ;
					}
					if((z+1)<TAILLE_MAX_PIECE && (x+1)<TAILLE_MAX_PIECE){
						verif[y][z+1][x+1] = 1 ;
					}
					if((z+1)<TAILLE_MAX_PIECE){
						verif[y][z+1][x] = 1 ;
					}
					if((x+1)<TAILLE_MAX_PIECE){
						verif[y][z][x+1] = 1 ;
					}
					if((y+1)<TAILLE_MAX_PIECE){
						verif[y+1][z][x] = 1 ;
					}
					// 14 cas sur 26 pour l'instant

					if((y-1)>=0 && (z-1)>=0 && (x+1)<TAILLE_MAX_PIECE){
						verif[y-1][z-1][x+1] = 1 ;
					}
					if((y-1)>=0 && (z+1)<TAILLE_MAX_PIECE && (x-1)>=0){
						verif[y-1][z+1][x-1] = 1 ;
					}
					if((y+1)<TAILLE_MAX_PIECE && (z-1)>=0 && (x-1)>=0){
						verif[y+1][z-1][x-1] = 1 ;
					}
					// 17 cas sur 26 

					if((y-1)>=0 && (z+1)<TAILLE_MAX_PIECE && (x+1)<TAILLE_MAX_PIECE){
						verif[y-1][z+1][x+1] = 1 ;
					}
					if((y+1)<TAILLE_MAX_PIECE && (z+1)<TAILLE_MAX_PIECE && (x-1)>=0){
						verif[y+1][z+1][x-1] = 1 ;
					}
					if((y+1)<TAILLE_MAX_PIECE && (z-1)>=0 && (x+1)<TAILLE_MAX_PIECE){
						verif[y+1][z-1][x+1] = 1 ;
					}
					// 20 cas sur 26 pour l'instant

					if((y-1)>=0 && (z+1)<TAILLE_MAX_PIECE){
						verif[y-1][z+1][x] = 1 ;
					}
					if((y+1)<TAILLE_MAX_PIECE && (x-1)>=0){
						verif[y+1][z][x-1] = 1 ;
					}
					if((y-1)>=0 && (x+1)<TAILLE_MAX_PIECE){
						verif[y-1][z][x+1] = 1 ;
					}
					if((y+1)<TAILLE_MAX_PIECE && (x-1)>=0){
						verif[y+1][z][x-1] = 1 ;
					}
					if((z-1)>=0 && (x+1)<TAILLE_MAX_PIECE){
						verif[y][z-1][x+1] = 1 ;
					}
					if((z+1)<TAILLE_MAX_PIECE && (x-1)>=0){
						verif[y][z+1][x-1] = 1 ;
					}
					// 26 cas sur 26 :)
				}

			}
			else if(a=='z'&& b=='y' && c=='x'){
				if(ligne>1){
					if(!verif[z][y][x]){
						fprintf(stderr,"La structure de la forme est impossible, voir ligne fichier %d et ligne code %d\n", ligne, __LINE__);
						freeArray(array, TAILLE_MAX_PIECE, TAILLE_MAX_PIECE, TAILLE_MAX_PIECE) ;
						freeArray(verif, TAILLE_MAX_PIECE, TAILLE_MAX_PIECE, TAILLE_MAX_PIECE) ;
						return NULL ;
					}

				}

				if(z<TAILLE_MAX_PIECE && y<TAILLE_MAX_PIECE && x<TAILLE_MAX_PIECE){
					array[z][y][x] = 1 ;
					if((z-1)>=0 && (y-1)>= 0 && (x-1)>= 0){
						verif[z-1][y-1][x-1] = 1 ;
					}
					if((z-1)>=0 && (y-1)>=0){
						verif[z-1][y-1][x] = 1 ;
					}
					if((z-1)>=0 && (x-1)>=0){
						verif[z-1][y][x-1] = 1 ;
					}
					if((y-1)>=0 && (x-1)>=0){
						verif[z][y-1][x-1] = 1 ;
					}
					if((y-1)>=0){
						verif[z][y-1][x] = 1 ;
					}
					if((x-1)>=0){
						verif[z][y][x-1] = 1 ;
					}
					if((z-1)>=0){
						verif[z-1][y][x] = 1 ;
					}
					// 7 cas sur 26 pour l'instant

					if((z+1)<TAILLE_MAX_PIECE && (y+1)<TAILLE_MAX_PIECE && (x+1)<TAILLE_MAX_PIECE){
						verif[z+1][y+1][x+1] = 1 ;
					}
					if((z+1)<TAILLE_MAX_PIECE && (y+1)<TAILLE_MAX_PIECE){
						verif[z+1][y+1][x] = 1 ;
					}
					if((z+1)<TAILLE_MAX_PIECE && (x+1)<TAILLE_MAX_PIECE){
						verif[z+1][y][x+1] = 1 ;
					}
					if((y+1)<TAILLE_MAX_PIECE && (x+1)<TAILLE_MAX_PIECE){
						verif[z][y+1][x+1] = 1 ;
					}
					if((y+1)<TAILLE_MAX_PIECE){
						verif[z][y+1][x] = 1 ;
					}
					if((x+1)<TAILLE_MAX_PIECE){
						verif[z][y][x+1] = 1 ;
					}
					if((z+1)<TAILLE_MAX_PIECE){
						verif[z+1][y][x] = 1 ;
					}
					// 14 cas sur 26 pour l'instant

					if((z-1)>=0 && (y-1)>=0 && (x+1)<TAILLE_MAX_PIECE){
						verif[z-1][y-1][x+1] = 1 ;
					}
					if((z-1)>=0 && (y+1)<TAILLE_MAX_PIECE && (x-1)>=0){
						verif[z-1][y+1][x-1] = 1 ;
					}
					if((z+1)<TAILLE_MAX_PIECE && (y-1)>=0 && (x-1)>=0){
						verif[z+1][y-1][x-1] = 1 ;
					}
					// 17 cas sur 26 

					if((z-1)>=0 && (y+1)<TAILLE_MAX_PIECE && (x+1)<TAILLE_MAX_PIECE){
						verif[z-1][y+1][x+1] = 1 ;
					}
					if((z+1)<TAILLE_MAX_PIECE && (y+1)<TAILLE_MAX_PIECE && (x-1)>=0){
						verif[z+1][y+1][x-1] = 1 ;
					}
					if((z+1)<TAILLE_MAX_PIECE && (y-1)>=0 && (x+1)<TAILLE_MAX_PIECE){
						verif[z+1][y-1][x+1] = 1 ;
					}
					// 20 cas sur 26 pour l'instant

					if((z-1)>=0 && (y+1)<TAILLE_MAX_PIECE){
						verif[z-1][y+1][x] = 1 ;
					}
					if((z+1)<TAILLE_MAX_PIECE && (x-1)>=0){
						verif[z+1][y][x-1] = 1 ;
					}
					if((z-1)>=0 && (x+1)<TAILLE_MAX_PIECE){
						verif[z-1][y][x+1] = 1 ;
					}
					if((z+1)<TAILLE_MAX_PIECE && (x-1)>=0){
						verif[z+1][y][x-1] = 1 ;
					}
					if((y-1)>=0 && (x+1)<TAILLE_MAX_PIECE){
						verif[z][y-1][x+1] = 1 ;
					}
					if((y+1)<TAILLE_MAX_PIECE && (x-1)>=0){
						verif[z][y+1][x-1] = 1 ;
					}
					// 26 cas sur 26 :)
				}
			}
			else if(a=='z'&& b=='x' && c=='y'){
				if(ligne>1){
					if(!verif[z][x][y]){
						fprintf(stderr,"La structure de la forme est impossible, voir ligne fichier %d et ligne code %d\n", ligne, __LINE__);
						freeArray(array, TAILLE_MAX_PIECE, TAILLE_MAX_PIECE, TAILLE_MAX_PIECE) ;
						freeArray(verif, TAILLE_MAX_PIECE, TAILLE_MAX_PIECE, TAILLE_MAX_PIECE) ;
						return NULL ;
					}
				}

				if(z<TAILLE_MAX_PIECE && x<TAILLE_MAX_PIECE && y<TAILLE_MAX_PIECE){
					array[z][x][y] = 1 ;
					if((z-1)>=0 && (x-1)>= 0 && (y-1)>= 0){
						verif[z-1][x-1][y-1] = 1 ;
					}
					if((z-1)>=0 && (x-1)>=0){
						verif[z-1][x-1][y] = 1 ;
					}
					if((z-1)>=0 && (y-1)>=0){
						verif[z-1][x][y-1] = 1 ;
					}
					if((x-1)>=0 && (y-1)>=0){
						verif[z][x-1][y-1] = 1 ;
					}
					if((x-1)>=0){
						verif[z][x-1][y] = 1 ;
					}
					if((y-1)>=0){
						verif[z][x][y-1] = 1 ;
					}
					if((z-1)>=0){
						verif[z-1][x][y] = 1 ;
					}
					// 7 cas sur 26 pour l'instant

					if((z+1)<TAILLE_MAX_PIECE && (x+1)<TAILLE_MAX_PIECE && (y+1)<TAILLE_MAX_PIECE){
						verif[z+1][x+1][y+1] = 1 ;
					}
					if((z+1)<TAILLE_MAX_PIECE && (x+1)<TAILLE_MAX_PIECE){
						verif[z+1][x+1][y] = 1 ;
					}
					if((z+1)<TAILLE_MAX_PIECE && (y+1)<TAILLE_MAX_PIECE){
						verif[z+1][x][y+1] = 1 ;
					}
					if((x+1)<TAILLE_MAX_PIECE && (y+1)<TAILLE_MAX_PIECE){
						verif[z][x+1][y+1] = 1 ;
					}
					if((x+1)<TAILLE_MAX_PIECE){
						verif[z][x+1][y] = 1 ;
					}
					if((y+1)<TAILLE_MAX_PIECE){
						verif[z][x][y+1] = 1 ;
					}
					if((z+1)<TAILLE_MAX_PIECE){
						verif[z+1][x][y] = 1 ;
					}
					// 14 cas sur 26 pour l'instant

					if((z-1)>=0 && (x-1)>=0 && (y+1)<TAILLE_MAX_PIECE){
						verif[z-1][x-1][y+1] = 1 ;
					}
					if((z-1)>=0 && (x+1)<TAILLE_MAX_PIECE && (y-1)>=0){
						verif[z-1][x+1][y-1] = 1 ;
					}
					if((z+1)<TAILLE_MAX_PIECE && (x-1)>=0 && (y-1)>=0){
						verif[z+1][x-1][y-1] = 1 ;
					}
					// 17 cas sur 26 

					if((z-1)>=0 && (x+1)<TAILLE_MAX_PIECE && (y+1)<TAILLE_MAX_PIECE){
						verif[z-1][x+1][y+1] = 1 ;
					}
					if((z+1)<TAILLE_MAX_PIECE && (x+1)<TAILLE_MAX_PIECE && (y-1)>=0){
						verif[z+1][x+1][y-1] = 1 ;
					}
					if((z+1)<TAILLE_MAX_PIECE && (x-1)>=0 && (y+1)<TAILLE_MAX_PIECE){
						verif[z+1][x-1][y+1] = 1 ;
					}
					// 20 cas sur 26 pour l'instant

					if((z-1)>=0 && (x+1)<TAILLE_MAX_PIECE){
						verif[z-1][x+1][y] = 1 ;
					}
					if((z+1)<TAILLE_MAX_PIECE && (x-1)>=0){
						verif[z+1][x-1][y] = 1 ;
					}
					if((z-1)>=0 && (y+1)<TAILLE_MAX_PIECE){
						verif[z-1][x][y+1] = 1 ;
					}
					if((z+1)<TAILLE_MAX_PIECE && (y-1)>=0){
						verif[z+1][x][y-1] = 1 ;
					}
					if((x-1)>=0 && (y+1)<TAILLE_MAX_PIECE){
						verif[z][x-1][y+1] = 1 ;
					}
					if((x+1)<TAILLE_MAX_PIECE && (y-1)>=0){
						verif[z][x+1][y-1] = 1 ;
					}
					// 26 cas sur 26 :)
				}

			}
			else{
				fprintf(stderr,"Le format de la ligne %d est incorrecte\n", ligne);
				freeArray(array, TAILLE_MAX_PIECE, TAILLE_MAX_PIECE, TAILLE_MAX_PIECE) ;
				freeArray(verif, TAILLE_MAX_PIECE, TAILLE_MAX_PIECE, TAILLE_MAX_PIECE) ;
				return NULL ;
			}
			ligne++ ;
		}
		delete[] chaine ;
		fclose(file) ;
		freeArray(verif, TAILLE_MAX_PIECE, TAILLE_MAX_PIECE, TAILLE_MAX_PIECE) ;
	}
	return array ;
}

int main(){
	int*** x = file_to_array((char*)"form9.txt") ;
	for(int i=0;i<TAILLE_MAX_PIECE;i++){
		for(int j=0;j<TAILLE_MAX_PIECE;j++){
			for(int k=0;k<TAILLE_MAX_PIECE;k++){
				printf("%d\n", x[i][j][k]); 
			}
		}
	}
	return 0 ;
}