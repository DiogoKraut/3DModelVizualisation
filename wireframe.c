/* DIOGO PARIS KRAUT - GRR20166365 */

#include <stdio.h>
#include <stdlib.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>

#include "datatypes.h"
#include "objread.h"

int main(int argc, char const *argv[])
{
	char file_path[MAX_FILE];
	if(argc <= 1)
		fgets(file_path, MAX_FILE, stdin);
	else
		file_path = argv[argc];



	return 0;
}
