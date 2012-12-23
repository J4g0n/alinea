#ifndef __matrice_h_
#define __matrice_h_

typedef float E;
typedef struct matrix {
	E *mat;
	int nb_rows, nb_columns;
} *Matrix, strMatrix;

Matrix identite(int,int);
Matrix copie(Matrix m);
Matrix newMatrix(int, int);
E getElt(Matrix, int, int);
void setElt(Matrix, int, int, E);
void deleteMatrix(Matrix);
 
int isSymetric(Matrix); // 0 si faux
int isSquare(Matrix); // 0 si faux
Matrix transpose(Matrix);
Matrix addition(Matrix, Matrix);
Matrix multiplication(Matrix, Matrix); // NULL si incompatible
Matrix mult_scalaire(E, Matrix);

void afficheMatrice(Matrix);
Matrix fillMatrix(Matrix);

#endif
