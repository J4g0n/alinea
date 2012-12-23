#include "resol.h"
#include <stdio.h>
#include <stdlib.h>

/* Calcul la comatrice d'une matrice m donnée en entrée
 */
Matrix comat(Matrix m) 
{
	int i,j;
	Matrix matTmp;
	Matrix m0=newMatrix(m->nb_rows,m->nb_columns);
	if(isSquare(m0))
	{
		int n=m0->nb_columns;
		for(i=0;i<n;i++)
		{
			for(j=0;j<n;j++)
			{
				matTmp=extraction(m,i,j);
				if((i+j)%2==0) 
					m0->mat[i*n+j]=m_detGauss(matTmp);
				else 
					m0->mat[i*n+j]=-m_detGauss(matTmp);
				deleteMatrix(matTmp);
			}
		}
	}
	return m0;
}

Matrix inverseComat(Matrix m)
{
	int i,j;
	Matrix m0=transpose(comat(m));
	E det=m_detGauss(m);
	int n = m->nb_columns;
	if(det!=0)
	{
		for(i=0;i<n;i++)
		{
			for(j=0;j<n;j++)
				m0->mat[i*n+j]=m0->mat[i*n+j]/det;
		}
	}
	return m0;
}

/* Attention cette fonction transforme la matrice m pendant qu'elle
 * calcule l'inverse il faut tout d'abord effectuer une copie de la
 * matrice m avant d'appeler la fonction 
 */
Matrix inverseGauss(Matrix m)
{
	Matrix inv;
	int i,j;
	E f;
	int column=m->nb_columns;
	int row=m->nb_rows;
	//premiere partie reprise de l'algorithme de gauss avec modifications
	//appliquées sur la matrice identité
	if(isSquare(m))
	{
		inv=identite(row,column);
		for(i=0;i<row;i++)
		{
			for(j=i+1;j<row;j++)
			{
				if(m->mat[i*column+i]==0)
				{
					int k;
					for(k=j;k<row;k++)
					{
						if(m->mat[k*column+i]!=0) 
						{
							m=permuter(m,i,k);
							inv=permuter(inv,i,k);
							break;
						}
					}
				}
				f=-(m->mat[j*column+i]/m->mat[i*column+i]);
				m=addMulLigne(m,f,i,j);
				inv=addMulLigne(inv,f,i,j);
			}
		}
	}
	//deuxieme partie on met la diagonale à 1
	for(i=0;i<row;i++)
	{
		if((m->mat[i*column+i])!=0)
		{
			f=1/m->mat[i*column+i];
			inv=mulLigne(inv,f,i);
			m=mulLigne(m,f,i);
		}
	}
	//troisieme partie remontée de l'algorithme de gauss
	for(;i>=0;--i)
	{
		for(j=i-1;j>=0;j--)
		{
			E coef=m->mat[i*column+i];
			if(coef!=0)
			{
				f=-(m->mat[j*column+i]/coef);
				inv=addMulLigne(inv,f,i,j);
				m=addMulLigne(m,f,i,j);
			}
		}
	}
	return inv;
}

Matrix resol(Matrix m,Matrix m2)
{
	int i,j;
	E f;
	int column=m->nb_columns;
	int row=m->nb_rows;
	//premiere partie reprise de l'algorithme de gauss avec modifications
	//appliquées sur la matrice matrice résultat
	if(isSquare(m))
	{
		for(i=0;i<row;i++)
		{
			for(j=i+1;j<row;j++)
			{
				if(m->mat[i*column+i]==0)
				{
					int k;
					for(k=j;k<row;k++)
					{
						if(m->mat[k*column+i]!=0) 
						{
							m=permuter(m,i,k);
							m2=permuter(m2,i,k);
							break;
						}
					}
				}
				f=-(m->mat[j*column+i]/m->mat[i*column+i]);
				m=addMulLigne(m,f,i,j);
				m2=addMulLigne(m2,f,i,j);
			}
		}
	}
	//deuxieme partie on met la diagonale à 1
	for(i=0;i<row;i++)
	{
		if((m->mat[i*column+i])!=0)
		{
			f=1/m->mat[i*column+i];
			m2=mulLigne(m2,f,i);
			m=mulLigne(m,f,i);
		}
	}
	//troisieme partie remontée de l'algorithme de gauss
	for(;i>=0;--i)
	{
		for(j=i-1;j>=0;j--)
		{
			E coef=m->mat[i*column+i];
			if(coef!=0)
			{
				f=-(m->mat[j*column+i]/coef);
				m2=addMulLigne(m2,f,i,j);
				m=addMulLigne(m,f,i,j);
			}
		}
	}
	return m2;
}

// Attention cette fonction modifie par effet de bord les matrices P, L et
// U et ne renvoit que la matrice U obtenue
Matrix plu(Matrix A,Matrix P, Matrix L, Matrix U)
{
	// TODO: s'assurer que A n'a aucune valeur nulle sur sa diagonale et
	// effectuer les permutations nécessaires le cas échéant
	int i,j,k;
	E val;
	int column=A->nb_columns;
	int row=A->nb_rows;
	for(i=0;i<row;i++)
	{
		if(A->mat[i*column+i]==0)
		{
			for(j=0;j<row;j++)
			{
				if(A->mat[j*column+i]!=0)
				{
					permuter(A,i,j);
					permuter(P,i,j);
					break;
				}
			}
		}
	}
	U->mat[0]=A->mat[0];
	// on remplit la colonne un de la matrice L et la ligne un de la
	// matrice U
	for(i=1;i<column;i++)
	{
		U->mat[i]=A->mat[i];
		L->mat[i*column]=A->mat[i*column]/A->mat[0];
	}
	// on remplit les autres colonnes et lignes de L et U respectivement
	for(i=1;i<row-1;i++)
	{
		for(k=0,val=0;k<i;k++)
			val+=L->mat[i*column+k]*U->mat[k*column+i];
		U->mat[i*column+i]=A->mat[i*column+i]-val;
		for(j=i+1;j<row;j++)
		{
			for(k=0,val=0;k<i;k++)
				val+=L->mat[i*column+k]*U->mat[k*column+j];
			U->mat[i*column+j]=A->mat[i*column+j]-val;
			for(k=0,val=0;k<i;k++)
				val+=L->mat[j*column+k]*U->mat[k*column+i];
			L->mat[j*column+i]=(A->mat[j*column+i]-val)/U->mat[i*column+i];
		}
	}
	for(k=0,val=0;k<i;k++)
		val+=L->mat[i*column+k]*U->mat[k*column+i];
	U->mat[i*column+i]=A->mat[i*column+i]-val;
	return U;
}
