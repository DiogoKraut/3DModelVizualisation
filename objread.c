/* DIOGO PARIS KRAUT - GRR20166365 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "datatypes.h"
#include "objread.h"

/* Recebe uma linha do arquivo .obj e a processa de acordo */
void readOBJ(char *s, tVertexList *vl, tFaceList *fl) {
	int i, aux;
	char *tok, *toktok;
	char *stoktok;

	tok = strtok(s, " ");
	/* Verifica se eh vertice ou face */
	switch(*tok) {
		/* Vertice */
		case 'v':
			/* Ler as coordenadas do vertice */
			for(i = 0; i < DIMENSION; i++) {
				tok = strtok(NULL, " ");
				vl->vertex[vl->size][i] = atof(tok);
			}
			vl->size++;
			break;
		/* Face */
		case 'f':
			/* Ler os vertices da face */
			tok = strtok(NULL, " ");
			for(i = 0; tok != NULL; i++) {
				toktok = strtok_r(tok, "/", &stoktok);
				aux = atoi(toktok);
				/* Listas num arv .obj comecam em 1, ajustamos para comecar em 0 */
				fl->face[fl->size][i] = aux - 1;
				tok = strtok(NULL, " ");
			}
			fl->size++;
			break;
	}
}

/* Inicializa lista de faces em -1, uma vez que a lista de vertices nao possui *
 * este indice. Posteriormente, se -1 for lido indica o fim da face */
void init_faceList(tFaceList *fl) {
	int i, j;
	for(i = 0; i < MAX_FACES; i++)
		for(j = 0; j < FACE_SIZE; j++) {
			fl->face[i][j] = -1;
		}
}
