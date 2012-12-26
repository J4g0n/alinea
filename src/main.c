#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "interface.h"
#include "matrice.h"
#include "gauss.h"
#include "resol.h"

int 
main () 
{
	srand(time(NULL));
	int bouton;
	
	while((bouton=menu())!=0)
	{
		switch(bouton)
		{
			case 1:
				menuOperation();
				break;
			case 2:
				menuResolution();
				break;
			case 3:
				menuInversion();
				break;
			case 4:
				menuDecomposition();
				break;
			default:
				printf("\nAucune action n'est associée à ce numéro!\n");
		}
	}
	return 0;
}
		

