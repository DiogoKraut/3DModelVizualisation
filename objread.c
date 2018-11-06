/* DIOGO PARIS KRAUT - GRR20166365 */

#include <stdio.h>

#include "datatypes.h"
#include "objread.h"

void readOBJ(FILE *in, tVertex *vertex_list, tFace *face_list) {
	int vi, fi, i;
	vi = fi = 0; // Indice da lista de vertices e faces
	
	char *s = malloc(MAX_READ_SIZE);
	fgets(s, MAX_READ_SIZE, in);

	while(s != NULL) {
		strtok(s, " "); // Seleciona substring antes do primeiro ' '

		/* Verifica se a substring eh vertice ou face */
		switch(*s) {
			case 'v':     // Vertice
				/* Ler as coordenadas do vertice */
				for(i = 0; i < DIMENSION; i++) {
					strtok(NULL, " ");
					vertex_list[vi]->pox[i] = atof(s);
				}
				vi++;
				break;

			case 'f':     // Face
				/* Ler os vertices da face */
				for(i = 0; strtok(NULL, " ") != NULL; i++) {
					face_list[fi].vx[i] = atoi(s);
				}
				fi++;
				break;
		}
		fgets(s, MAX_READ_SIZE, in);
	}
}