/* DIOGO PARIS KRAUT - GRR20166365 */

#define DIMENSION 3
#define FACE_SIZE 16

#define X 0
#define Y 1
#define Z 2

#define MAX_FACES 69451 * 2
#define MAX_VERTIXES 34834 * 2

typedef strct sVertex {
	float pos[DIMENSION];
} tVertex;

typedef struct sFace {
	int vx[FACE_SIZE];
} tFace;

