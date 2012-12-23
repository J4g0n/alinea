#ifndef __resol_h_
#define __resol_c_

#include "gauss.h"
#include "matrice.h"

Matrix comat(Matrix);
Matrix inverseComat(Matrix);
Matrix inverseGauss(Matrix);
Matrix resol(Matrix,Matrix);

Matrix plu(Matrix A, Matrix P, Matrix L, Matrix U);

#endif
