/* DIOGO PARIS KRAUT - GRR20166365 */

#include <stdio.h>
#include <stdlib.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>

#include "datatypes.h"
#include "objread.h"
#include "graphics.h"
#include "perspect.h"

int main(int argc, char const *argv[])
{
	char file_path[MAX_FILE];
	if(argc <= 1)
		fgets(file_path, MAX_FILE, stdin);
	else
		file_path = argv[argc];

	tVertex *vertex_list = malloc(sizeof(tVertex) * MAX_VERTIXES);
	tFace *face_list     = malloc(sizeof(tFace) * MAX_FACES);
	if(!vertex_list || !face_list) {
		fprintf(stderr, "Falha ao alocar espaco para OBJ\n");
		exit(EXIT_FAILURE);
	}

	FILE *in = fopen(file_path, "r");
	readOBJ(in, vertex_list, face_list);
	fclose(in);

	int camera[DIMENSION];
	camera[x] = 0;
	camera[Y] = 0;
	camera[Z] = 10;

	convertToPerspective(camera, vertex_list);


	return 0;
}
