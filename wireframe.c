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
	camera[X] = 5;
	camera[Y] = 0;
	camera[Z] = 2;

	convertToPerspective(camera, vl);
	convertToScreenCoord(vl);

	if(SDL_Init(SDL_INIT_EVENTS | SDL_INIT_VIDEO)) {
		fprintf(stderr, "Error em SDL_Init: %s", SDL_GetError());
		exit(EXIT_FAILURE);
	}

	SDL_Window *win = SDL_CreateWindow(
		"Main window",
		0,
		0,
		WIN_WIDTH,
		WIN_HEIGHT,
		SDL_WINDOW_INPUT_GRABBED | SDL_WINDOW_OPENGL
	);
	if(win == NULL) {
		printf ("Erro em SDL_CreateWindow: %s", SDL_GetError());
		SDL_Quit();
		exit(EXIT_FAILURE);
	}

	SDL_Renderer *renderer = SDL_CreateRenderer(
		win,
		-1,
		SDL_RENDERER_ACCELERATED
	);
	if(renderer == NULL) {
		SDL_DestroyWindow(win);
		printf ("Erro em SDL_CreateRenderer: %s", SDL_GetError());
		SDL_Quit();
		exit(EXIT_FAILURE);
}
	SDL_Event e;

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 100);

	int quit = 0;
	while(!quit) {
	  if(SDL_PollEvent(&e)) {
			if(e.type == SDL_QUIT)
				quit = 1;
			else if(e.type == SDL_KEYDOWN) {
				switch(e.key.keysym.sym) {
					case SDLK_UP:
						camera[Z]++;
						break;
					case SDLK_DOWN:
						camera[Z]--;
						break;
					case SDLK_RIGHT:
						camera[X]++;
						break;
					case SDLK_LEFT:
						camera[X]--;
						break;
					case SDLK_SPACE:
						camera[Y]++;
						break;
					case SDLK_LCTRL:
						camera[Y]--;
						break;
				}
				convertToPerspective(camera, vl);
				convertToScreenCoord(vl);
			}
		}
		SDL_RenderClear(renderer);
		drawEdges(renderer, vl, fl);
		SDL_RenderPresent(renderer);
	}

	SDL_DestroyWindow(win);
	SDL_Quit();
	free(vl);
	free(fl);
	return 0;
}
