/* ******************************************************************
 * Polytech-marseille 																*
 * Projet d'algorithmique 2012-2013												*
 * Jeu du morpion																		*
 * Baldé thierno et Pierre-martin Ekomo Abessolo							*
 ********************************************************************/
 
 #include "util.h"
 void afficher_grille(void);
void set_color (GdkGC *gc, int r, int g, int b)
{
		GdkColor c;
		c.pixel = 0;
		c.red = r << 8;
		c.green = g << 8;
		c.blue = b << 8;
		gdk_gc_set_rgb_fg_color (gc, &c);
}
/*fonction qui redessine l'interface 
 * en fonction du contenu de la matrice 
 * */
void redessiner_win (GdkWindow *win)
{
	GdkGC *gc;
	int i,j,test;

	gc = gdk_gc_new (win);
	set_color(gc, 250, 0, 0);
	printf(" fonction redessiner win \n");
	for(i=0;i<=N;i++)
	{
		gdk_draw_line (win, gc, X1+(taille_case*i), Y1, X1+(taille_case*i), Y2);/*trait vertical*/
		gdk_draw_line (win, gc, X1, Y1+(taille_case*i), X2, Y1+(taille_case*i));/*trait horizontal*/
	}
	test=0;
	for(i=0;i<N;i++)
	{
		for(j=0;j<N;j++)
		{
			if(G[i][j]=='j'){
				set_color(gc, 0, 0, 250);
				test=1;
			}
			else if(G[i][j]=='o')
			{
				set_color(gc, 250, 0, 0);
				test=1;
			}
			else if(G[i][j]=='c')
			{
				set_color(gc, 0, 250, 0);
				test=1;
			}
			else if(G[i][j]=='n')
			{
				set_color(gc, 0, 0, 0);
				test=1;
			}
			if(test){
				/* les -et + 5 sont pour laisser une marge*/
				gdk_draw_rectangle (win, gc, TRUE, X1+j*taille_case + 5, Y1+i*taille_case + 5, taille_case-10, taille_case -10);
				test=0;
			}
		}
	}
	
	g_object_unref (gc);
}


void on_event (GdkEvent *ev, gpointer data)
{
	
	GdkGC *gc;
	int lg;
	p_noeud temp,best;
	int mv,v,n;
	int i,j,x,y;
	gc = gdk_gc_new (ev->expose.window);
	switch(ev->type)
	{
		case GDK_DELETE : 
			exit(0);
			break;
			
		case GDK_BUTTON_RELEASE : 
		if(fin || r==Nb_cases){
			printf("fin du jeu\n");
			break;
		}
			printf("bouton relaché\n");
		/*coordonées du pointeur lors du relachement de la souris*/
		x=(int)ev->button.x;
		y=(int)ev->button.y;
		
		if(x>=X1 && x<=X2 && y>=Y1 && y<=Y2)
		{	x=x-X1;
			y=y-Y1;
			i=y/taille_case;
			j=x/taille_case;
			if(G[i][j]=='c')
			{
				/*------- enregistrement du jeu du joueur -------*/
				G[i][j]='j';
				modifier(i,j);
				r++;
				supprimer_noeud(i,j);
				printf("joueur a joué %d  %d\n",i,j);
				gdk_window_invalidate_rect(fenetre,NULL,FALSE);
				
				lg=plus_longue_suite('j');
				if(lg>=5){
					printf("gagné joueur\n"); 
					fin=1;
					break;
				}
				
				temp=L;mv=INT_MIN; best=NULL;
				while(temp!=NULL){
					r--;
					temp->e='o';
					G[temp->x][temp->y]='o';
					n=modifier(temp->x,temp->y);
					/*if(r<10) C=2;
					else if(r<20)C=4;
					else C=5;*/C=3;
					v=parcoursA_B(C-1,0,mv);
					
					depiler(n);
					G[temp->x][temp->y]='c';
					temp->e='c';
					r++;
					if(v>mv)
					{
						mv=v;
						best=temp;
					}
					temp=temp->suiv;
				}
				if(best!=NULL){
				
					G[best->x][best->y]='o';
					modifier(best->x,best->y);
					printf("ordi a joué %d  %d\n",best->x,best->y);
					r++;
					supprimer_noeud(best->x,best->y);
					gdk_window_invalidate_rect(fenetre,NULL,FALSE);
					
					lg=plus_longue_suite('o');
					if(lg>=5){
						printf("gagné ordi\n"); 
						fin=1;
						break;
					}
				}
				else
				{ 
					printf("jeu terminer aucun gagnant\n");
					fin=1;
					break;
				}
			}else
			{
				printf("case dejà choise\n");
				break;
			}	

		}
		else printf("hors des limites de la grille %d %d  \n",x,y);
					break;
						
			case GDK_KEY_PRESS :
			switch(ev->key.keyval)
			{
				case GDK_q : 
					exit(0);
					break;
				case GDK_space :
				/* reinitialisation du jeu*/
					re_init_jeu();
					gdk_window_invalidate_rect(fenetre,NULL,FALSE);
					break;
			}
			break;
			
		case GDK_EXPOSE :
			redessiner_win(ev->expose.window);
			break;
			
		default : break;
	}
	data=data;
}

void boucle_principale()
{
	GMainLoop *loop=g_main_loop_new (NULL, FALSE);
	
	gdk_event_handler_set (on_event, NULL, NULL);
	g_main_loop_run(loop);
}

GdkWindow *creer_fenetre(char *titre,int largeur,int hauteur)
{
	GdkWindowAttr attr;
	GdkWindow *win;
	
	attr.width=largeur;
	attr.height=hauteur;
	attr.window_type=GDK_WINDOW_TOPLEVEL;
	attr.wclass=GDK_INPUT_OUTPUT;
	
	win=gdk_window_new (NULL,&attr,0);
	
	gdk_window_set_title (win, titre);
	gdk_window_show (win);
	
	gdk_window_set_events (win, (GDK_EXPOSURE_MASK|GDK_BUTTON_PRESS_MASK|GDK_BUTTON_RELEASE_MASK|GDK_KEY_PRESS_MASK|GDK_KEY_RELEASE_MASK));
	
	
	return win;
}

/*-----reinitialise le jeu-----------------------*/
void re_init_jeu(void)
{
	int i,j;
	p_noeud temp;
	
	fin=0; 
	
	/* listes*/
	while(L!=NULL)
	{
		temp=L;
		L=L->suiv;
		free(temp);
	}
	/* grillle*/
	for(i=0;i<N;i++)
		for(j=0;j<N;j++)
			G[i][j]='n';
		
	G[N/2][N/2]='o';
	r=1;
	
	/*modification definitive donc pas de depiler derriere*/
	i=modifier(N/2, N/2);
	
	/*redessiner*/
	gdk_window_invalidate_rect(fenetre,NULL,FALSE);
	
}
/* fonction d'initialisation du jeu 
 * Ici nous partons du principe que l'ordi joue en premier
 * */
void init_jeu(void)
{
	int i,j;
	
	fin=0;
	G=malloc(N*sizeof(char*));
	assert(G!=NULL);
	for(i=0;i<N;i++)
	{
		G[i]=malloc(N*sizeof(char));
		assert(G[i]!=NULL);
		for(j=0;j<N;j++)
		G[i][j]='n'; 
		
	}
	
	r=1;
	Nb_cases=N*N;
	X1=20;Y1=20;
	X2=560; Y2=560;
	taille_case=(X2-X1)/N;
	G[N/2][N/2]='o';
	
	/*modification definitive donc pas de depiler derriere*/
	modifier(N/2, N/2);
	
	
}
int main(int argc,char *argv[])
{
	
	if(!(argc==2 && (N=atoi(argv[1]))>=5)){
		printf("\n*******jeu du morpion*******\n\npour lancer le jeu faites:\n./morpion a\n\tavec 'a>=5'la dimension de la grille \n\n");
		return 1;
	}
	
	
	init_jeu();
	gdk_init(&argc,&argv);
	fenetre=creer_fenetre ("\t\t********MORPION*********",600,600);
	printf("Init gdk réussie\n");
	boucle_principale();
	
	return 0;
}


