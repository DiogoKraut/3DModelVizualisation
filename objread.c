/* DIOGO PARIS KRAUT - GRR20166365 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "datatypes.h"
#include "objread.h"

void readOBJ(FILE *in, tVertex *vertex_list, tFace *face_list) {
	int vi, fi, i, aux;
	vi = fi = 0; // Indice da lista de vertices e faces

	char s[MAX_READ_SIZE];
	fgets(s, MAX_READ_SIZE, in);

	while(s != NULL) {
		strtok(s, " "); // Seleciona substring antes do primeiro ' '

		/* Verifica se a substring eh vertice ou face */
		switch(*s) {
			/* Vertice */
			case 'v':
				/* Ler as coordenadas do vertice */
				for(i = 0; i < DIMENSION; i++) {
					strtok(NULL, " ");
					vertex_list[vi].pos[i] = atof(s);
				}
				vi++;
				break;
			/* Face */
			case 'f':
				/* Ler os vertices da face */
				for(i = 0; strtok(NULL, " ") != NULL; i++) {
					aux = atoi(s) - 1; // Lista de vertices comeca em 1
					face_list[fi].vx[i] = aux;
				}
				fi++;
				break;
		}
		fgets(s, MAX_READ_SIZE, in);
	}
}
