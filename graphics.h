/* DIOGO PARIS KRAUT - GRR20166365 */

#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>

#include "datatypes.h"

#define WIN_WIDTH 400
#define WIN_HEIGHT 300

void drawEdges(SDL_Renderer *renderer, tVertexList *vl, tFaceList *fl);
