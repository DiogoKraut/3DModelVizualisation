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
	vl->vertex = malloc(sizeof(tVertex) * LIST_SIZE);
	fl->face   = malloc(sizeof(tFace) * LIST_SIZE);
	if(!vl->vertex || !fl->face) {
		fprintf(stderr, "Falha ao alocar espaco para OBJ\n");
		exit(EXIT_FAILURE);
	}

	vl->max_size = fl->max_size = LIST_SIZE;
	vl->size = fl->size = 0;

	FILE *in = fopen(file_path, "r");
	readOBJ(in, vl, fl);
	fclose(in);

	int camera[DIMENSION];
	camera[X] = 0;
	camera[Y] = 0;
	camera[Z] = 10;

	convertToPerspective(camera, vl);

	SDL_Init(SDL_INIT_EVENTS | SDL_INIT_VIDEO);

	SDL_Window *win;
	SDL_Renderer *renderer;
	SDL_CreateWindowAndRenderer(
		WIN_HEIGHT,
		WIN_WIDTH,
		SDL_WINDOW_INPUT_GRABBED,
		&win,
		&renderer
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

	free(vl->vertex);
	free(fl->face);
	free(vl);
	free(fl);
	return 0;
}
