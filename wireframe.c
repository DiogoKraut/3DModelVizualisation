/* DIOGO PARIS KRAUT - GRR20166365 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>

#include "datatypes.h"
#include "objread.h"
#include "graphics.h"
#include "perspect.h"

int main(int argc, char const *argv[]) {
	/* Inicializacao das estruturas que armazenarao um .obj */
	t3dVertexList *vl1 = malloc(sizeof(t3dVertexList));
	t2dVertexList *vl2 = malloc(sizeof(t2dVertexList));
	tFaceList   *fl = malloc(sizeof(tFaceList));
	if(!vl1 || !vl2 || !fl) {
		fprintf(stderr, "Falha ao alocar espaco para OBJ\n");
		exit(EXIT_FAILURE);
	}
	vl1->size = fl->size = 0;
	init_faceList(fl);

	/* Carrega o .obj em memoria */
	char s[MAX_LINE];
	if(argc == 2) { // Se .obj foi passado em argv
		FILE *in = fopen(argv[1], "r");
		while(fgets(s, MAX_LINE, in)) // Ler arqv linha por linha ate o fim
			readOBJ(s, vl1, fl);
		fclose(in);
	} else          // .obj passado por stdin
		while(fgets(s, MAX_LINE, stdin))
			readOBJ(s, vl1, fl);

	/* Inicializa camera */
	tCamera *camera = malloc(sizeof(tCamera));
	camera->surface[X] = 0;
	camera->surface[Y] = 0;
	camera->surface[Z] = 10;
	// Camera em coords esfericas (graus)
	double theta = 90;   // angulo a partir do eixo y
	double phi   = 0.0;   // angulo a partir do eixo z
	double dist  = 100.0;

	// Camera em coordenadas cartesianas
	cameraToCartesian(camera, &theta, &phi, dist);

	/* Calculo da projecao inicial */
	convertToPerspective(camera, vl1, vl2);
	convertToScreenCoord(vl2);

	/* Inicializacao de SDL */
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

	SDL_Event e;  // Strutura para tratar eventos
	int quit = 0;
	int mouse_x1, mouse_x2, mouse_y1, mouse_y2;

	while(!quit) {
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 100); // Background
		SDL_RenderClear(renderer);
		drawEdges(renderer, vl2, fl); // Desenha arestas do objeto
		SDL_RenderPresent(renderer);  // Refresh

		SDL_GetMouseState(&mouse_x1, &mouse_y1);

		/* Verificacao de eventos */
	  while(SDL_PollEvent(&e) != 0) {
			if(e.type == SDL_QUIT) // Sair
				quit = 1;
			else if(e.type == SDL_KEYDOWN) // Tecla pressionada
				switch(e.key.keysym.sym) {   // Move a camera de acordo com a tecla
					case SDLK_UP:
						theta += 5;
						cameraToCartesian(camera, &theta, &phi, dist);
						convertToPerspective(camera, vl1, vl2);
						convertToScreenCoord(vl2);
						break;
					case SDLK_DOWN:
						theta -= 5;
						cameraToCartesian(camera, &theta, &phi, dist);
						convertToPerspective(camera, vl1, vl2);
						convertToScreenCoord(vl2);
						break;
					case SDLK_RIGHT:
						phi += 5;
						cameraToCartesian(camera, &theta, &phi, dist);
						convertToPerspective(camera, vl1, vl2);
						convertToScreenCoord(vl2);
						break;
					case SDLK_LEFT:
						phi -= 5;
						cameraToCartesian(camera, &theta, &phi, dist);
						convertToPerspective(camera, vl1, vl2);
						convertToScreenCoord(vl2);
						break;
					case SDLK_ESCAPE:
							quit = 1;
						break;
				}
			else if((e.type == SDL_MOUSEMOTION) && (SDL_GetMouseState(&mouse_x2, &mouse_y2) & SDL_BUTTON_LMASK)) {
				/* SDL_GetMouseState retorna um bit mask do estado do botao e altera os paremetros *
				 * para a nova posicao do mouse. IF: Se moveu o mouse e MOUSE1 pressionado, move a *
				 * camera de acordo com a nova posicao do mouse em relacao a posicao antiga        */
				theta += mouse_x1 - mouse_x2;
				phi += mouse_y1 - mouse_y2;
				convertToPerspective(camera, vl1, vl2);
				convertToScreenCoord(vl2);
			}
		}
	}

	/* Free routine */
	SDL_DestroyWindow(win);
	SDL_Quit();
	free(vl1);
	free(fl);
	return 0;
}
