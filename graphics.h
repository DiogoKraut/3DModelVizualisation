/* DIOGO PARIS KRAUT - GRR20166365 */

#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>

#include "datatypes.h"

#define WIN_WIDTH 800
#define WIN_HEIGHT 600

void drawEdges(SDL_Renderer *renderer, t2dVertexList *vl, tFaceList *fl);
