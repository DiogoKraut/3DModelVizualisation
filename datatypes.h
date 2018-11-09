/* DIOGO PARIS KRAUT - GRR20166365 */

#ifndef __TYPES__
#define __TYPES__

#define DIMENSION 3
#define FACE_SIZE 16

#define X 0
#define Y 1
#define Z 2

#define MAX_FACES  500
#define MAX_VERTEX 500

#define MAX_FILE 50
#define MAX_LINE 50

typedef float tVertex[DIMENSION];
typedef int tFace[FACE_SIZE];

typedef struct sVertexList {
	tVertex *vertex;
	int size, max_size;
} tVertexList;

typedef struct sFaceList {
	tFace *face;
	int size, max_size;
} tFaceList;

#endif
