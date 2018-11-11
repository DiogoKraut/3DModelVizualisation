/* DIOGO PARIS KRAUT - GRR20166365 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "datatypes.h"

void convertToPerspective(int *camera, tVertexList *vl);
void convertToScreenCoord(tVertexList *vl);
void findMaxMin(tVertexList *vl, float *max, float *min, int coord);
