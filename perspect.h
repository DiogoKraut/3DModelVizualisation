/* DIOGO PARIS KRAUT - GRR20166365 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "datatypes.h"

void convertToPerspective(tCamera *camera, t3dVertexList *vl1, t2dVertexList *vl2);
void convertToScreenCoord(t2dVertexList *vl);
void findMaxMin(t2dVertexList *vl, double *max, double *min, int coord);
void cameraToCartesian(tCamera *camera, double *theta, double *phi, double dist);
