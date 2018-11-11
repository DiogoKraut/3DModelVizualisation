/* DIOGO PARIS KRAUT - GRR20166365 */

#ifndef __TYPES__
#define __TYPES__

#define DIMENSION 3
#define FACE_SIZE 6

#define X 0
#define Y 1
#define Z 2

#define MAX_FACES 100
#define MAX_VERTEX 100

#define MAX_LINE 50

typedef float tVertex[DIMENSION];
typedef int tFace[FACE_SIZE];

typedef struct sVertexList {
	tVertex vertex[MAX_VERTEX];
	int size;
} tVertexList;

typedef struct sFaceList {
	tFace face[MAX_FACES];
	int size;
} tFaceList;

#endif
