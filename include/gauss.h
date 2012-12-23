#ifndef __gauss_h_
#define __gauss_h_

#include "matrice.h"

E m_determinant(Matrix);
Matrix extraction(Matrix,int,int);

Matrix addMulLigne(Matrix,E,int,int);
Matrix mulLigne(Matrix,E,int);
Matrix permuter(Matrix,int,int);

Matrix gauss(Matrix);
E m_detGauss(Matrix);

#endif

