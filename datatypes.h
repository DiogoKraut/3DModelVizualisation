/* DIOGO PARIS KRAUT - GRR20166365 */

#ifndef __TYPES__
#define __TYPES__

#define DIMENSION 3
#define FACE_SIZE 6

#define X 0
#define Y 1
#define Z 2

#define MAX_FACES 65536   // 2^16
#define MAX_VERTEX 131072 // 2^17

#define MAX_LINE 50

typedef double t3dVertex[DIMENSION];
typedef double t2dVertex[DIMENSION-1];
typedef int tFace[FACE_SIZE];

typedef struct sCamera {
	t3dVertex pos;
	t3dVertex surface; // Superficie onde sera feita a projecao em relacao a camera
} tCamera;

typedef struct s3dVertexList {
	t3dVertex vertex[MAX_VERTEX];
	int size;
} t3dVertexList;

typedef struct s2dVertexList {
	t2dVertex vertex[MAX_VERTEX];
	int size;
} t2dVertexList;

typedef struct sFaceList {
	tFace face[MAX_FACES];
	int size;
} tFaceList;

#endif
