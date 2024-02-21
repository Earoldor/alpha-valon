/***********************************************************/
/*Groupe : L'Avaleur                                       */
/*Numéro du groupe : 1                                     */
/***********************************************************/

// Path: alpha-valon/cmj2023/standalone/standalone.c

/***********************************************************/
/*Déclaration des librairies. Nous aurons besoins des      */
/*librairies de base du langage C, ainsi que celle fournies*/
/***********************************************************/

#include <stdio.h>          //standard input output
#include <stdlib.h>         //standard également
#include <string.h>         //pour le traitement de chaine de caractère
#include "include/avalam.h" //pour les fonctions de jeu
#include "include/topologie.h"  //pour la topologie du plateau

/***********************************************************/
/*Fonction principale : main                               */
/***********************************************************/

int main()
{
    /*******************************************************/
    /*Déclaration des variables                            */
    /*******************************************************/

    T_Position position;    //déclaration de la position
    T_Score score;          //déclaration du score
    T_Coup coup;            //déclaration du coup
    T_ListeCoups legaux;    //déclaration des coups légaux (critère d'arret potentiel)
    octet stockage;         //déclaration d'un octet qui servira de stockage quelconque


    /*******************************************************/
    /*Initialisation et démarrage de la partie             */
    /*******************************************************/

    printf("\t!--!--!--!--!--!--!--!--! JOUONS À AVALAM !--!--!--!--!--!--!--!--!\n\n");

    position = getPositionInitiale();    //initialisation de la position
    legaux = getCoupsLegaux(position);   //initialisation des coups légaux
    score = evaluerScore(position);      //initialisation du score

    printf("\t!--!--!--!--!--!--!--!--! LA PARTIE COMMENCE !--!--!--!--!--!--!--!--!\n\n");

    printf("\t C'est au tour du joueur %d de jouer.\n", position.trait);    //affichage du joueur qui doit jouer


    return 0;
}

