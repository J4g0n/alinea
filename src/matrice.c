#include "matrice.h"
#include <stdio.h>
#include <stdlib.h>

Matrix identite(int nbRows, int nbColumns)
{
	Matrix m;
	if(nbRows==nbColumns)
	{
		m=(newMatrix(nbRows,nbColumns));
		int i;
		for(i=0;i<nbRows;i++)
		{
			m->mat[i*nbColumns+i]=1;
		}
	}
	return m;
}

Matrix copie(Matrix m)
{
	Matrix m0=newMatrix(m->nb_rows,m->nb_columns);
	int i,j;
	int row=m->nb_rows;
	int column=m->nb_columns;
	for(i=0;i<row;i++)
	{
		for(j=0;j<column;j++)
		{
			m0->mat[i*column+j]=m->mat[i*column+j];
		}
	}
	return m0;
}

Matrix newMatrix(int nbRows, int nbColumns)
{
	Matrix m=(Matrix) malloc(sizeof(strMatrix));
	m->nb_rows=nbRows;
	m->nb_columns=nbColumns;
	m->mat=(E *) calloc(nbRows*nbColumns,sizeof(E));
	return m;
}

E getElt(Matrix m, int row, int column)
{
	if(m==NULL || m->nb_rows<=row || m->nb_columns<=column)
	{
		fprintf(stderr,"erreur matrice pas assez grande ou non définie\n");
		return 0.0;
	}
	else
	{
		return m->mat[row*m->nb_columns+column];
	}
}

void setElt(Matrix m, int row, int column, E val)
{
	if(m==NULL || m->nb_rows<=row || m->nb_columns<=column)
	{
		fprintf(stderr,"erreur matrice pas assez grande ou non définie\n");
	}
	else
	{
		m->mat[row*m->nb_columns+column]=val;
	}
}

void deleteMatrix(Matrix m)
{
	if(m!=NULL)
	{
		free(m->mat);
		free(m);
	}
}


int isSymetric(Matrix m)
{
	int Bool=1;
	if(m!=NULL)
	{
		int i,j;
		for(i=1;i<m->nb_rows;i++)
		{
			for(j=1;j<m->nb_columns;j++)
			{
				if(m->mat[i*m->nb_columns+j]!=m->mat[j*m->nb_rows+i]) 
				{
					Bool=0;
					break;
				}
			}
			if(Bool==0) break;
		}
	}
	return Bool;
}

int isSquare(Matrix	m)
{
	if(m==NULL)
	{	
		fprintf(stderr,"attention matrice non définie\n");
		return 0;
	}
	if(m->nb_columns==m->nb_rows) return 1;
	else return 0;
}

Matrix transpose(Matrix m)
{
	if((m!=NULL)&&(isSquare(m)))
	{
		E tmp;
		int i,j;
		int rows=m->nb_rows;
		int columns=m->nb_columns;
		for(i=0;i<rows;i++)
		{
			for(j=i+1;j<columns;j++)
			{
				tmp=m->mat[i*columns+j];
				m->mat[i*columns+j]=m->mat[j*columns+i];
				m->mat[j*columns+i]=tmp;
			}
		}
	}
	return m;
}

Matrix addition(Matrix m1, Matrix m2)
{
	Matrix m;
	int rows,columns;
	if((m1!=NULL)&&(m2!=NULL)&&((rows=m1->nb_rows)==m2->nb_rows)&&((columns=m1->nb_columns)==m2->nb_columns))
	{
		m=newMatrix(rows,columns);
		int i;
		for(i=0;i<rows*columns;i++)
		{
			m->mat[i]=m1->mat[i]+m2->mat[i];
		}
	}
	return m;
}

Matrix multiplication(Matrix m1, Matrix m2)
{
	Matrix m;
	if((m1!=NULL)&&(m2!=NULL)&&(m1->nb_columns==m2->nb_rows))
	{
		int rows=m1->nb_rows;
		int columns=m2->nb_columns;
		int n=m2->nb_rows;
		m=newMatrix(rows,columns);
		if(m!=NULL)
		{
			int i,j,k;
			for(i=0;i<rows;i++) // indice de ligne de m1
			{
				for(j=0;j<columns;j++) // indice de colonne de m2
				{
					for(k=0;k<n;k++)
					{
						m->mat[i*columns+j]+=m1->mat[i*n+k]*m2->mat[k*columns+j];
					}
				}
			}
		}
	}
	return m;
}

Matrix mult_scalaire(E reel, Matrix m)
{
	if(m!=NULL)
	{
		int i;
		for(i=0;i<m->nb_rows*m->nb_columns;i++)
		{
			m->mat[i]=reel*m->mat[i];
		}
	}
	else
	{
		fprintf(stderr,"attention matrice non définie");
	}
	return m;
}

void afficheMatrice(Matrix m)
{
	int i,j;
	int n=m->nb_columns;
	int l=m->nb_rows;
	for(i=0;i<l;i++)
	{
		for(j=0;j<n;j++)
		{
			printf("%3f ",m->mat[i*n+j]);
		}
		printf("\n");
	}
	printf("\n");
}

Matrix fillMatrix(Matrix m)
{
	int i,j;
	int n=m->nb_columns;
	int l=m->nb_rows;
	for(i=0;i<l;i++)
	{
		for(j=0;j<n;j++)
		{
			m->mat[i*n+j]=(E)(rand()%10);
		}
	}
	return m;
}
