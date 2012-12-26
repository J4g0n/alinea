#include "interface.h"
#include "matrice.h"
#include "gauss.h"
#include "resol.h"
#include <stdio.h>
#include <stdlib.h>

int menu()
{
	int action,i;
	action=-1;
	while((action<0)||(action>4))
	{
		for(i=0;i<40;i++)
			printf("-");
		printf("\n\nMENU : \n");
		for(i=0;i<=4;i++)
		{
			printf("\t%d./ ",i);
			switch(i)
			{
				case 0:
					printf("quitter ;\n");
					break;
				case 1:
					printf("effectuer des opérations sur les matrices ;\n");
					break;
				case 2:
					printf("résoudre un système d'équations ;\n");
					break;
				case 3:
					printf("inverser une matrice ;\n");
					break;
				case 4:
					printf("décomposer une matrice. \n");
					break;
				default:
					break;
			}
		}
		printf("\n\n");
		for(i=0;i<40;i++)
			printf("-");
		printf("\n\n");
		printf("Que voulez-vous faire?\n");
		scanf("%d",&action);
		printf("\n\n");
	}
	return action;
}

int menuResolution()
{
	Matrix m,result;
	int action,i,j;
	int dim=0;
	action=-1;
	while(action!=0)
	{
		for(i=0;i<40;i++)
			printf("-");
		printf("\n\nRESOLUTION : \n");
		for(i=0;i<2;i++)
		{
			printf("\t%d./ ",i);
			switch(i)
			{
				case 0:
					printf("Retourner au menu ;\n");
					break;
				case 1:
					printf("Resolution par le pivot de gauss ;\n");
					break;
				default:
					break;
			}
		}
		printf("\n\n");
		for(i=0;i<40;i++)
			printf("-");
		printf("\n\n");

		printf("Que voulez-vous faire?\n");
		scanf("%d",&action);
		printf("\n\n");

		if(action==1)
		{
			printf("Donnez la dimension de la matrice.\n");
			scanf("%d",&dim);
			printf("\n");

			printf("Souhaitez-vous remplir la matrice ou la créer	aléatoirement?\n");
			printf("\t1./ Je remplis la matrice moi-même\n");
			printf("\t2./ Je fais confiance au hasard\n");
			scanf("%d",&action);
			printf("\n\n");

			if((dim>=0)&&(action>0)&&(action<3))
			{
				result=newMatrix(dim,1);
				m=newMatrix(dim,dim);

				if(action==1)
				{
					for(i=0;i<dim;i++)
					{
						for(j=0;j<dim;j++)
						{
							printf("Donnez le %dème coefficient pour l'équation %d:	",j,i);
							scanf("%f",&m->mat[i*dim+j]);
						}
						printf("Donnez le résultat pour l'équation %d: ",i);
						scanf("%f",&result->mat[i]);
					}
				}
				if(action==2)	
				{
					fillMatrix(m);
					fillMatrix(result);
				}

				printf("\nVoici les matrices:\n");
				afficheMatrice(m);
				afficheMatrice(result);
				printf("\n");

				result=resol(m,result);
				printf("On obtient: \n");
				for(i=0;i<dim;i++)
					printf("x%d = %f; \n",i,result->mat[i]);
				printf("\n\n\n");

				deleteMatrix(m);
				deleteMatrix(result);
			}
		}
		else
		{
			break;
		}
	}
	return action;
}

int menuInversion()
{
	Matrix m,result;
	int action,act,i,j;
	int dim=0;
	action=-1;
	while(action!=0)
	{
		for(i=0;i<40;i++)
			printf("-");
		printf("\n\nINVERSION : \n");
		for(i=0;i<3;i++)
		{
			printf("\t%d./ ",i);
			switch(i)
			{
				case 0:
					printf("Retourner au menu ;\n");
					break;
				case 1:
					printf("Inversion par la comatrice ;\n");
					break;
				case 2:
					printf("Inversion par le pivot de gauss.\n");
					break;
				default:
					break;
			}
		}
		printf("\n\n");
		for(i=0;i<40;i++)
			printf("-");
		printf("\n\n");

		printf("Que voulez-vous faire?\n");
		scanf("%d",&act);
		printf("\n\n");

		if(act!=0)
		{
			printf("Donnez la dimension de la matrice.\n");
			scanf("%d",&dim);
			printf("\n");

			printf("Souhaitez-vous remplir la matrice ou la créer	aléatoirement?\n");
			printf("\t1./ Je remplis la matrice moi-même\n");
			printf("\t2./ Je fais confiance au hasard\n");
			scanf("%d",&action);
			printf("\n\n");

			if((dim>0)&&(action>0)&&(action<3))
			{
				m=newMatrix(dim,dim);

				if(action==1)
				{
					for(i=0;i<dim;i++)
					{
						for(j=0;j<dim;j++)
						{
							printf("Donnez le %dème coefficient pour la ligne %d:	",j,i);
							scanf("%f",&m->mat[i*dim+j]);
						}
					}
				}
				if(action==2)	
				{
					fillMatrix(m);
				}

				printf("\nVoici la matrice: \n");
				afficheMatrice(m);
				printf("\n");

				if(act==1) 
				{
					printf("attention cette inversion n'est pas toujours foncionnelle\n");
					result=inverseComat(m);
				}
				else result=inverseGauss(m);

				printf("On obtient: \n");
				afficheMatrice(result);

				deleteMatrix(m);
				deleteMatrix(result);
			}
		}
		else
		{
			break;
		}
	}
	return action;
}

int menuOperation()
{
	Matrix m,m1,result;
	int action,act,i,j,row,column,row1,column1;
	int dim=0;
	action=-1;
	while(act!=0)
	{
		for(i=0;i<40;i++)
			printf("-");
		printf("\n\nOPERATIONS: \n");
		for(i=0;i<4;i++)
		{
			printf("\t%d./ ",i);
			switch(i)
			{
				case 0:
					printf("Retourner au menu ;\n");
					break;
				case 1:
					printf("Echelonner une matrice par le pivot de gauss ;\n");
					break;
				case 2:
					printf("Additionner deux matrices ;\n");
					break;
				case 3:
					printf("Multiplication de deux matrices.\n");
					break;
				default:
					break;
			}
		}
		printf("\n\n");
		for(i=0;i<40;i++)
			printf("-");
		printf("\n\n");

		printf("Que voulez-vous faire?\n");
		scanf("%d",&act);
		printf("\n\n");

		switch(act)
		{
			case 1:
				printf("Donnez la dimension de la matrice.\n");
				scanf("%d",&dim);
				printf("\n");

				printf("Souhaitez-vous remplir la matrice ou la créer	aléatoirement?\n");
				printf("\t1./ Je remplis la matrice moi-même\n");
				printf("\t2./ Je fais confiance au hasard\n");
				scanf("%d",&action);
				printf("\n\n");

				if((dim>0)&&(action>0)&&(action<3))
				{
					m=newMatrix(dim,dim);

					if(action==1)
					{
						for(i=0;i<dim;i++)
						{
							for(j=0;j<dim;j++)
							{
								printf("Donnez le %dème coefficient pour la ligne %d:	",j,i);
								scanf("%f",&m->mat[i*dim+j]);
							}
						}
					}
					if(action==2)	
					{
						fillMatrix(m);
					}

					printf("\nVoici la matrice: \n");
					afficheMatrice(m);
					printf("\n");

					result=gauss(m);

					printf("On obtient: \n");
					afficheMatrice(result);

					deleteMatrix(result);
				}	
				break;
			case 2: 
				printf("Donnez les dimensions de la matrice.\n");
				printf("\tNombre de lignes: ");
				scanf("%d",&row);
				printf("\tNombre de colonnes: ");
				scanf("%d",&column);
				printf("\n");

				printf("Souhaitez-vous remplir les matrices ou les créer aléatoirement?\n");
				printf("\t1./ Je remplis les matrices moi-même\n");
				printf("\t2./ Je fais confiance au hasard\n");
				scanf("%d",&action);
				printf("\n\n");

				if((row>0)&&(column>0))
				{
					m=newMatrix(row,column);
					m1=newMatrix(row,column);

					if(action==1)
					{
						printf("Matrice 1: \n");
						for(i=0;i<row;i++)
						{
							for(j=0;j<column;j++)
							{
								printf("%dème ligne, %d colonne:	",i,j);
								scanf("%f",&m->mat[i*column+j]);
							}
						}
						printf("\n\nMatrice 2: \n");
						for(i=0;i<row;i++)
						{
							for(j=0;j<column;j++)
							{
								printf("%dème ligne, %d colonne:	",i,j);
								scanf("%f",&m1->mat[i*column+j]);
							}
						}
					}
					if(action==2)	
					{
						fillMatrix(m);
						fillMatrix(m1);
					}

					printf("\nVoici les matrices: \n");
					afficheMatrice(m);
					afficheMatrice(m1);
					printf("\n");

					result=addition(m,m1);

					printf("On obtient: \n");
					afficheMatrice(result);

					deleteMatrix(result);
					deleteMatrix(m);
					deleteMatrix(m1);
				}			
				break;
			case 3:
				printf("Donnez les dimensions des matrices.\n");
				printf("Matrice 1:\n");
				printf("\tNombre de lignes: ");
				scanf("%d",&row);
				printf("\tNombre de colonnes: ");
				scanf("%d",&column);
				printf("Matrice 2:\n");
				printf("\tNombre de lignes: ");
				scanf("%d",&row1);
				printf("\tNombre de colonnes: ");
				scanf("%d",&column1);
				printf("\n");

				if((column==row1)&&(row>0)&&(column>0)&&(column1>0))
				{
					printf("Souhaitez-vous remplir les matrices ou les créer aléatoirement?\n");
					printf("\t1./ Je remplis les matrices moi-même\n");
					printf("\t2./ Je fais confiance au hasard\n");
					scanf("%d",&action);
					printf("\n\n");

					m=newMatrix(row,column);
					m1=newMatrix(row1,column1);

					if(action==1)
					{
						printf("Matrice 1: \n");
						for(i=0;i<row;i++)
						{
							for(j=0;j<column;j++)
							{
								printf("%dème ligne, %dème colonne:	",i,j);
								scanf("%f",&m->mat[i*column+j]);
							}
						}
						printf("Matrice 2: \n");
						for(i=0;i<row1;i++)
						{
							for(j=0;j<column1;j++)
							{
								printf("%dème ligne, %dème colonne:	",i,j);
								scanf("%f",&m1->mat[i*column1+j]);
							}
						}
					}
					if(action==2)	
					{
						fillMatrix(m);
						fillMatrix(m1);
					}

					printf("\nVoici les matrices: \n");
					afficheMatrice(m);
					afficheMatrice(m1);
					printf("\n");

					result=multiplication(m,m1);

					printf("On obtient: \n");
					afficheMatrice(result);

					deleteMatrix(result);
					deleteMatrix(m);
					deleteMatrix(m1);
				}
				break;
			default:
				break;
		}
	}
	return action;
}

int menuDecomposition()
{
	Matrix m,p,l,u;
	int action,i,j;
	int dim=0;
	action=-1;
	while(action!=0)
	{
		for(i=0;i<40;i++)
			printf("-");
		printf("\n\nDECOMPOSITION : \n");
		for(i=0;i<2;i++)
		{
			printf("\t%d./ ",i);
			switch(i)
			{
				case 0:
					printf("Retourner au menu ;\n");
					break;
				case 1:
					printf("Décompostion PLU.\n");
					break;
				default:
					break;
			}
		}
		printf("\n\n");
		for(i=0;i<40;i++)
			printf("-");
		printf("\n\n");

		printf("Que voulez-vous faire?\n");
		scanf("%d",&action);
		printf("\n\n");

		if(action==1)
		{
			printf("Donnez la dimension de la matrice.\n");
			scanf("%d",&dim);
			printf("\n");

			printf("Souhaitez-vous remplir la matrice ou la créer	aléatoirement?\n");
			printf("\t1./ Je remplis la matrice moi-même\n");
			printf("\t2./ Je fais confiance au hasard\n");
			scanf("%d",&action);
			printf("\n\n");

			if((dim>0))
			{
				p=identite(dim,dim);
				l=identite(dim,dim);
				u=newMatrix(dim,dim);
				m=newMatrix(dim,dim);

				if(action==1)
				{
					for(i=0;i<dim;i++)
					{
						for(j=0;j<dim;j++)
						{
							printf("Donnez le %dème coefficient pour l'équation %d:	",j,i);
							scanf("%f",&m->mat[i*dim+j]);
						}
					}
				}
				if(action==2)	
				{
					fillMatrix(m);
				}

				printf("\nVoici les matrices:\n");
				afficheMatrice(m);
				printf("\n");

				plu(m,p,l,u);

				printf("On obtient: \n");
				afficheMatrice(p);
				afficheMatrice(l);
				afficheMatrice(u);
				printf("\n\n\n");

				deleteMatrix(m);
				deleteMatrix(p);
				deleteMatrix(l);
				deleteMatrix(u);
			}
		}
		else
		{
			break;
		}
	}
	return action;
}
