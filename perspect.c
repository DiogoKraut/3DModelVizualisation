/* DIOGO PARIS KRAUT - GRR20166365 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>

#include "datatypes.h"
#include "perspect.h"
#include "graphics.h"

/* Perspectiva fraca. Salva o resultado em outra lista de vertices */
void convertToPerspective(double *camera, tVertexList *vl1, tVertexList *vl2) {
	int i;
	double aux;
	for(i = 0; i < vl1->size; i++) {
		aux = vl1->vertex[i][Z] + camera[Z]; // (Zv + Zc)
		vl2->vertex[i][X] = camera[X] + camera[Z] * ((vl1->vertex[i][X] - camera[X]) / aux);
		vl2->vertex[i][Y] = camera[Y] + camera[Z] * ((vl1->vertex[i][Y] - camera[Y]) / aux);
	}
	vl2->size = i;
}

/* Encontra o maximo e minimo da coordenada 'coord' em uma lista de vertices */
void findMaxMin(tVertexList *vl, double *max, double *min, int coord) {
	int i;
	*max = *min = 0;

	for(i = 0; i < vl->size; i++) {
		if(vl->vertex[i][coord] > *max)
			*max = vl->vertex[i][coord];
		else if(vl->vertex[i][coord] < *min)
			*min = vl->vertex[i][coord];
	}
}

/* Coverta as coordenadas cartesianas dos vertices para coordenadas de tela */
void convertToScreenCoord(tVertexList *vl) {
	int i;
	/* Passo 1: Mins, maxs, centros e difs */
	double maxY, maxX, minY, minX, cY, cX;
	findMaxMin(vl, &maxX, &minX, X);
	findMaxMin(vl, &maxY, &minY, Y);

	cX = (maxX + minX) / 2;
	cY = (maxY + minY) / 2;

	/* Passo 2: Fator de escala*/
	double sclX, sclY, scl;
	sclX = WIN_WIDTH  / (maxX - minX);
	sclY = WIN_HEIGHT / (maxY - minY);

	scl = sclX < sclY ? sclX : sclY;
	// scl = scl/2;
	/* Passos 3 a 5: Ajustar escala e posicao na tela */
	for(i = 0; i < vl->size; i++) {
		vl->vertex[i][X] = ((vl->vertex[i][X] - cX) * scl) + WIN_WIDTH / 2;
		vl->vertex[i][Y] = ((vl->vertex[i][Y] - cY) * scl) + WIN_HEIGHT / 2;
	}
}

void cameraToCartesian(double *x, double*y, double *theta, double dist) {
	double t;
	/* Converter theta para radianos */
	t = (double) *theta * M_PI / 180.0;
	/* Converter para coordenadas cartesianas */
	x = dist * cos(t);
	y = dist * sin(t);
}
