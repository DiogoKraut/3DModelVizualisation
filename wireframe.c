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

	tVertexList *vl = init_VertexList()
	tFaceList   *fl = malloc(sizeof(tFaceList));
	if(!vertex_list || !face_list) {
		fprintf(stderr, "Falha ao alocar espaco para OBJ\n");
		exit(EXIT_FAILURE);

	vl->tam = fl->tam = 0;

	FILE *in = fopen(file_path, "r");
	readOBJ(in, vl, fl);
	fclose(in);

	int camera[DIMENSION];
	camera[x] = 0;
	camera[Y] = 0;
	camera[Z] = 10;

	convertToPerspective(camera, vl);


	return 0;
}
