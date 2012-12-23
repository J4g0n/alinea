#include "gauss.h"
#include <stdio.h>
#include <stdlib.h>

E m_determinant(Matrix m)
{
	E r=0;
	if(isSquare(m))
	{
		int n=m->nb_columns;
		int i;
		if(n==1)
			r=m->mat[0];
		else
		{
			if(n==2)
			{
				r=m->mat[0]*m->mat[3]-m->mat[2]*m->mat[1];
			}
			else
			{
				for(i=0;i<n;i++)
				{
					if(i%2==0) r+=m_determinant(extraction(m,0,i))*m->mat[i];
					else r-=m_determinant(extraction(m,0,i))*m->mat[i];
				}
			}
		}
	}
	return r;
}

Matrix extraction(Matrix m,int i,int j)
{
	Matrix mcp;
	if(m!=NULL)
	{		
		int rows=m->nb_rows;
		int columns=m->nb_columns;
		mcp=newMatrix(rows-1,columns-1);
		int k,l,s;
		s=0;
		for(k=0;k<rows;k++)
		{
			if(k!=i)
			{
				for(l=0;l<columns;l++)
				{
					if(l!=j)
					{
						mcp->mat[s]=m->mat[k*columns+l];
						s++;
					}
				}
			}
		}
	}
	return mcp;
}

Matrix mulLigne(Matrix m,E n,int i)
{
	int j;
	int nbreColonnes=m->nb_columns;
	for(j=0;j<nbreColonnes;j++)
	{
		m->mat[i*nbreColonnes+j]=m->mat[i*nbreColonnes+j]*n;
	}
	return m;
}

Matrix addMulLigne(Matrix m,E f,int i,int j)
{
	int k;
	int n=m->nb_columns;
	for(k=0;k<n;k++)
	{
		m->mat[j*n+k]=m->mat[i*n+k]*f+m->mat[j*n+k];
	}
	return m;
}

Matrix permuter(Matrix m,int i,int j)
{
	int k;
	E tmp;
	int n=m->nb_columns;
	for(k=0;k<n;k++)
	{
		tmp=m->mat[i*n+k];
		m->mat[i*n+k]=m->mat[j*n+k];
		m->mat[j*n+k]=tmp;
	}
	return m;
}

Matrix gauss(Matrix m)
{
	if(isSquare(m))
	{
		int column=m->nb_columns;
		int row=m->nb_rows;
		int i,j;
		E f;
		for(i=0;i<row;i++)
		{
			for(j=i+1;j<row;j++)
			{
				if(m->mat[i*column+i]==0)
				{
					int k;
					for(k=j+1;k<row;k++)
						if(m->mat[k*column+i]!=0) {m=permuter(m,i,k);break;}
				}
				f=-(m->mat[j*column+i]/m->mat[i*column+i]);
				m=addMulLigne(m,f,i,j);
			}
		}
	}
	return m;
}

E m_detGauss(Matrix m)
{
	E det=1;
	if(isSquare(m))
	{
		m=gauss(m);
		int n=m->nb_rows;
		int i;
		for(i=0;i<n;i++)
		{
			det*=m->mat[i*n+i];
		}
	}
	return det;
}
