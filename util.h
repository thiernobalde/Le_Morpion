/* ******************************************************************
 * Polytech-marseille 																*
 * Projet d'algorithmique 2012-2013												*
 * Jeu du morpion																		*
 * Baldé thierno et Pierre-martin Ekomo Abessolo							*
 ********************************************************************/


#ifndef _UTIL_
#define _UTIL_

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>

#include <gdk/gdk.h>
#include <gdk/gdkkeysyms.h>
/*#define N 6 juste pour retrouver une erreur de segmentation avec gdb*/
/*#define C 2*/
/*definition de types*/
typedef struct maillon
{
	int x;
	int y;
	char e;/*Canddidate, Humain, Ordi, Non-candidate*/
	struct maillon *suiv;
}noeud,*p_noeud;

typedef struct chaine
{
	int i1;
	int j1;
	int i2;
	int j2;
	char t;
	int l;
}Chaine;

GdkWindow *fenetre;
int C;
int fin;
int r; /* utiliser  pour chaque etat le nombre de cases deja choisies*/
int N;
int Nb_cases ;  /*le nombre de cases de la grille N*N  */
int taille_case;
p_noeud L; /*contient la liste des coups possibles*/
char **G;/*la grille du jeu */
int X1, Y1, X2, Y2;

void re_init_jeu(void);

int  plus_longue_suite(char c);
int parcoursA_B(int p, int max,int val);
int modifier(int i,int j);
void depiler(int n);
void supprimer_noeud(int i,int j);


int evaluation_1(void);
int evaluation_2(void);

#endif
