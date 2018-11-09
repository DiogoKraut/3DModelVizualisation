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
		/* Mais espaco para listas, se nescessario */
		if(vl->size == vl->max_size) {
			vl->max_size *= 2;
			vl->vertex = realloc(vl->vertex, sizeof(tVertex) * vl->max_size);
		}
		if(fl->size == fl->max_size) {
			fl->max_size *= 2;
			fl->face = realloc(fl->face, sizeof(tFace) * fl->max_size);
		}
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
				strtok(s, " "); // Seleciona 'f'
				/* Ler os vertices da face */
				for(i = 0; strtok(NULL, " ") != NULL; i++) {
					aux = atoi(s) - 1; // Lista de vertices comeca em 1
					fl->face[fl->size][i] = aux;
				}
				fl->size++;
				break;
		}
	}
}
