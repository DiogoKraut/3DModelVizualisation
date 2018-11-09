/* DIOGO PARIS KRAUT - GRR20166365 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "datatypes.h"
#include "objread.h"

void readOBJ(FILE *in, tVertexList *vl, tFaceList *fl) {
	int i, aux;
	char s[MAX_LINE];
	char *tok;
	while(fgets(s, MAX_LINE, in)) {
		/* Verifica se a substring eh vertice ou face */
		switch(*s) {
			/* Vertice */
			case 'v':
				tok = strtok(s, " "); // Seleciona 'v'
				/* Ler as coordenadas do vertice */
				for(i = 0; i < DIMENSION; i++) {
					tok = strtok(NULL, " ");
					vl->vertex[vl->size][i] = atof(tok);
				}
				vl->size++;
				break;
			/* Face */
			case 'f':
				tok = strtok(s, " "); // Seleciona 'f'
				/* Ler os vertices da face */
				tok = strtok(NULL, " ");
				for(i = 0; tok != NULL; i++) {
					aux = atoi(tok); // Lista de vertices comeca em 0, mas no arquivo em 1
					fl->face[fl->size][i] = aux - 1;
					tok = strtok(NULL, " ");
				}
				fl->size++;
				break;
		}
	}
}

void init_faceList(tFaceList *fl) {
	int i, j;
	for(i = 0; i < MAX_FACES; i++)
		for(j = 0; j < FACE_SIZE; j++) {
			fl->face[i][j] = -1;
		}
}
