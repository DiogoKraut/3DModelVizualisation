/* DIOGO PARIS KRAUT - GRR20166365 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>

#include "datatypes.h"
#include "objread.h"
#include "graphics.h"
#include "perspect.h"

int main(int argc, char const *argv[]) {
	char file_path[MAX_FILE];
	if(argc <= 1)
		fgets(file_path, MAX_FILE, stdin);
	else
		strcpy(file_path, argv[argc-1]);

	int i, j;

	tVertexList *vl = malloc(sizeof(tVertexList));
	tFaceList   *fl = malloc(sizeof(tFaceList));
	if(!vl || !fl) {
		fprintf(stderr, "Falha ao alocar espaco para OBJ\n");
		exit(EXIT_FAILURE);
	}
	vl->size = fl->size = 0;
	init_faceList(fl);

	FILE *in = fopen(file_path, "r");
	readOBJ(in, vl, fl);
	fclose(in);

	int camera[DIMENSION];
	camera[X] = 0;
	camera[Y] = 0;
	camera[Z] = 10;

	convertToPerspective(camera, vl);

	SDL_Init(SDL_INIT_EVENTS | SDL_INIT_VIDEO);

	SDL_Window *win = SDL_CreateWindow(
		"Main window",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		WIN_WIDTH,
		WIN_HEIGHT,
		SDL_WINDOW_INPUT_GRABBED
	);
	SDL_Renderer *renderer = SDL_CreateRenderer(
		win,
		-1,
		SDL_RENDERER_ACCELERATED
	);

	for(i = 0; i < fl->size; i++) {
		for(j = 0; fl->face[i][j+1] != -1; j++) {
			lineRGBA(renderer,
				       vl->vertex[fl->face[i][j]]   [X], // x1
			         vl->vertex[fl->face[i][j]]   [Y], // y1
							 vl->vertex[fl->face[i][j+1]] [X], // x2
							 vl->vertex[fl->face[i][j+1]] [Y], // y2
							 0, 0, 0, 100
						  );
		}
	}
	while(1);
	SDL_DestroyWindow(win);
	free(vl->vertex);
	free(fl->face);
	free(vl);
	free(fl);
	return 0;
}
