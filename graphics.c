/* DIOGO PARIS KRAUT - GRR20166365 */

#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>

#include "datatypes.h"

void drawEdges(SDL_Renderer *renderer, tVertexList *vl, tFaceList *fl) {
	int i, j;
	for(i = 0; i < fl->size; i++) {
		for(j = 0; fl->face[i][j+1] != -1; j++) {
			lineRGBA(renderer,
							 vl->vertex[fl->face[i][j]]   [X], // x1
							 vl->vertex[fl->face[i][j]]   [Y], // y1
							 vl->vertex[fl->face[i][j+1]] [X], // x2
							 vl->vertex[fl->face[i][j+1]] [Y], // y2
							 255, 255, 255, 100
							);
		}
		lineRGBA(renderer,
						 vl->vertex[fl->face[i][j]] [X], // x1
						 vl->vertex[fl->face[i][j]] [Y], // y1
						 vl->vertex[fl->face[i][0]]   [X], // x2
						 vl->vertex[fl->face[i][0]]   [Y], // y2
						 255, 255, 255, 100
						);
	}
}
