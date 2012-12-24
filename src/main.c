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
		printf("%d",bouton);
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
			default:
				printf("\nAucune action n'est associée à ce numéro!\n");
		}
	}
/*	int a;
	scanf("%d",&a);

	Matrix A=newMatrix(a,a);
	Matrix U=newMatrix(a,a);
	Matrix P=identite(a,a);
	Matrix L=identite(a,a);
	
	A=fillMatrix(A);
	afficheMatrice(A);
	
	U=plu(A, P, L, U);
	afficheMatrice(L);
	afficheMatrice(U);

	Matrix mult=multiplication(P,multiplication(L,U));
	afficheMatrice(mult);
*/
	return 0;
}
		

