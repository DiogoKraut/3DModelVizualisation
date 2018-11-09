/* DIOGO PARIS KRAUT - GRR20166365 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>

#include "datatypes.h"
#include "perspect.h"
#include "graphics.h"

void convertToPerspective(int *camera, tVertexList *vl) {
	int i;
	float aux;
	for(i = 0; i < vl->size; i++) {
		aux = vl->vertex[i][Z] + camera[Z]; // (Zv + Zc)
		vl->vertex[i][X] = camera[X] + camera[Z] * ((vl->vertex[i][X] - camera[X]) / aux);
		vl->vertex[i][Y] = camera[Y] + camera[Z] * ((vl->vertex[i][Y] - camera[Y]) / aux);
	}
}

void findMaxMin(tVertexList *vl, float *max, float *min, int coord) {
	int i;
	*max = *min = 0;

	for(i = 0; i < vl->size; i++) {
		if(vl->vertex[i][coord] > *max)
			*max = vl->vertex[i][coord];
		else if(vl->vertex[i][coord] < *min)
			*min = vl->vertex[i][coord];
	}
}

void convertToScreenCoord(tVertexList *vl) {
	int i;
	/* Passo 1: Mins, maxs, centros e difs */
	float maxY, maxX, minY, minX, cY, cX;
	findMaxMin(vl, &maxX, &minX, X);
	findMaxMin(vl, &maxY, &minY, Y);

	cX = (maxX + minX) / 2;
	cY = (maxY + minY) / 2;

	/* Passo 2: Fator de escala*/
	float sclX, sclY, scl;
	sclX = WIN_WIDTH  / (maxX - minX);
	sclY = WIN_HEIGHT / (maxY - minY);

	scl = sclX < sclY ? sclX : sclY;

	/* Passos 3 a 5: Ajustar escala e posicao na tela */
	for(i = 0; i < vl->size; i++) {
		vl->vertex[i][X] = ((vl->vertex[i][X] - cX) * scl) + WIN_WIDTH;
		vl->vertex[i][Y] = ((vl->vertex[i][Y] - cY) * scl) + WIN_HEIGHT;
	}
}
