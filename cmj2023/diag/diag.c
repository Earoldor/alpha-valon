/***********************************************************/
/*Groupe : La Valeur                                       */
/*Numéro du groupe : 1                                     */
/*Composition du groupe :                                  */
/* OUAZZANI CHAHDI Oualid                                  */
/* VOROBIEFF--NAWROT Clément                               */
/* DESVIGNE Arthur                                         */
/* DEBROUCKER Baptiste                                     */
/*Horodatage de création de ce fichier : 19/02/24          */
/***********************************************************/

// Path: alpha-valon/cmj2023/diag/diag.c

/***********************************************************/
/*Déclaration des librairies. Nous aurons besoins des      */
/*librairies de base du langage C, ainsi que celle fournies*/
/***********************************************************/

#include <stdio.h>                  //standard input output
#include <stdlib.h>                 //standard également
#include <string.h>                 //pour le traitement de chaine de caractère
#include "../include/avalam.h"      //pour les fonctions de jeu
#include "../include/topologie.h"   //pour la topologie du plateau
#define MAXNOM 20
#define MAXCHAR 1000

/***********************************************************/
/*Déclaration des prototypes                               */
/***********************************************************/

void writeJS(T_Position position, T_Score score, char chaine_JS[]); //prototype de la fonction d'écriture du fichier JSON
void fonctionFen(T_Position position);                              //prototype de la fonction d'écriture du format FEN
T_Position interpreterFen(char* argv[]);                                //prototype de la fonction d'interprétation du format FEN

/***********************************************************/
/*Fonction principale : main                               */
/***********************************************************/

int main(int argc, char* argv[])
{
    /*******************************************************/
    /*Déclaration des variables                            */
    /*******************************************************/

    T_Position position;    //déclaration de la position
    T_Score score;          //déclaration du score
    T_Coup coup;            //déclaration du coup
    T_ListeCoups legaux;    //déclaration des coups légaux (critère d'arret potentiel)
    octet stockage;         //déclaration d'un octet qui servira de stockage quelconque
    int reponse;


    /*******************************************************/
    /*Initialisation et démarrage de la partie             */
    /*******************************************************/



    printf("\t!--!--!--!--!--!--!--!--! JOUONS À AVALAM !--!--!--!--!--!--!--!--!\n\n");

    position = getPositionInitiale();    //initialisation de la position
    legaux = getCoupsLegaux(position);   //initialisation des coups légaux
    score = evaluerScore(position);      //initialisation du score

    printf("Voulez-vous charger une partie ? (1 pour oui, 0 pour non) : ");
    scanf("%d", &reponse);

    if(reponse != 1)
    {
    

    writeJS(position, score, "./web/refresh-data.json");    //écriture du fichier JSON de la position initiale
    fonctionFen(position);                                  //écriture du format FEN de la position initiale

    printf("\t!--!--!--!--!--!--!--!--! LA PARTIE COMMENCE !--!--!--!--!--!--!--!--!\n\n");

    printf("\tC'est au tour du joueur %d de jouer.\n", position.trait);    //affichage du joueur qui doit jouer au départ
    

    /*******************************************************/
    /*Placement des bonus et des malus                     */
    /*******************************************************/


    printf("\n\tAu tour du joueur 1 de donner la position de son bonus :");
    scanf("%hhd", &position.evolution.bonusJ);            //saisie de la position du bonus du joueur 1

    while(position.cols[position.evolution.bonusJ].couleur==ROU)
    {
        printf("\n\tImpossible de placer le bonus sur une case occupée par un malus ou d'une autre couleur, veuillez choisir une autre case:");
        scanf("%hhd", &position.evolution.bonusJ);
    }
   
    printf("\n\tAu tour du joueur 1 de donner la position de son malus :");
    scanf("%hhd", &position.evolution.malusJ);            //saisie de la position du malus du joueur 1

    while(position.cols[position.evolution.malusJ].couleur!=JAU || position.evolution.malusJ==position.evolution.bonusJ)
    {
        printf("\tImpossible de placer le bonus sur une case occupée par un malus ou d'une autre couleur, veuillez choisir une autre :");
        scanf("%hhd", &position.evolution.malusJ);
    }

    printf("\n\tAu tour du joueur 2 de donner la position de son bonus :");
    scanf("%hhd", &position.evolution.bonusR);            //saisie de la position du bonus du joueur 2

    while(position.cols[position.evolution.bonusR].couleur!=ROU)
    {
        printf("\tImpossible de placer le bonus sur une case occupée par un malus ou d'une autre couleur, veuillez choisir une autre :");
        scanf("%hhd", &position.evolution.bonusR);
    }

    printf("\n\tAu tour du joueur 2 de donner la position de son malus :");
    scanf("%hhd", &position.evolution.malusR);            //saisie de la position du malus du joueur 2

    while(position.cols[position.evolution.malusR].couleur!=ROU || position.evolution.malusR==position.evolution.bonusR)
    {
        printf("\tImpossible de placer le bonus sur une case occupée par un malus ou d'une autre couleur, veuillez choisir une autre :");
        scanf("%hhd", &position.evolution.malusR);
    }

    writeJS(position, score, "./web/refresh-data.json");    //écriture du fichier JSON de la position initiale

    /*******************************************************/
    /*Déroulement de la partie                             */
    /*Première fonction while qui servira de boucle de jeu */
    /*******************************************************/

    while(legaux.nb != 0)
    {
        printf("\n\tC'est au tour du joueur %d de jouer.\n", position.trait);    //affichage du joueur qui doit jouer

        /***************************************************/
        /*Système de coups                                 */
        /***************************************************/

        printf("\n\t!--!--!--!--!--!--!--!--! QUELLE COUP VOULEZ-VOUS JOUER ? !--!--!--!--!--!--!--!--!\n\n");
        printf("\n\tEntrez la case de départ : ");              //demande de la case de départ
        scanf("%hhd", &coup.origine);                             //saisie de la case de départ
  
        printf("\n\tEntrez la case d'arrivée : ");              //demande de la case d'arrivée
        scanf("%hhd", &coup.destination);                         //saisie de la case d'arrivée

        stockage = estValide(position, coup.origine, coup.destination);    //stockage de la validité du coup
        
        /***************************************************/
        /*Vérification et mise en place du coup si valide  */
        /***************************************************/

        if(stockage == 1)                                                       //si le coup est valide
        {
            position = jouerCoup(position, coup.origine, coup.destination);     //jouer le coup
            score = evaluerScore(position);                                     //évaluer le score
            printf("\n\t!--!--!--!--!--!--!--!--! COUP JOUÉ AVEC SUCCÈS !--!--!--!--!--!--!--!--!\n\n");
        }
        else                                                                    //si le coup n'est pas valide
        {
            printf("\n\t!--!--!--!--!--!--!--!--! COUP IMPOSSIBLE !--!--!--!--!--!--!--!--!\n\n");
        }

        fonctionFen(position);
        writeJS(position, score, "./web/refresh-data.json");    //écriture du fichier JSON de la position actuelle
        legaux=getCoupsLegaux(position);                                         //mise à jour des coups légaux
    }

    /*******************************************************/
    /*Fin de la partie                                     */
    /*******************************************************/

    printf("\n\t!--!--!--!--!--!--!--!--! PARTIE TERMINÉE !--!--!--!--!--!--!--!--!\n\n");

    /*******************************************************/
    /*Affichage du gagnant ou de l'égalité                 */
    /*******************************************************/

    if(score.nbJ > score.nbR)                                                               //si le score des jaunes est supérieur au score des rouges
    {
        printf("\n\t!--!--!--!--!--! LE JOUEUR JAUNE GAGNE !! !--!--!--!--!--!\n");         //affichage de la victoire des jaunes
    }
    else if(score.nbJ < score.nbR)                                                          //si le score des jaunes est inférieur au score des rouges
    {
        printf("\n\t!--!--!--!--!--! LE JOUEUR ROUGE GAGNE !! !--!--!--!--!--!\n");                                               //affichage de la victoire des rouges
    }
    else                                                                                    //si les scores sont égaux
    {
        if(score.nbJ5 > score.nbR5)
            printf("\n\t!--!--!--!--! LE JOUEUR JAUNE GAGNE GRACE A SES PILES DE 5 !--!--!--!--!");     //on prends en compte le nombre de pile de 5 de chaque joueur pour déterminer la victoire
            
        if(score.nbJ5 < score.nbR5)
            printf("\n\t!--!--!--!--! LE JOUEUR ROUGE GAGNE GRACE A SES PILES DE 5 !--!--!--!--!");
            
        else
            printf("\n\t!--!--!--!--! ÉGALITÉ !--!--!--!--!");                                //affichage de l'égalité
    }

}
    else
    {
        printf("La chaine est en cours d'intréprétation\n");
        position=interpreterFen(argv);
        fonctionFen(position);
    }
    return 0;
}

/***********************************************************/
/*Fonction d'écriture du fichier JSON                      */
/***********************************************************/

void writeJS(T_Position position, T_Score score, char chaine_JS[])
{

    FILE *fic ;
    fic = fopen(chaine_JS, "w");


    fprintf(fic,"traiterJson({\n");
    fprintf(fic, "%s;%d,\n", STR_TURN, position.trait);     //affichage du trait
    fprintf(fic, "%s;%d,\n",STR_SCORE_J, score.nbJ);        //affichage du score des jaunes
    fprintf(fic, "%s;%d,\n",STR_SCORE_J5, score.nbJ5);      //affichage du score des jaunes en pile de 5
    fprintf(fic, "%s;%d,\n",STR_SCORE_R, score.nbR);        //affichage du score des rouges
    fprintf(fic, "%s;%d,\n",STR_SCORE_R5, score.nbR5);      //affichage du score des rouges en pile de 5
    fprintf(fic, "%s;%d,\n",STR_BONUS_J, position.evolution.bonusJ);    //affichage du bonus des jaunes
    fprintf(fic, "%s;%d,\n",STR_MALUS_J, position.evolution.malusJ);    //affichage du malus des jaunes
    fprintf(fic, "%s;%d,\n",STR_BONUS_R, position.evolution.bonusR);    //affichage du bonus des rouges
    fprintf(fic, "%s;%d,\n",STR_MALUS_R, position.evolution.malusR);    //affichage du malus des rouges
    fprintf(fic,"\"cols\":[\n");

    for(int i=0; i < NBCASES; i++)
    {
        fprintf(fic,"\t {%s:%hhd, %s:%hhd},\n",STR_NB, position.cols[i].nb,STR_COULEUR, position.cols[i].couleur);
    }
        
        
    fprintf(fic,"]\n");
    fprintf(fic,"});");
    fclose(fic);
}

/***********************************************************/
/*Fonction d'écriture du format FEN                        */
/***********************************************************/

void fonctionFen(T_Position position)
{
    char chaine[100];
    int i,j=0,stock=0;
    char nbvide[10];

    for(i=0;i< NBCASES;i++)
    {
        if(position.cols[i].nb==0)
        {
            stock++;
            while(i + 1 < NBCASES && position.cols[i + 1].nb == 0)
            {
            stock++;
            i++;
            }

            snprintf(nbvide, sizeof(nbvide), "%d", stock);
            strcat(chaine, nbvide);
            j += strlen(nbvide);
            stock = 0;         
        }

        switch(position.cols[i].nb)
        {
            case 1:
                if(position.cols[i].couleur==JAU)
                {
                    chaine[j]='u';
                    j++;
                }
                else
                {
                    chaine[j]='U';
                    j++;
                }
                break;
            case 2:
                if(position.cols[i].couleur==JAU)
                {
                    chaine[j]='d';
                    j++;
                }
                else
                {
                    chaine[j]='D';
                    j++;
                }
                break;
            case 3:
                if(position.cols[i].couleur==JAU)
                {
                    chaine[j]='t';
                    j++;
                }
                else
                {
                    chaine[j]='T';
                    j++;
                }
                break;
            case 4:
                if(position.cols[i].couleur==JAU)
                {
                    chaine[j]='q';
                    j++;
                }
                else
                {
                    chaine[j]='Q';
                    j++;
                }
                break;
            case 5:
                if(position.cols[i].couleur==JAU)
                {
                    chaine[j]='c';
                    j++;
                }
                else
                {
                    chaine[j]='C';
                    j++;
                }
                break;
        }
        if(i==position.evolution.bonusJ)
        {
            chaine[j] = 'b';
            j++;
        }
        if(i==position.evolution.malusJ)
        {
            chaine[j] = 'm';
            j++;
        }
        if(i==position.evolution.bonusR)
        {
            chaine[j] = 'B';
            j++;
        }
        if(i==position.evolution.malusR)
        {
            chaine[j] = 'M';
            j++;
        }
    }

    chaine[j]=' ';
    if(position.trait==JAU)
    {
        chaine[j+1]='j';
    }
    else
    {
        chaine[j+1]='r';
    }
    chaine[j+2]='\0';

    printf("%s\n",chaine);
}

T_Position interpreterFen(char* argv[])
{
    T_Position position;
    int i,j;

    if (argv[2] == NULL) {
        printf("Erreur : pas assez d'arguments.\n");
        exit(1);
    }

    int len = strlen(argv[2]);
    if (len < 48) {
        printf("Erreur : l'argument n'est pas assez long.\n");
        exit(1);
    }

    for(i=0;i<NBCASES;i++)
    {
        if(argv[2][i] >= '0' && argv[2][i] <= '9')
        {
            position.cols[i].nb = argv[2][i] - '0';
            position.cols[i].couleur = VIDE;
        }
        switch(argv[2][i])
        {
            case 'u':
                position.cols[i].nb=1;
                position.cols[i].couleur=JAU;
                break;
            case 'd':
                position.cols[i].nb=2;
                position.cols[i].couleur=JAU;
                break;
            case 't':
                position.cols[i].nb=3;
                position.cols[i].couleur=JAU;
                break;
            case 'q':
                position.cols[i].nb=4;
                position.cols[i].couleur=JAU;
                break;
            case 'c':
                position.cols[i].nb=5;
                position.cols[i].couleur=JAU;
                break;
            case 'U':
                position.cols[i].nb=1;
                position.cols[i].couleur=ROU;
                break;
            case 'D':
                position.cols[i].nb=2;
                position.cols[i].couleur=ROU;
                break;
            case 'T':
                position.cols[i].nb=3;
                position.cols[i].couleur=ROU;
                break;
            case 'Q':
                position.cols[i].nb=4;
                position.cols[i].couleur=ROU;
                break;
            case 'C':
                position.cols[i].nb=5;
                position.cols[i].couleur=ROU;
                break;
            case 'b':
                position.evolution.bonusJ=i;
                break;
            case 'm':
                position.evolution.malusJ=i;
                break;
            case 'B':
                position.evolution.bonusR=i;
                break;
            case 'M':
                position.evolution.malusR=i;
                break;
            case 'j':
                position.trait=JAU;
                break;
            case 'r':
                position.trait=ROU;
                break;
        }
    }

    return position;
}
