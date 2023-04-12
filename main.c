#include<stdio.h>
#include<stdlib.h>
// Definition du fonction du maximum
#define max(a,b) a<b? b:a
/// Evaluation d'expression arithmetique en fonction des arbres
/* on utilisera une structure pour representer le type du donnée
qui est soit un operande ou un operateur ,pour ceci on utilse l'union afin
d'avoir un moyen efficace d'utilisation du même emplacement de mémoire à des fins multiples */
typedef union
{
    float nombre;
    char operateur;
}DATA;
/*  Une Structure utilise pour la representation de l'arbre
Description:
	Chaque nœud de l'arbre est un objet constitué :
  * d'un champ de données.
  * d'un pointeur vers le fils gauche (sous-arbre gauche).
  * d'un pointeur vers le fils droit (sous-arbre droit).
*/
typedef struct cel
{
    DATA info;//l'information a inserer de type DATA
    struct cel *fg;// fils gauche
    struct cel *fd;// fils droit
}ARBRE;
/****************  numerique(char )  *****************
Entrées: Un caractere
Sorties: Un entier
But:
  la fonction retourne 1 si le caractere passé en argument, est dans
  l'intervalle des entiers [0,9], sinon retourner 0.
**********************************************************/
int numerique(char c)
{
    // tester sur le caractere passé en parametre
	// retourne 1 si le test est VRAI
    if((c>='0')&&(c<='9')) return((int)1);
       // retourne 0 si le test est FAUX
        return((int)0);
}

/**************** typeoperateur(char) **************
Entrées: caractere
Sorties: entier
But:
	la fonction retourne 1 si le caractere passé en parametre
    est une operateur arithmetique , et 0 sinon .
**********************************************************/
int typeoperateur(char c)
{
    // si le caractere saisit est un operateur retourne 1
    if((c=='+')||(c=='-')||(c=='*')||(c=='/'))return((int)1);
   //sinon 0
    return((int)0);
}
/***************convertir_num(char )*****************
Entrées: caractere
Sorties: entier
But:
	le deroulement de cette fonction   se base sur le code Ascii
	on passe en parametre un caractere ,si il est valide  on le convertit en numerique tout en le  soustrasisant par
	le caractere 0 qui a le code Ascii 48 .
**********************************************************/
int convertir_num(char c )
{
    //si caractere est nombre ,on le converti en numerique
    if(numerique(c)) return((int)c-48);
   // sinon retourner 0
    return((int)-1);
}
/**********convertisseur_entier****
Entrées: entier et caractere
Sorties: entier qui represente le resultat obtenu
But:
	La fonction permet de calculer la partie entiere d'un nombre,
 le deroulement   pour cette fonction  prend en parametre un entier
 qui represente la valeur initiale qu'on'a dejà , et un caractere
 qu'on va le transformer en un entier .
*/
int convertisseur_entier(int s,char c)
{
  return((int)s*10+convertir_num(c));
}

/***** decimale(float ,char ,float )********
Entrées: 2 reels et un caractere
		float nombre :reel represente le nombre intiale
		float coef : le coeffition de multiplication
		char c : le caractere à ajouter au nombre initiale

Sorties:  Un reel representant le resultat obtenu
But:
La fonction sert à calculer la partie decimale d'un nombre,
pour cette fonction  on a un reel  qui represente la valeur initiale qu'on a dejà , et un caractere
à convertir en entier avec la fonction predifinit qui va etre multiplier par un coefficient.
 Exemple:
 	float resultat;
 	float nombre=189.0;
 	char caractere= '9';
 	float coef=0.01;
 	N=decimal(nombre,caractere,coef);
 	demarche:
 		N = nombre+ coef*val_number(c);
 	output:
 		N= 189.09
*/
float decimal(float nombre,char c,float coef)
{
    return((float)nombre+(coef*convertir_num(c)));
}
/****** convertisseur(float *,char ,char *)******
Entrées: -pointeur de reel :(float*) dans lequel on met le resultat
         -caractere: le caractere qu'on a declaré en argumment
		 -pointeur de caractere : le caratere avec lequel en sort de la fonction

Sorties: - entier qui designe le deroulement de la fonction
	 		1 si tout est bien passé
		    0 sinon
	 	 -resultat de la fonction est mis dans une variable
	 	reel passée en parametre comme pointeur ( *resultat).
	 	 - le caratere qui fait sortie par la fonction du calcule
	 	est mis dans une variable de type char qui est passée en parametre
		comme pointeur (*sorti).
But:
Cette fonction concerne le calcule de valeur d'une suite
de caractere saisie (des chiffres).
Premierement on calcule la partie decimale, et on refait
 ce traitement tant qu'on tape encore des chiffres, et si on
 tape une vergule " . ", On sort de la boucle du calcule du partie
 decimale , et on accede au bloc qui concerne le calcule de la partie
 entiere ,et on fait la meme chose tant qu'on tape encore des chiffre.
On sort de cette boucle,si on tape un caractere qui n'est pas
 un chiffre , et on le garde dans la variable qu'on passe deja dans
 les parametres pour le traiter ,( ce caractere qui nous fait sortir
 de cette fonction peut etre une operation ou un caractere non pris
 en charge ).
Au cours du manipulation  de cette fonction , on verifie le caractere
 lu , s'il est un espace on le saute sinon , un non numerique autre que la premiere vergule
 on declare comme une erreure du syntaxe.
On retourne 1 si tout bien passer , sinon erreur.
**********************************************************/
int convertisseur(float *resultat,char donne,char *sorti)
{
	char courrant; // declaration du caractere a traiter au bout du fonction
	int entier=0; // entier pour stocker la valeur decimale compter
	float reel=0.0; // reel pour stocker la valeur entiere calculer
	float coef=1.0; // le coefficient de la partie entiere
	// initialiser le caracter du traitement par la meme valeur d'entrer
	courrant=donne;
	// debut du traitement sur le caractere d'entrer
	// soit il est un chiffre ou une vergule
	if(numerique(courrant)|| courrant == '.')
	{
		while(numerique(courrant)) // le cas d'un chiffre
		{
			// calcule de la partie entiere
			entier=convertisseur_entier(entier,courrant);
			//refaire la lecture du caractere suivant tant qu'on a des espaces
			// pour les eviter et les ignorers.
			do courrant=getchar(); while(courrant == ' ');
		}

		if(courrant== '.') // le cas d'une vergule
		{
			courrant=getchar();// lecture du caractere qui suit la vergule
			// retourner 0 si on a deux vergule qui ce suive
			if(courrant == '.') return 0;
			//refaire la lecture du caractere suivant tant qu'on a des espaces
			// pour les eviter.
			while(courrant== ' ') courrant=getchar();
			// retourner 0 si on a une autre vergule
			if(courrant == '.') return 0;

			// le cas de saisie de chiffre apres la vergule
			while(numerique(courrant))
			{	// le calcule de la partie entiere
				coef*=0.1; // multiplier a chaque fois le coef par 0.1
				// faire appel a la fonction du calcule de cette partie
				// on passe le nombre_float qui joue le role du nombre initale
				// avec le caractere lu (courrant)
				// meme le coef a multiplier
				reel=decimal(reel,courrant,coef);
				//refaire la lecture du caractere suivant tant qu'on a des espaces
				// pour les eviteret les ignorers.
				do courrant=getchar(); while(courrant == ' ');
				// retourner 0, si apres un certains espace saisie on a vergule
				if(courrant == '.') return 0;
			}//fin while(numerique(current))
		}//fin if(current== '.')

		reel+=entier;  // ajouter la partie decimale à la partie entiere
		*resultat=reel;// pointer sur le resultat obtenue
		*sorti=courrant;        // pointer sur le caractere qui nous fait sorti
		return 1;			   // retourner 1 montrons que tout est bien passer
	} // fin if(numerique(current) || current == '.')
}// fin fonction

/***** calcule(float , char , float )******************
Entrées: 2 reels representant  les operandes et un caractere designe
l'operation à faire.
Sorties: un  reel qui designe   le resultat de l'operation faite.
But:
Cette fonction sert a calculer une operation donnée, passant
en parametre les operandes et l'operation a faire.
Le deroulement de cette fonction   fait appel à  un switch
sur l'operateur et on retourne directement le resultat de l'operation tout en ayant des conditions valides.
**********************************************************/

float calcule(float a, char op , float b)
{
	switch (op)
	{
		// si le caractere saisit est + faire la somme
		case '+' : return((float)a + b) ;
		// si le caratere saisit est - faire la soustraction
		case '-' : return ((float)a-b);
		// si le caratere saisit est / faire la division dans le cas d'erreur on le traite dans  ane autre fonction .
		case '/' : if(b!=0) return ((float)a / b);
		// si le caratere saisit est * faire la multiplication
		case '*' : return ((float)a * b);
	}
}
/************ int type(DATA) ****************
Entrées: variable de type union
Sorties: entier qui est soit 0 s'il est un operteur
		 sinon 1 ,le cas d'un reel.
But:
Cette fonction a pour but de verifier un champs
 de l'union , si c'est un operateur en retourne 0
 sinon en retourne 1 (le cas d'un reel).
**********************************************************/

int type(DATA val)
{
	// si le champs operateur d'union est un operateur retourne 0
	if(typeoperateur(val.operateur)) return 0;
	//sinon retourne 1
	return 1;
}




/********** float calcule_arb(ARBRE* )******************
Entrées: arbre .
Sorties: reel qui represente le resultat obtenu ,en utilisant  un
	parcous postfixe de l'arbre.
But:Appel recursif du parcours postfixe en faisant appel chaque fois au fonction du calcul
**********************************************************/

float calcule_arb(ARBRE * arb)
{
	// declaration des variables qui vas contenir les resultas du SAG & SAD
	float resultat_gch,resultat_dt;
	// declaration du caractere qui vas contenir l'operation a effectuer
	char op;

	if(arb) // si l'arbre n'est pas vide
	{
		resultat_gch = calcule_arb(arb->fg);// calcule du SAG
		resultat_dt = calcule_arb(arb->fd);//  calcule du SAD
		op = arb->info.operateur;      // operation a effectuer

		// si la donnée du noeud est un chiffre on le retourne
		// condition d'arret
		if ( type(arb->info) ) return ((float)(arb->info.nombre));
		// si non fait l'appel de la fonction avec le resultat
		// du SAG et SAD avec l'operateur qu'on a dans la racine
		return ((float) calcule(resultat_gch, op ,resultat_dt));
	}//fin if(arb)
	else return 0; // retourner 0 si l'arbre est vide
}// fin du fonction calcule_arb(arbre *arb)


/************creer_noeud(DATA var)*****************
Entrées: variable de type union (DATA)
Sorties: arbre ( le Noeud crée)
But
Cette fonction sert a construire un noeud , on mettant
 le DATA passé en parametre dans le champs de donnée
 du noeud , et initialiser les fils gauche et droit à NULL,ceçi est
aprés l'allocation dynamique du Noeud, et on le retourne par la suite.
**********************************************************/

ARBRE * creer_noeud(DATA val)
{
	ARBRE * noeud; // declaration du noeud
	noeud = (ARBRE*) malloc(sizeof(ARBRE));// l'allocation dynamique du noeud
	if(!noeud) //Erreur de l 'allocation
	 {
	 	printf("\n Erreur d'allocation du Noeud ");
	 	exit(1);
	 }
	noeud->info = val; // met la donne du champs info du noeud
	noeud->fg = NULL; // initaliser SAG à NULL
	noeud->fd = NULL; // initaliser SAD à NULL
	return ((ARBRE*)noeud) ;   // retourner le noeud creer
}

/**********  vider(ARBRE* )*************
Entrées: une arbre
Sorties: arbre vide
But:
On  commence par  vider le sous arbre gauche ,
puis le sous arbre droit et finalement la racine .
Dernièrement on met l'arbre a NULL pour s'assurer quand
 va retourner un arbre vide et supprimer n'importe reste du buffer.
**********************************************************/

ARBRE * vider(ARBRE* arb)
{
	if (arb)
	{
		arb->fg= vider(arb->fg); // vider l'arbre gauch
		arb->fd = vider(arb->fd); // vider l'arbre droit
		free(arb);					 // vider la racine
	}
	arb = NULL;						// pointer l'arbre a NULL
	return arb;						// retourner l'arbre resulta
}

/********** inserer_arbre(ARBRE *, DATA)***********
Entrées:- arbre dans lequel on va inserer la valeur
		- la donnée à inserer de type union(DATA)

Sorties: - retourner arbre resultat , apres faire l'insertion
But:
Cette fonction sert à inserer un nouveau noeud dans la bonne
place selon sa nature et son ordre de priorité s'il s'agit d'une
opération.
Le stockage et l'évaluation de l'expression se complètent
l'un de l'autre, le stockage est fait de telle façon à ce
que l'évaluation se fait dans le sens infixe c'est à dire:
gauche->racine->droite.
L'insertion dans cette fonction ce base sur la nature de
l'element a inserer . Pour ceçi  on traite les  cas des operateurs
parceque  il faut bien gerer la priorité de ces derniers.En effet
s'il s'agit d'un'+' ou '-' on met ce noeud comme nouvelle racine
de l'arbre , et s'il s'agit d'un '*' ou '/'   .on remplace le noeud
actuelle par le nouveau noeud a inserer et le reste de l'arbre reçoit
sous arbre gauche  de ce noeud.
**********************************************************/

ARBRE * remplir_arbre(ARBRE * mon_arb, DATA var)
{
	ARBRE * arb = mon_arb;	  // pointeur sur la racine de l'arbre a traiter
	ARBRE * noeud = NULL;     // le noeud a inserer
	noeud = creer_noeud(var); // la creation du noeud avec la donnée (var)
	if (!arb) return noeud;   // si l'arbre est vide retourner le noeud crée
	if (type(var))          // si la donnée à inserer est un chiffre
	{
		while (arb->fd) arb = arb->fd; // on part jusqu'a le dernier fils dt
		arb->fd = noeud;     // on insere le noeud creer comme un fils dt
	}//fin if (type(var))
	else
	{// si la donnée a inserer est un operateur, on doit  traiter les priorités
	 	// si l'operateur est '*' ou '/' ,on donne la prorité
		if ((var.operateur == '*') || (var.operateur == '/'))
		{
			if (!mon_arb->fd)
			{ // si l'arbre n'a pas un fils dt
				noeud->fg = mon_arb; // SAG du noeud creer reçoit l'arbre
				return noeud;// retourner la nouvelle arbre
			}// fin if (!mon_arb->fd)
			else if (!mon_arb->fd->fd)
			{// si non si l'arbre a un seul fils dt
				if (mon_arb->info.operateur== '/')
				{// si la donnée du noeud est : '/'
					noeud->fg = mon_arb; // SAG du noeud creer reçoit l'arbre
					return noeud; // retourner la nouvelle arbre
				}// fin if (mon_arb->info.operateur == '/')
				else
				{// si la donnée du noeud est differente du  '/'
					// on part jusqu'à un noeud qui posséde 2 fils dt
					while (arb->fd->fd)arb = arb->fd;
					// on point SAG du noeud creer sur la S-A qui reste
					noeud->fg = arb->fd;
					//et en remplace la racine de cette S-A par le noeud creer
					arb->fd = noeud;
				}
			}// fin else if (!mon_arb->fd->fd)
			else
			{// sinon si SAD  a plus que deux fd
				// on boucle jusqu'à s'arret sur un ancetre
				// un noued qu'a 3 fils dt
				while (arb->fd->fd->fd) arb = arb->fd;
				// test sur le continue de ce noeud
				if (arb->fd->info.operateur == '/')
				{// si c'est un '/'
					// pointer le SAG du noeud creer sur l'arbre dt pointer
					noeud->fg = arb->fd;
					// remplacer ce racine par le noeud creer
					arb->fd = noeud;
				}//fin if (arb->fd->info.operateur== '/')
				else
				{// si arb->fd->info.operateur != '/'
					arb = arb->fd;
					noeud->fg = arb->fd;
					arb->fd = noeud;
				}//fin else
			}
		}//fin if ((var.operateur == '*') || (var.operateur == '/'))
		else
		{// si l'operateur a inserer est '+' ou '-'
		   // le noeud creer reçoit la racine & l'ancienne arbre reçoit leur fg
			noeud->fg = mon_arb;
			// retourner la nouvelle arbre
			return noeud;
		}// fin else
	}

	return mon_arb; // retourner l'arbre resultat
}//fin de inserer_arbre(ARBRE * mon_arb, DATA var)



/************ lecture_operateur()*******
Entrées: les caracteres a lire
Sorties: arbre dans lequel on stocke l'operateur arithmetique

**********************************************************/

ARBRE* lecture_opperateur()
{

	ARBRE* arb = NULL;	// arbre dans lequel on stock
	// courrant : variable à stocker le caractere lu
	//operation: variable à stocker l'operateur a faire
	char courrant, operation;
	//etat:indicateur de traitement du chiffre saisie 1 tout bien passer 0 sinon
	//signe: indicateur du signe d'un operande -1 negative, 1 positif
	//der_operation:indicateur qui montre si la formule termine par operation
	int etat=1,signe = 1,der_operation = 0;
	float decimale=0.0;	//number_float : reel à stocker la valeur saisie
	DATA var;	// la donnée a inserer dans l'arbre
	courrant = getchar(); // lecture du premier caratere
	while(courrant==' ') courrant=getchar();// eviter tous les espaces

	if(courrant=='-' || courrant=='+')
	  { // si le premier caractére lu '-' ou '+'
	  	// on les considére comme signe
		if(courrant=='-') signe*=-1; // si '-' le signe reçoit -1
		courrant=getchar(); //lecture du caratére qui le suit
		while(courrant==' ') courrant=getchar(); //eviter les espaces
		while(courrant=='-' || courrant=='+')
			{// tant que on a une suite des operations '+' ou '-'
				// on les considere comme signe
			  if(courrant=='-') signe*=-1;
			  courrant=getchar(); // lecture de caractere qui le suit
			}// fin while(current=='-' || current=='+')
		if ((courrant == '*') || (courrant == '/'))
			{// si le caractere est un '*' ou'/'
				printf("Erreur operation succesive !!\n");// signialer erreur
				arb = vider(arb);		    // assurer de vider l'arbre
				return arb; 					 // retourner l'arbre vide
			}//fin if ((current == '*') || (current == '/'))
   	  }//fin if(current=='-' || current=='+')
	if ((courrant == '*') || (courrant == '/'))
	  {// si on commence par '*' ou '/'
		printf("Erreur operation debut !!\n"); // signialer erreur
		arb = vider(arb);   // assurer de vider l'arbre
		return arb;         // retourner l'arbre vide
	  }	// fin if ((current == '*') || (current == '/'))
	while (courrant != '\n')
	{
		// intialiser a chaque fois indicateur de la dernier operation
		der_operation = 0;
		//  initialier a chaque fois le nombre a saisie
		decimale=0.0;
		if ( numerique(courrant) || courrant=='.' )
		{// si on lit un chiffre ou une vergule
			//faire l'appel a la fonction du calcule
			//et mettre le caractere du sorti dans current
			etat=convertisseur(&decimale,courrant,&courrant);
			// multiplier le resultas de la fonction par le signe
			decimale= (float)decimale* signe;
			/************** Partie de Gestion d'erreur et cas limites ************/
			if ((! decimale) && (operation == '/'))
			 {// le nombre saisie est le zero et suivie par l'operation du division '/'
				printf("Erreur devision par zero !!\n");// signialer erreur
				arb = vider(arb);// assurer de vider l'arbre
				return arb;// retourner l'arbre vide
			 }//fin if ((! number_float) && (operation == '/'))
			if(!etat)
			 {// si etat == 0
				printf("Erreur syntaxe du nombre saisie  !!\n"); // signaler erreur
				arb = vider(arb);// retourner l'arbre vide
				return arb;// retourner l'arbre vide
			 }//fin if(!etat)
			 // si tout est bien passer
			 // remplir le champ reel d'union par le resultas obtenue
			var.nombre = decimale;
			// inserer la donnée dans l'arbre
			arb = remplir_arbre(arb, var);
		}// fin if ( numerique(current) || current=='.' )
		else
		{
			if (typeoperateur(courrant))
			{// si le caractere est une operation
				// initialiser l'indicateur du signe
				signe = 1;
				//stocker l'operation
				operation = courrant;
				//eviter les espaces
				do courrant = getchar();while ( courrant == ' ');
				while (typeoperateur(courrant))
					{// tant que on saisie autre operation
						if ((courrant == '*') || (courrant == '/'))
						{// si c'est '*' ou '/'
							// signaler erreur
							printf("Erreur operation succes !!\n");
							arb = vider(arb);// assurer de vider l'arbre
							return arb;// retourner l'arbre vide
						}//fin if ((current == '*') || (current == '/'))
						else // si l'operation lu est '-'
							 // changer encore signe
							if (courrant =='-') signe *= -1;
							//eviter les espaces
						do courrant = getchar();	while ( courrant == ' ');
					}//fin while (operateur(current))
				der_operation = 1; // signaler comme dernier operation
				// remplire le champs operation de l'union par operation a inserer
				var.operateur = operation;
				// inserer la donnée dans l'arbre
				arb = remplir_arbre(arb, var);
			}//fin if (operateur(current))
		   else
			{// ni operande ni opearation
			  if(courrant != ' ')
			   {//caractére different d'espace
				 printf("Erreur: caractere non inclut !!\n");//signaler l'erreur
				 arb = vider(arb);// assurer de vider l'arbre
				 return arb;// retourner l'arbre vide
			   }
			  courrant = getchar();
		    }
	    }
	}//fin while (current != '\n')
	if(der_operation && ( (operation == '/') || (operation == '*')
	    || (operation=='+') || (operation=='-') )
	  )
	{
		printf("Erreur operation fin !!\n");//signaler l'erreur
		arb =vider(arb);// assurer de vider l'arbre
		return arb;// retourner l'arbre vide
	}// fin if(der_operation && ( (operation == '/')....)
	return arb;// retourner l'arbre resultat
}

/**********affichage_arbre(ARBRE *arb, int current_niveau, int niveau)
Entrées: -arbre a afficher
		 -entier qui designe le niveau actuelle dans l'arbre
		 -entier qui designe la longeur de l'arbre
Sorties: l'affichage structurer de l'arbre
But:
	Cette fonction sert a afficher l'arbre d'une maniére qui ressemble
 a un arbre reel.
 	Cette fonction est recursive , ce qui faut le besoin d'une condition d'arret,
 la condition cette fois ce fait sur l'arbre s'il n'est pas vide,on commence
 à faire l'appel du fonction avec SAD, cette appel s'arret dans les feuilles
 avec leur niveau , apres on boucle avec un for pour saisie les espaces par rapport
 à leur niveau , et on affiche le noeud.
Puis on passe a faire l'appel avec le SAG  de la meme maniere.
**********************************************************/

void affichage_arbre(ARBRE *arb, int niveau)
{
  int i; // l'indice de la boucle for
  if (arb) // si l'arbre est non vide
  {
  	//afficher le SAD
    affichage_arbre(arb->fd, niveau + 1);
    // afficher les espace par rapport au niveau courant
    for (i = 0; i < niveau; i++) printf("    ");
    //affichage de la donnée du noeud
    //  s'il est une valeur
    if (type(arb->info)) printf("%.4f\n", arb->info.nombre);
    // sinon une operation
	else printf("%c\n", arb->info.operateur);
	// afficher le SAG
    affichage_arbre(arb->fg, niveau + 1);
  } // fin if (arb)
}

/***********void operation_arithmetique()******************
Entrées: l'operation saisie par l'utilisateur
Sorties: -affichage de l'arbre & le resultas obtenue
		 - au cas d'erreur message d'erreur

**********************************************************/
void evaluation_arithmetique()
{
	// arbre dans lequel on insere
	ARBRE * arb = NULL;
	char c;// le caractere a stocker ce qu'on tape
	printf("\n Calcule de l'operation arithmetique: \n");
	// boucle pour repeter le programme
			printf("\n Veuiller saisir votre expression mathematique a traiter : \n");
			// lecture de l'operation saisit
			arb=lecture_opperateur();
			// si l'arbre est vide , on vide le buffer
			if (!arb)	do c = getchar(); while (c != '\n');
			else
			{// si l'arbre n'est pas vide
				printf(" L'arbre est comme suite: \n\n");
				//affichage de l'arbre
  				affichage_arbre(arb, 0);
  				printf("\n\n");
  				//affichage du resultat obtenue ,en affichant 4 nombre apres la vergule
				printf("\n -->Le resultat est :%.4f\n", calcule_arb(arb));
			}
			// montrer la fin d'une operation pour tapez une autre
			printf("\n-------------------------------\n");


}

void main()
{
    evaluation_arithmetique();

}
