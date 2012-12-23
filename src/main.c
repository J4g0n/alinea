#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "matrice.h"
#include "gauss.h"
#include "resol.h"


int 
main () 
{
	srand(time(NULL));
	
	int a;
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

	Matrix mult=multiplication(L,U);
	afficheMatrice(mult);

	return 0;
}
		

