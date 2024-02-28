/***********************************************************/
/*Group : La Valeur                                        */
/*Group number : 1                                         */
/*Group composition :                                      */
/* OUAZZANI CHAHDI Oualid                                  */
/* VOROBIEFF -- NAWROT Clément                             */
/* DESVIGNE Arthur                                         */
/* DEBROUCKER Baptiste                                     */
/*Date of original creation : 19/02/24                     */
/*Version : 1.0 - Without Debugging Mode                   */
/***********************************************************/

// Path: alpha-valon/cmj2023/standalone/standalone.c

/***********************************************************/
/*Library declaration. We will need other libraries from C */
/***********************************************************/

#include <stdio.h>                  //standard input output
#include <stdlib.h>                 //standard too
#include <string.h>                 //for char manipulation
#include "../include/avalam.h"      //for games functions
#include "../include/topologie.h"   //for the topologie of the game

/***********************************************************/
/*Prototype Declaration                                    */
/***********************************************************/

void writeJS(T_Position position, T_Score score, char chaine_JS[]); //prototype of the function that will write the JSON file
void fonctionFen(T_Position pos);                              //prototype of the function that will write the FEN format

/***********************************************************/
/*Principal function : main                               */
/***********************************************************/

int main()
{
    /*******************************************************/
    /*Variables declaration                                */
    /*******************************************************/

    T_Position position;    //position declaration
    T_Score score;          //score declaration
    T_Coup coup;            //mmoove declaration
    T_ListeCoups legaux;    //legal moves declaration
    octet stockage;         //octet declaration for the storage of the validity of a move
    int result;             //int declaration for the storage of the result of the scanf

    /*******************************************************/
    /*Initialization and starting of the game              */
    /*******************************************************/



    printf("\t!--!--!--!--!--!--!--!--! JOUONS À AVALAM !--!--!--!--!--!--!--!--!\n\n");

    printf0("_DEBUG_ RECUPERATION DE LA POSITION INITIALE\n");
    position = getPositionInitiale();    //position initialization
    printf0("_DEBUG_ RECUPERATION DES COURS LEGAUX\n");
    legaux = getCoupsLegaux(position);   //legal moves initialization
    printf0("_DEBUG_ EVALUATION DU SCORE\n");
    score = evaluerScore(position);      //move evaluation

    writeJS(position, score, "../web/refresh-data.json");    //writting of the JSON file of the initial position

    printf("\t!--!--!--!--!--!--!--!--! LA PARTIE COMMENCE !--!--!--!--!--!--!--!--!\n\n");

    printf("\tC'est au tour du joueur %d de jouer.\n", position.trait);    //showing the player who has to play
    fonctionFen(position);                                               //writting of the FEN format of the position

    /*******************************************************/
    /*Placement of bonus and malus                         */
    /*******************************************************/


    printf("\n\tAu tour du joueur 1 de donner la position de son bonus :");
    scanf("%hhd", &(position.evolution.bonusJ));            //entering the position of the bonus of the player 1

    while(position.cols[position.evolution.bonusJ].couleur==ROU)
    {
        printf("\n\tImpossible de placer le bonus sur une case occupée par un malus ou d'une autre couleur, veuillez choisir une autre case:");
        scanf("%hhd", &position.evolution.bonusJ);
    }
    writeJS(position, score, "../web/refresh-data.json");
   
    printf("\n\tAu tour du joueur 1 de donner la position de son malus :");
    scanf("%hhd", &position.evolution.malusJ);            //entering the position of the malus of the player 1

    while(position.cols[position.evolution.malusJ].couleur!=JAU || position.evolution.malusJ==position.evolution.bonusJ)
    {
        printf("\tImpossible de placer le bonus sur une case occupée par un malus ou d'une autre couleur, veuillez choisir une autre :");
        scanf("%hhd", &position.evolution.malusJ);
    }
    writeJS(position, score, "../web/refresh-data.json");

    printf("\n\tAu tour du joueur 2 de donner la position de son bonus :");
    scanf("%hhd", &position.evolution.bonusR);            //entering the position of the bonus of the player 2

    while(position.cols[position.evolution.bonusR].couleur!=ROU)
    {
        printf("\tImpossible de placer le bonus sur une case occupée par un malus ou d'une autre couleur, veuillez choisir une autre :");
        scanf("%hhd", &position.evolution.bonusR);
    }
    writeJS(position, score, "../web/refresh-data.json");

    printf("\n\tAu tour du joueur 2 de donner la position de son malus :");
    scanf("%hhd", &position.evolution.malusR);            //entering the position of the malus of the player 2

    while(position.cols[position.evolution.malusR].couleur!=ROU || position.evolution.malusR==position.evolution.bonusR)
    {
        printf("\tImpossible de placer le bonus sur une case occupée par un malus ou d'une autre couleur, veuillez choisir une autre :");
        scanf("%hhd", &position.evolution.malusR);
    }

    writeJS(position, score, "../web/refresh-data.json");    //writting finals results of placing bonus and malus
    fonctionFen(position);                                   //writting of the FEN format of the position
  

    /*******************************************************/
    /*Progress of the game                                 */
    /*First function while which will serve for looping    */
    /*******************************************************/

    while(legaux.nb != 0 || coup.origine>99 || coup.destination>99 || coup.origine<0 || coup.destination<0)
    {
        printf("\n\tC'est au tour du joueur %d de jouer.\n", position.trait);    //showing the player who has to play

        /***************************************************/
        /*Système de coups                                 */
        /***************************************************/

        printf("\n\t!--!--!--!--!--!--!--!--! QUELLE COUP VOULEZ-VOUS JOUER ? !--!--!--!--!--!--!--!--!\n\n");

        do 
        {
            printf("\n\tEntrez la case de départ : "); // asking for the case of departure
            result = scanf("%hhd", &coup.origine); // asking for the case of ending

                
            if (result != 1)        // if scanf didn't succeed to read a number, empty the input buffer
            {          
                printf("Entrée invalide. Veuillez entrer un nombre.\n");
                while (getchar() != '\n'); // emptying the input buffer
            }

        } 
        while (result != 1); // repeating until the input is a number

        do 
        {
            printf("\n\tEntrez la case d'arrivée : "); // asking for the case of departure
            result = scanf("%hhd", &coup.destination); // asking for the case of ending

                        
            if (result != 1)    // if scanf didn't succeed to read a number, empty the input buffer
            {
                printf("Entrée invalide. Veuillez entrer un nombre.\n");
                while (getchar() != '\n'); // emptying the input buffer
            }
        } 
        while (result != 1); // repeating until the input is a number
        stockage = estValide(position, coup.origine, coup.destination);    //stockage of the validity of the move

        /***************************************************/
        /*Checking if a move is valide or not              */
        /***************************************************/

        if(stockage == 1)                                                       //if the move is valid
        {
            position = jouerCoup(position, coup.origine, coup.destination);     //play the move
            score = evaluerScore(position);                                     //evaluate the score
            printf("\n\t!--!--!--!--!--!--!--!--! COUP JOUÉ AVEC SUCCÈS !--!--!--!--!--!--!--!--!\n\n");
            fonctionFen(position);
        }
        else                                                                    //if the move is not valid
        {
            printf("\n\t!--!--!--!--!--!--!--!--! COUP IMPOSSIBLE !--!--!--!--!--!--!--!--!\n\n");
        }

        writeJS(position, score, "../web/refresh-data.json");    //writting of the JSON file of the position after the move
        legaux=getCoupsLegaux(position);                                         //update of the legal moves
    }

    /*******************************************************/
    /*Finishing the game                                   */
    /*******************************************************/

    printf("\n\t!--!--!--!--!--!--!--!--! PARTIE TERMINÉE !--!--!--!--!--!--!--!--!\n\n");

    /*******************************************************/
    /*Showing the winner or the loser                      */
    /*******************************************************/

    if(score.nbJ > score.nbR)                                                               //si le score des jaunes est supérieur au score des rouges
    {
        printf("\n\t!--!--!--!--!--! LE JOUEUR JAUNE GAGNE !! !--!--!--!--!--!\n");         //affichage de la victoire des jaunes
    }
    else if(score.nbJ < score.nbR)                                                          //si le score des jaunes est inférieur au score des rouges
    {
        printf("\n\t!--!--!--!--!--! LE JOUEUR ROUGE GAGNE !! !--!--!--!--!--!\n");         //affichage de la victoire des rouges
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

/***********************************************************/
/*Writting function of the JSON File                       */
/***********************************************************/

void writeJS(T_Position position, T_Score score, char chaine_JS[])
{

    FILE *fic ;
    fic = fopen(chaine_JS, "w");

    if(fic == NULL)
    {
        printf("Erreur lors de l'ouverture du fichier");
        exit(1);
    }


    fprintf(fic,"traiterJson({\n");
    fprintf(fic, "%s:%d,\n", STR_TURN, position.trait);             //showing the player who has to play
    fprintf(fic, "%s:%d,\n",STR_SCORE_J, score.nbJ);                //showing the score of the yellow
    fprintf(fic, "%s:%d,\n",STR_SCORE_J5, score.nbJ5);              //showing the score of the yellow in pile of 5
    fprintf(fic, "%s:%d,\n",STR_SCORE_R, score.nbR);                //showing the score of the red
    fprintf(fic, "%s:%d,\n",STR_SCORE_R5, score.nbR5);              //showing the score of the red in pile of 5
    fprintf(fic, "%s:%d,\n",STR_BONUS_J, position.evolution.bonusJ);    //showing the bonus of the yellow
    fprintf(fic, "%s:%d,\n",STR_MALUS_J, position.evolution.malusJ);    //showing the malus of the yellow
    fprintf(fic, "%s:%d,\n",STR_BONUS_R, position.evolution.bonusR);    //showing the bonus of the red
    fprintf(fic, "%s:%d,\n",STR_MALUS_R, position.evolution.malusR);    //showing the malus of the red
    fprintf(fic,"\"cols\":[\n");

    for(int i=0; i < NBCASES; i++)
    {
        fprintf(fic,"\t {%s:%hhd, %s:%hhd},\n",STR_NB, position.cols[i].nb,STR_COULEUR, position.cols[i].couleur);
    }
        
        
    fprintf(fic,"]\n");
    fprintf(fic,"});");
    fclose(fic);
}

void fonctionFen(T_Position pos)
{
    char chaine[100];
    int i,j=0,stock=0;
    char nbvide[10];

    for(i=0;i< NBCASES;i++)
    {
        if(pos.cols[i].nb==0)
        {
            stock++;
            while(i + 1 < NBCASES && pos.cols[i + 1].nb == 0)
            {
            stock++;
            i++;
            }

            snprintf(nbvide, sizeof(nbvide), "%d", stock);
            strcat(chaine, nbvide);
            j += strlen(nbvide);
            stock = 0;         
        }

        switch(pos.cols[i].nb)
        {
            case 1:
                if(pos.cols[i].couleur==JAU)
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
                if(pos.cols[i].couleur==JAU)
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
                if(pos.cols[i].couleur==JAU)
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
                if(pos.cols[i].couleur==JAU)
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
                if(pos.cols[i].couleur==JAU)
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
        if(i==pos.evolution.bonusJ)
        {
            chaine[j] = 'b';
            j++;
        }
        if(i==pos.evolution.malusJ)
        {
            chaine[j] = 'm';
            j++;
        }
        if(i==pos.evolution.bonusR)
        {
            chaine[j] = 'B';
            j++;
        }
        if(i==pos.evolution.malusR)
        {
            chaine[j] = 'M';
            j++;
        }
    }

    chaine[j]=' ';
    if(pos.trait==JAU)
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
