/* ******************************************************************
 * Polytech-marseille 																*
 * Projet d'algorithmique 2012-2013												*
 * Jeu du morpion																		*
 * Baldé thierno et Pierre-martin Ekomo Abessolo							*
 ********************************************************************/

#include "util.h"

/*--------------------------fonction d'evaluation 1------------------------*/
int calcul_score(int cp)
{
	switch(cp)
	{
		case 1:
			return 2;
		case 2:
			return 8;
		case 3:
			return 50;	
		case 4:
			return 200;
		default:
			return 0;
	}
}

/*elle evalue un etat donné de la grille de jeu et renvoi un entier
 * */
/* j'ai quelque douttes sur l'utilité de ce que je fait ici . 
 * il faut que je verifie si je peut pas pas faiire plus
 *  simple et moin couteux .
 * */
int evaluation_1(void)
{
	int i,j,k,l,cp,score;
	char c;
	int lg;
	
	lg=plus_longue_suite('j');
	if(lg>=5)
		return -1000;
	 
	lg=plus_longue_suite('o');
	if(lg>=5)
		return 1000;
	
	
	score=0;
	/* score horizontale*/
	j=0;
	for(i=0;i<N;i++)
	{
		
		cp=0; 
		while(j<N)
		{
			cp=0;
			while(j<N && G[i][j]!='o' && G[i][j]!='j')
				j++;
			/* faire test dfe non depassement avant affectation*/
			if (j<N)
				c=G[i][j];
			while(j<N && c==G[i][j])
			{
				cp++;
				j++;
			}
			if(j<N && G[i][j]=='o')
				score=score+calcul_score(cp);
			else if(j<N && G[i][j]=='j')
				score=score-calcul_score(cp);
				
		}
	}
	/* score vertical*/
	i=0;
	for(j=0;j<N;j++)
	{
		while(i<N)
		{
			cp=0;
			while(i<N && G[i][j]!='o' && G[i][j]!='j')
				i++;
			if(i<N)
				c=G[i][j];
			while(i<N && c==G[i][j])
			{
				cp++;
				i++;
			}
			if(i<N && G[i][j]=='o')
				score=score+calcul_score(cp);
			else if(i<N && G[i][j]=='j')
				score=score-calcul_score(cp);
		}
	}
	
	
	
	/* score    oblique ascendant      */
	
	for(i=N-1; i>=0; i--)
	{
		cp=0; 
		k=i; l=0;
		while(k>=0 && l<N)
		{
			while(k>=0 && l<N && G[k][l]!='o' && G[k][l]!='j')
			{
				k--;
				l++;
			}
			if(k>=0 && l<N)
				c=G[k][l];
			while(k>=0 && l<N && c==G[k][l])
			{
				cp++;
				k--;
				l++;
			}
			if(k>=0 && l<N && G[k][l]=='o')
				score=score+calcul_score(cp);
			else if(k>=0 && l<N && G[k][l]=='j')
				score=score-calcul_score(cp);
		}
	}
	
	for(j=1;j<N;j++)
	{
		cp=0;
		k=N-1; l=j;
		while(k>=0 && l<N)
		{
			while(k>=0 && l<N && G[k][l]!='o' && G[k][l]!='j')
			{
				k--;
				l++;
			}
			
			if(k>=0 && l<N)
				c=G[k][l];
			while(k>=0 && l<N && c==G[k][l])
			{
				cp++;
				k--;
				l++;
			}
			if(k>=0 && l<N && G[k][l]=='o')
				score=score+calcul_score(cp);
			else if(k>=0 && l<N && G[k][l]=='j')
				score=score-calcul_score(cp);
		}
	}

		/*     oblique descendant      */
	
	for(i=0; i<N; i++)
	{
		cp=0;
		k=i; l=0;
		while(k<N && l<N)
		{
			while(k<N && l<N && G[k][l]!='o' && G[k][l]!='j')
			{
				k++;
				l++;
			}
			if(k<N && l<N)
				c=G[k][l];
			while(k<N && l<N  && c==G[k][l])
			{
				cp++;
				k++;
				l++;
			}
			if(k<N && l<N && G[k][l]=='o')
				score=score+calcul_score(cp);
			else if(k<N && l<N && G[k][l]=='j')
				score=score-calcul_score(cp);
		}	
	}
	for(j=1;j<N;j++)
	{
		
		cp=0;
		k=0; l=j;
		while(k<N && l<N)
		{
			while(k<N && l<N && G[k][l]!='o' && G[k][l]!='j')
			{
				k++;
				l++;
			}
			if(k<N && l<N)
				c=G[k][l]; 
			while(k<N && l<N  && c==G[k][l])
			{
				cp++;
				k++;
				l++;
			}
			if(k<N && l<N && G[k][l]=='o')
				score=score+calcul_score(cp);
			else if(k<N && l<N && G[k][l]=='j')
				score=score-calcul_score(cp);
		}
	}	

	return score;
}


/*--------------------------------------------------------------------------*/
/*-----------------------fonction d'évaluation 2----------------------------*/
/*--------------------------------------------------------------------------*/
int nombre_pion(char c,int i)
{
	int som=0;
	int j;
	for(j=0;j<N;j++)
		if(G[i][j]==c)
			som+=1;
	
	return som;
}
	

int nombre_pion_ligne(char c,int i)
{
	int som=0;
	int j;
	for(j=0;j<N;j++)
		if(G[i][j]==c)
			som+=1;
	
	return som;
}

int nombre_pion_colonne(char c,int i)
{
	int som=0;
	int j;
	for(j=0;j<N;j++)
		if(G[j][i]==c)
			som+=1;
	
	return som;
}


int nombre_pion_diagoa_i (char c,int i)
{
		int k,l,som;
		
		k=i; l=0;
		som=0;
		while(k>=0 && l<N)
		{
			if(G[k][l]==c)
				som+=1;
			
			k--;
			l++;
		}
	return som;
}
int nombre_pion_diagoa_j (char c,int j)
{
		int k,l,som;
		
		k=N-1; l=j;
		som=0;
		while(k>=0 && l<N)
		{
			if(G[k][l]==c)
				som+=1;
			
			k--;
			l++;
		}
	return som;
}

int nombre_pion_diagod_i (char c,int i)
{
	int k,l,som;
		
		som=0;
		k=i; l=0;
		while(k<N && l<N)
		{
			if(G[k][l]==c)
				som+=1;
			
			k++;
			l++;
		}
		return som;
		
}		

int nombre_pion_diagod_j (char c,int j)
{
		int k,l,som;
		
		k=0; l=j;
		som=0;
		while(k<N && l<N)
		{
			if(G[k][l]==c)
				som+=1;
			
			k++;
			l++;
		}
	return som;
}
		
		

int evaluation_2(void)
{
	int score,som;
	int lg1,lg2;
	int i,j;
	
	for (i=0;i<N;i++)
		for (j=0;j<N;j++)
			if ((G[i][j]=='j') || (G[i][j]=='o'))
				som=som+1;
	lg1=plus_longue_suite('j');
	lg2=plus_longue_suite('o');
	
	score=0;
	
	if ((lg1>=5) || (lg1>=5))
	{
		if ((lg1>=5) && (lg2>=5))
			return 0;
		if (lg1>=5)
		  {
			  return 1000;
		  }
		  else if (lg2>=5)
		  {
			   return -1000;
		  }
	}
	else
	{
		for(i=0;i<N;i++)
		{
				if(!(nombre_pion_ligne('o',i)>1 && nombre_pion_ligne('j',i)>1))
				{
					if (nombre_pion_ligne('o',i)==4)
						score=400+score;
					else if (nombre_pion_ligne('j',i)==4)
								score=-400+score;
							else if (nombre_pion_ligne('o',i)==3)
										score=300+score;
									else if (nombre_pion_ligne('j',i)==3)
											score=-300+score;
											else if (nombre_pion_ligne('o',i)==2)
													score=200+score;
													else if (nombre_pion_ligne('j',i)==2)
															score=-200+score;
															else if (nombre_pion_ligne('o',i)==1)
																	score=100+score;
																	else if (nombre_pion_ligne('j',i)==1)
																				score=-100+score;
				}
			 
			 /* *********parcours en colonne ****************** */
			
			if(!(nombre_pion_colonne('o',i)>1 && nombre_pion_colonne('j',i)>1))
				{
					if (nombre_pion_colonne('o',i)==4)
						score=400+score;
					else if (nombre_pion_colonne('j',i)==4)
								score=-400+score;
							else if (nombre_pion_colonne('o',i)==3)
										score=300+score;
									else if (nombre_pion_colonne('j',i)==3)
											score=-300+score;
											else if (nombre_pion_colonne('o',i)==2)
													score=200+score;
													else if (nombre_pion_colonne('j',i)==2)
															score=-200+score;
															else if (nombre_pion_colonne('o',i)==1)
																	score=100+score;
																	else if (nombre_pion_colonne('j',i)==1)
																				score=-100+score;
				}
		}	
			
		/* ----------------parcours en diagonal ascendante en i---------------*/
		/* i variant j fixe et egala à 0------------------------------------*/
		/*les diagonales ascendants au dessus de la grande diagonale--------*/
		for(i=0;i<N;i++)
		{
			if(!(nombre_pion_diagoa_i('o',i)>1 && nombre_pion_diagoa_i('j',i)>1))
			{
				if (nombre_pion_diagoa_i('o',i)==4)
					score=400+score;
				else if (nombre_pion_diagoa_i('j',i)==4)
							score=-400+score;
						else if (nombre_pion_diagoa_i('o',i)==3)
									score=300+score;
								else if (nombre_pion_diagoa_i('j',i)==3)
										score=-300+score;
										else if (nombre_pion_diagoa_i('o',i)==2)
												score=200+score;
												else if (nombre_pion_diagoa_i('j',i)==2)
														score=-200+score;
														else if (nombre_pion_diagoa_i('o',i)==1)
																score=100+score;
																else if (nombre_pion_diagoa_i('j',i)==1)
																			score=-100+score;
			}
		}
		/* ----------------parcours en diagonal ascendante en j---------------*/
		/* j variant i fixe et egala à N-1------------------------------------*/
		/*les diagonales ascendants en dessous de la grande diagonale--------*/
		for(j=0;j<N;j++)
		{
			if(!(nombre_pion_diagoa_j('o',j)>1 && nombre_pion_diagoa_j('j',j)>1))
			{
				if (nombre_pion_diagoa_j('o',j)==4)
					score=400+score;
				else if (nombre_pion_diagoa_j('j',j)==4)
							score=-400+score;
						else if (nombre_pion_diagoa_j('o',j)==3)
									score=300+score;
								else if (nombre_pion_diagoa_j('j',j)==3)
										score=-300+score;
										else if (nombre_pion_diagoa_j('o',j)==2)
												score=200+score;
												else if (nombre_pion_diagoa_j('j',j)==2)
														score=-200+score;
														else if (nombre_pion_diagoa_j('o',j)==1)
																score=100+score;
																else if (nombre_pion_diagoa_j('j',j)==1)
																			score=-100+score;
			}
		}
			
		/*----------------parcours en diagonal descendante en i-------------*/
		/* i variant j fixe et egala à 0------------------------------------*/
		/*les diagonales descendantes en dessous de la grande diagonale--------*/
		for(i=0;i<N;i++)
		{
			if(!(nombre_pion_diagod_i('o',i)>1 && nombre_pion_diagod_i('j',i)>1))
			{
				if (nombre_pion_diagod_i('o',i)==4)
					score=400+score;
				else if (nombre_pion_diagod_i('j',i)==4)
							score=-400+score;
						else if (nombre_pion_diagod_i('o',i)==3)
									score=300+score;
								else if (nombre_pion_diagod_i('j',i)==3)
										score=-300+score;
										else if (nombre_pion_diagod_i('o',i)==2)
												score=200+score;
												else if (nombre_pion_diagod_i('j',i)==2)
														score=-200+score;
														else if (nombre_pion_diagod_i('o',i)==1)
																score=100+score;
																else if (nombre_pion_diagod_i('j',i)==1)
																			score=-100+score;
			}
		}
			
	
	/*----------------parcours en diagonal descendante en j-------------*/
	/* j variant i fixe et egala à 0------------------------------------*/
	/*les diagonales descendantes au dessus de la grande diagonale--------*/
		for(j=0;j<N;j++)
		{
			if(!(nombre_pion_diagod_j('o',j)>1 && nombre_pion_diagod_j('j',j)>1))
			{
				if (nombre_pion_diagod_j('o',j)==4)
					score=400+score;
				else if (nombre_pion_diagod_j('j',j)==4)
							score=-400+score;
						else if (nombre_pion_diagod_j('o',j)==3)
									score=300+score;
								else if (nombre_pion_diagod_j('j',j)==3)
										score=-300+score;
										else if (nombre_pion_diagod_j('o',j)==2)
												score=200+score;
												else if (nombre_pion_diagod_j('j',j)==2)
														score=-200+score;
														else if (nombre_pion_diagod_j('o',j)==1)
																score=100+score;
																else if (nombre_pion_diagod_j('j',j)==1)
																			score=-100+score;
			}
		}
		
	}
		
	return score;
}
