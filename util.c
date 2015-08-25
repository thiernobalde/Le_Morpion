/* ******************************************************************
 * Polytech-marseille 																*
 * Projet d'algorithmique 2012-2013												*
 * Jeu du morpion																		*
 * Baldé thierno et Pierre-martin Ekomo Abessolo							*
 ********************************************************************/

#include "util.h"


p_noeud creer_noeud(int i, int j, int type, p_noeud suiv)
{
	p_noeud p=malloc(sizeof(struct maillon));
	p->x=i;
	p->y=j;
	p->e=type;
	p->suiv=suiv;
	return p;
}

		
void supprimer_noeud(int i,int j)
{
	p_noeud temp,a;
	temp=L;
	if(temp==NULL)	/* ne sert à rien car temp n'est jamais null */
		return;
	if(temp->x==i && temp->y==j)
	{
		L=L->suiv;
		free(temp);
		return;
	}
	while(temp->suiv!=NULL)
	{
		if(temp->suiv->x==i && temp->suiv->y==j)
		{
			a=temp->suiv;
			temp->suiv=temp->suiv->suiv;
			free(a);
			break;
		}
		temp=temp->suiv;
	}
}	

int plus_longue_suite(char c)
{
	int i,j,k,l,cp;
	/*      horizontale       */
	 int max;
	max=0;
	for(i=0;i<N;i++)
	{
		
		cp=0; 
		for(j=0;j<N;j++)
		{
			if(G[i][j]==c)
				cp++;

			if(j==N-1 || G[i][j]!=c)
			{
			
				if (max<cp)
					max=cp;
				
				cp=0;

			}
		}
	}
	
	
	/*       verticale        */
	/*pareil que horizontale juste une inversion des boucles*/
	/* on conserve le  précédent max 		*/
	
	for(j=0;j<N;j++)
	{
		cp=0; 
		for(i=0;i<N;i++)
		{
			if(G[i][j]==c)
				cp++;
				
			if(i==N-1 || G[i][j]!=c)
			{
				if (max<cp)
					max=cp;
			
				cp=0;
				
			}
		}
	}	
		/*     oblique ascendant      */
	/* on conserve le  précédent max 		*/
	
	for(i=N-1; i>=0; i--)
	{
		cp=0; 
		k=i; l=0;
		while(k>=0 && l<N)
		{
			if(G[k][l]==c)
				cp++;
			
			if(k==0 ||l==N-1 || G[k][l]!=c)
			{

				if (max<cp)
					max=cp;
			
				cp=0;
			}
			k--;
			l++;
		}
		for(j=1;j<N;j++)
		{
			cp=0; 
			k=N-1; l=j;
			while(k>=0 && l<N)
			{
				if(G[k][l]==c)
					cp++;
				
				if(k==0 ||l==N-1 || G[k][l]!=c)
				{
					if (max<cp)
						max=cp;
							
					cp=0;
					
				}
				k--;
				l++;
			}
		}
	}

		/*     oblique descendant      */
	/* on conserve le  précédent max 		*/
	
	for(i=0; i<N; i++)
	{
		cp=0;
		k=i; l=0;
		while(k<N && l<N)
		{
			if(G[k][l]==c)
				cp++;
				
			if(k==N-1 || l==N-1 || G[k][l]!=c)
			{
				
					if (max<cp)
						max=cp;
					cp=0;
			}
			
			k++;
			l++;
		}
		
		
		for(j=1;j<N;j++)
		{
			cp=0; 
			k=0; l=j;
			while(k<N && l<N)
			{
				if(G[k][l]==c)
					cp++;
		
				if(k==N-1 || l==N-1 || G[k][l]!=c)
				{
					if (max<cp)
						max=cp;
					cp=0;
				}
				k++;
				l++;
			}
		}
}

return max;
}
	


/* Fonctions de recherche de la plus longue sous chaine*/

/*	La fonction modifier ajoute 
 * 	les nouvelles case cadidates et renvoie leur nombre
 * */
int modifier(int i, int j)
{
	int k,l,cp;
	cp=0;
	/*printf("modifier de %d %d\n",i,j);*/
	for(k=i-1;k<=i+1;k++){
		for(l=j-1;l<=j+1;l++)
		{
			if((k!=i || l!=j)  && (k<N && l<N && l>=0 && k>=0) && (G[k][l]=='n'))
			{
				L=creer_noeud(k,l,'c',L);
				
				G[k][l]='c';
				cp++;
			}
		}
	}
	return cp;	
}

/*annule les modifications faites par la fonction 
 * modifier
 * */
void depiler(int n)
{
	int i;
	p_noeud l;
	i=0; 
	while(i<n)
	{
		l=L;
		L=L->suiv;
		G[l->x][l->y]='n';
		free(l);
		i++;
	}
}

/*fonction de parcours : principe du mini max
 *val represente  alpha ou beta selon les cas 
 * */
 
int parcoursA_B(int p, int max,int val)
{
	
	p_noeud l;
	int vm, n,v;
	if(p==0 || r==Nb_cases){return evaluation_1();} /* apres p coups anticipés on evalue */
	
	vm=(max?  INT_MIN: INT_MAX);
	l=L;
	while(l!=NULL)
	{
		if(l->e=='c')
		{
			/*modifier le sommet courant*/
			
			l->e=(max ? 'o':'j');
			G[l->x][l->y]=l->e;
			n=modifier(l->x,l->y);
			r++;
			
			v=parcoursA_B(p-1,!max,vm);
			
			G[l->x][l->y]='c';
			r--;
			if(max)/*si on est sur un noeud max*/
			{
			
				if(v>vm)
					vm=v;
				l->e='c';
				depiler(n);
					
				if(vm>=val)
					break;
			
				
			}
			else 
			{
				if(v<vm)
					vm=v;
				l->e='c';
				depiler(n);
					
				if(vm<=val)
					break;
			
			}
			
		}
		l=l->suiv;
	}
	
	return vm;
}





