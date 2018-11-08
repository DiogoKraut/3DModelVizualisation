/* DIOGO PARIS KRAUT - GRR20166365 */

#define DIMENSION 3
#define FACE_SIZE 16

#define X 0
#define Y 1
#define Z 2

#define MAX_FACES 69451 * 2
#define MAX_VERTEX 34834 * 2

#define MAX_FILE 30

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
