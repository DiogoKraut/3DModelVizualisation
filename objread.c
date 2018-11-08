/* DIOGO PARIS KRAUT - GRR20166365 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "datatypes.h"
#include "objread.h"

void readOBJ(FILE *in, tVertexList *vl, tFaceList *fl) {
	int i, aux;
	char *s = NULL;

	while(getline(&s, 0, in)) {
		strtok(s, " "); // Seleciona substring antes do primeiro ' '

		/* Verifica se a substring eh vertice ou face */
		switch(*s) {
			/* Vertice */
			case 'v':
				/* Ler as coordenadas do vertice */
				for(i = 0; i < DIMENSION; i++) {
					strtok(NULL, " ");
					vl->vertex[vl->size][i] = atof(s);
				}
				vl->size++;
				break;
			/* Face */
			case 'f':
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
