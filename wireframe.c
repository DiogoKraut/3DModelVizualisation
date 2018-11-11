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

	tVertexList *vl1 = malloc(sizeof(tVertexList));
	tVertexList *vl2 = malloc(sizeof(tVertexList));
	tFaceList   *fl = malloc(sizeof(tFaceList));
	if(!vl1 || !vl2 || !fl) {
		fprintf(stderr, "Falha ao alocar espaco para OBJ\n");
		exit(EXIT_FAILURE);
	}
	vl1->size = fl->size = 0;
	init_faceList(fl);

	FILE *in = fopen(file_path, "r");
	readOBJ(in, vl1, fl);
	fclose(in);

	float camera[DIMENSION];
	camera[X] = 0;
	camera[Y] = 0;
	camera[Z] = 2;

	convertToPerspective(camera, vl1, vl2);
	convertToScreenCoord(vl2);

	if(SDL_Init(SDL_INIT_EVENTS | SDL_INIT_VIDEO)) {
		fprintf(stderr, "Error em SDL_Init: %s", SDL_GetError());
		exit(EXIT_FAILURE);
	}

	SDL_Window *win = SDL_CreateWindow(
		"Main window",	0, 0,	WIN_WIDTH, WIN_HEIGHT,
		SDL_WINDOW_INPUT_GRABBED | SDL_WINDOW_OPENGL);
	if(win == NULL) {
		printf ("Erro em SDL_CreateWindow: %s", SDL_GetError());
		SDL_Quit();
		exit(EXIT_FAILURE);
	}

	SDL_Renderer *renderer = SDL_CreateRenderer(win, -1,	SDL_RENDERER_ACCELERATED);
	if(renderer == NULL) {
		SDL_DestroyWindow(win);
		printf ("Erro em SDL_CreateRenderer: %s", SDL_GetError());
		SDL_Quit();
		exit(EXIT_FAILURE);
}
	SDL_Event e;


	int quit = 0;
	while(!quit) {
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 100);
		SDL_RenderClear(renderer);
		drawEdges(renderer, vl2, fl);
		SDL_RenderPresent(renderer);
	  if(SDL_PollEvent(&e)) {
			if(e.type == SDL_QUIT)
				quit = 1;
			else if(e.type == SDL_KEYDOWN) {
				switch(e.key.keysym.sym) {
					case SDLK_DOWN:
						camera[Z] += 0.2;
						convertToPerspective(camera, vl1, vl2);
						convertToScreenCoord(vl2);
						break;
					case SDLK_UP:
						camera[Z] -= 0.2;
						convertToPerspective(camera, vl1, vl2);
						convertToScreenCoord(vl2);
						break;
					case SDLK_RIGHT:
						camera[X] += 0.2;
						convertToPerspective(camera, vl1, vl2);
						convertToScreenCoord(vl2);
						break;
					case SDLK_LEFT:
						camera[X] -= 0.2;
						convertToPerspective(camera, vl1, vl2);
						convertToScreenCoord(vl2);
						break;
					case SDLK_SPACE:
						camera[Y] += 0.2;
						convertToPerspective(camera, vl1, vl2);
						convertToScreenCoord(vl2);
						break;
					case SDLK_LCTRL:
						camera[Y] -= 0.2;
						convertToPerspective(camera, vl1, vl2);
						convertToScreenCoord(vl2);
						break;
						case SDLK_ESCAPE:
							quit = 1;
						break;
				}
			}
		}
	}

	SDL_DestroyWindow(win);
	SDL_Quit();
	free(vl1);
	free(fl);
	return 0;
}
