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

/* https://en.wikipedia.org/wiki/3D_projection#Weak_perspective_projection *
 * Algoritimo com base na secao Perspective Projection                     */
void convertToPerspective(tCamera *camera, t3dVertexList *vl1, t2dVertexList *vl2) {
	int i;
	double aux;
	t3dVertex d; // Coordenada do vertice em relacao a camera
	for(i = 0; i < vl1->size; i++) { // Percorre lista de vertices
		/* Calcular d */
		d[X] = vl1->vertex[i][X] - camera->pos[X];
		d[Y] = vl1->vertex[i][Y] - camera->pos[Y];
		d[Z] = vl1->vertex[i][Z] - camera->pos[Z];

		/* Calcular vertice em perspectiva */
		aux = camera->surface[Z] / d[Z]; // Ez / dz onde Ez == camera.surface[Z]

		vl2->vertex[i][X] = aux * d[X];
		vl2->vertex[i][Y] = aux * d[Y];
	}
	vl2->size = i;
}

/* Encontra o maximo e minimo da coordenada 'coord' em uma lista de vertices */
void findMaxMin(t2dVertexList *vl, double *max, double *min, int coord) {
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
void convertToScreenCoord(t2dVertexList *vl) {
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
	scl *= 0.8;
	// scl = scl/2;
	/* Passos 3 a 5: Ajustar escala e posicao na tela */
	for(i = 0; i < vl->size; i++) {
		vl->vertex[i][X] = ((vl->vertex[i][X] - cX) * scl) + WIN_WIDTH / 2;
		vl->vertex[i][Y] = ((vl->vertex[i][Y] - cY) * scl) + WIN_HEIGHT / 2;
	}
}

void cameraToCartesian(tCamera *camera, double *theta, double *phi, double r) {
	long double t, p;
	/* Converter theta para radianos */
	t = *theta * (M_PI / 180.0);
	p = *phi * (M_PI / 180.0);
	/* Converter para coordenadas cartesianas */
	camera->pos[X] = r * sin(t) * sin(p);
	camera->pos[Y] = r * cos(t);
	camera->pos[Z] = r * sin(t) * cos(p);
}
