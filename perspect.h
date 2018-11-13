/* DIOGO PARIS KRAUT - GRR20166365 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "datatypes.h"

void convertToPerspective(double *camera, tVertexList *vl1, tVertexList *vl2);
void convertToScreenCoord(tVertexList *vl);
void findMaxMin(tVertexList *vl, double *max, double *min, int coord);
void cameraToCartesian(double *camera, double *theta, double *phi, double dist);