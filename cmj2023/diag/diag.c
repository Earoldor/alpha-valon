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

void writeJS(T_Position position, T_Score score, char chaine_JS[], char desc[], int numDiag); //prototype de la fonction d'écriture du fichier JSON
void fonctionFen(T_Position position);                              //prototype de la fonction d'écriture du format FEN
T_Position interpreterFen(char* chaineFEN);                                //prototype de la fonction d'interprétation du format FEN
T_Position lireFEN(char *chaineFEN);
/***********************************************************/
/*Fonction principale : main                               */
/***********************************************************/

int main(int argc, char* argv[])
{
    char *chaineF=argv[2]; //chaineFEN est la chaine de caractère qui contient la FEN
    char desc[MAXCHAR];             //desc est la chaine de caractère qui contient la description du fichier
    int rep,c;
    char chemin[MAXNOM];
    T_Position position;
    T_Score score=evaluerScore(position);
    


    if(argc != 3)   //Condition d'erreur pour le nombre d'arguments passé en ligne de commandes
    {
        fprintf(stderr, "!--!--!--!--!--! ERREUR CRITIQUE : NOMBRE D'ARGUMENTS TROP IMPORTANT. SYNTAXE AUTORISÉE: EXE NUMDIAG FEN !--!--!--!--!--!\n");
        exit(EXIT_FAILURE);
    }

    printf("!--!--!--!--!--! VEUILLEZ ENTREZ UNE DESCRIPTION POUR LE DIAGRAMME !--!--!--!--!--!\n");
    fgets(desc, MAXCHAR, stdin); //on demande à l'utilisateur de rentrers la description du fichier
    strtok(desc, "\n"); //on supprime le retour à la ligne du au fgets
    
    if(desc==NULL)
        printf("!--!--!--!--!--! DESCRIPTION NON RENSEIGNÉE !--!--!--!--!--!\n");

    printf("!--!--!--!--!--! CARACTÉRISTIQUES DU FICHIER !--!--!--!--!--!\n");
    printf("!--! DIAGRAMME NUMÉRO : %s !--!\n", argv[1]);
    printf("!--! CHAINE FEN : %s !--!\n",chaineF);
    printf("!--! DESCRIPTION : %s !--!\n",desc);
    printf("!--!--!--!--!--! FIN DES CARACTÉRISTIQUES !--!--!--!--!--!--!\n");

    position = lireFEN(chaineF); //on interprète la chaine FEN

    printf("!--!--!--!--!--! VOULEZ-VOUS CHANGER LE CHEMIN D'ACCES DU FICHIER ??? 1 POUR OUI, 0 POUR NON !--!--!--!--!--!\n");
    scanf("%d",&rep);
    
    if(rep == 1)
    {
        printf("!--!--!--!--!--! VEUILLEZ RENSEIGNER LE NOUVEAU CHEMIN D'ACCES !--!--!--!--!--!\n");
        while ((c = getchar()) != '\n' && c != EOF) { }
        fgets(chemin, MAXNOM, stdin);
        //strtok(chemin, "\n");
        writeJS(position,score, chemin,desc, atoi(argv[1]));
    }

    else
    {
        writeJS(position,score, "diagramme.js",desc, atoi(argv[1]));
    }

}
/***********************************************************/
/*Fonction d'écriture du fichier JSON                      */
/***********************************************************/

void writeJS(T_Position position, T_Score score, char chaine_JS[], char desc[], int numDiag)
{

    FILE *fic ;
    fic = fopen(chaine_JS, "w");


    fprintf(fic,"traiterJson({\n");
    fprintf(fic, "%s:%d,\n", STR_NUMDIAG, numDiag);             //affichage du numéro du diagramme
    fprintf(fic, "%s:\"%s\",\n", STR_NOTES, desc);                //affichage de la description
    fprintf(fic, "%s:%d,\n", STR_TURN, position.trait);     //affichage du trait
    fprintf(fic, "%s:%d,\n",STR_SCORE_J, score.nbJ);        //affichage du score des jaunes
    fprintf(fic, "%s:%d,\n",STR_SCORE_J5, score.nbJ5);      //affichage du score des jaunes en pile de 5
    fprintf(fic, "%s:%d,\n",STR_SCORE_R, score.nbR);        //affichage du score des rouges
    fprintf(fic, "%s:%d,\n",STR_SCORE_R5, score.nbR5);      //affichage du score des rouges en pile de 5
    fprintf(fic, "%s:%d,\n",STR_BONUS_J, position.evolution.bonusJ);    //affichage du bonus des jaunes
    fprintf(fic, "%s:%d,\n",STR_MALUS_J, position.evolution.malusJ);    //affichage du malus des jaunes
    fprintf(fic, "%s:%d,\n",STR_BONUS_R, position.evolution.bonusR);    //affichage du bonus des rouges
    fprintf(fic, "%s:%d,\n",STR_MALUS_R, position.evolution.malusR);    //affichage du malus des rouges
    fprintf(fic,"\"cols\":[\n");

    for(int i=0; i < NBCASES; i++)
    {
        if(position.cols[i].nb != 0 && position.cols[i].nb != 1 && position.cols[i].nb!=2 &&  position.cols[i].nb!=3 && position.cols[i].nb!=4 &&position.cols[i].nb!=5)
        {
            position.cols[i].nb=0; position.cols[i].couleur=0;
            fprintf(fic,"\t {%s:%hhd, %s:%hhd},\n",STR_NB, position.cols[i].nb,STR_COULEUR, position.cols[i].couleur);
        }
        else
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
    char nbvide[1000000];

    for(i=0;i< NBCASES;i++)
    {
        if(position.cols[i].nb==0)
        {
            stock++;
            if(i==position.evolution.bonusJ || i==position.evolution.malusJ || i==position.evolution.bonusR || i==position.evolution.malusR)
            {
               stock=0;
            }

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

/***********************************************************/
/*Fonction d'interprétation de la chaine FEN               */
/***********************************************************/

T_Position interpreterFen(char* chaineFEN)
{
    T_Position position;
    int i,j;
    int stock=0;
    char temp[100];

    if (chaineFEN == NULL) {
        printf("Erreur : pas assez d'arguments.\n");
        exit(1);
    }

    /* 
    for(i=0;chaineFEN[i]!='\0';i++)
    {

        if(chaineFEN[i] >= '0' && chaineFEN[i] <= '9')
        {
            position.cols[i].nb=0;
            temp[0] = chaineFEN[i];
            if(chaineFEN[i+1] >= '0' && chaineFEN[i+1] <= '9')
            {
                temp[1] = chaineFEN[i+1];
                temp[2] = '\0';
                i++;
            }
            else
            {
                temp[1] = '\0';
            }
            stock=atoi(temp);

            for(j=i;j<i+stock-2;j++)
            {
                position.cols[j].nb=0;
                position.cols[j].couleur=0;
            }
            j=i+stock;
        }
        else
        {
            j=(i+stock);
        }
        switch(chaineFEN[i])
        {
            case 'u':
                position.cols[j].nb=1;
                position.cols[j].couleur=JAU;
                break;
            case 'd':
                position.cols[j].nb=2;
                position.cols[j].couleur=JAU;
                break;
            case 't':
                position.cols[j].nb=3;
                position.cols[j].couleur=JAU;
                break;
            case 'q':

                position.cols[j].nb=4;
                position.cols[j].couleur=JAU;
                break;
            case 'c':
                position.cols[j].nb=5;
                position.cols[j].couleur=JAU;
                break;
            case 'U':
                position.cols[j].nb=1;
                position.cols[j].couleur=ROU;
                break;
            case 'D':
                position.cols[j].nb=2;
                position.cols[j].couleur=ROU;
                break;
            case 'T':
                position.cols[j].nb=3;
                position.cols[j].couleur=ROU;
                break;
            case 'Q':
                position.cols[j].nb=4;
                position.cols[j].couleur=ROU;
                break;
            case 'C':
                position.cols[j].nb=5;
                position.cols[j].couleur=ROU;
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
    */

   for(i = 0; i < NBCASES && chaineFEN[i] != '\0'; i++) {
    switch(chaineFEN[i]) {
       case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8': case '9':
        temp[0] = chaineFEN[i];
        temp[1] = '\0';

        // Check if the next character is also a digit
        if(chaineFEN[i+1] >= '0' && chaineFEN[i+1] <= '9') 
        {
            temp[1] = chaineFEN[i+1];
            temp[2] = '\0';
            i++; // Skip the next character as we have already processed it
        }

    stock = atoi(temp);

    for(int j = 0; j < stock; j++) 
    {
        position.cols[i+j].nb = 0;
        position.cols[i+j].couleur = 0;
    }

    i += stock - 1;
    break;
        case 'u':
            position.cols[i].nb = 1;
            position.cols[i].couleur = JAU;
            break;
        case 'U':
            position.cols[i].nb = 1;
            position.cols[i].couleur = ROU;
            break;
        case 'd':
            position.cols[i].nb = 2;
            position.cols[i].couleur = JAU;
            break;
        case 'D':
            position.cols[i].nb = 2;
            position.cols[i].couleur = ROU;
            break;
        case 't':
            position.cols[i].nb = 3;
            position.cols[i].couleur = JAU;
            break;
        case 'T':
            position.cols[i].nb = 3;
            position.cols[i].couleur = ROU;
            break;
        case 'q':
            position.cols[i].nb = 4;
            position.cols[i].couleur = JAU;
            break;
        case 'Q':
            position.cols[i].nb = 4;
            position.cols[i].couleur = ROU;
            break;
        case 'c':
            position.cols[i].nb = 5;
            position.cols[i].couleur = JAU;
            break;
        case 'C':
            position.cols[i].nb = 5;
            position.cols[i].couleur = ROU;
            break;
        case 'r':
            position.trait = ROU;
            break;
        case 'j':
            position.trait = JAU;
            break;
    }
}
    return position;
}


T_Position lireFEN(char *chaineFEN)
{
    int i=0,j=0,stock,save;
    char intstock[3];
    T_Position position;

    while(chaineFEN[i]!='\0')
    {
        save=j;
        if(chaineFEN[i]>='0' && chaineFEN[i]<='9')
        {
            if(chaineFEN[i+1]>='0' && chaineFEN[i+1]<='9')
            {
                intstock[0]=chaineFEN[i];
                intstock[1]=chaineFEN[i+1];
                intstock[2]='\0';

                stock=atoi(intstock);
                for(j=save;j<=stock;j++)
                {
                    position.cols[j].nb=0;
                    position.cols[j].couleur=0;
                }
                i=i+2;
            }
            else
            {
                intstock[0]=chaineFEN[i];
                intstock[1]='\0';
                stock=atoi(intstock);
                for(j=save;j<=stock;j++)
                {
                    position.cols[j].nb=0;
                    position.cols[j].couleur=0;
                }
                i++;
            }
        }
        else
        {
            switch(chaineFEN[i])
            {
                case 'u':
                    position.cols[j].nb=1;
                    position.cols[j].couleur=JAU;
                    break;
                case 'd':
                    position.cols[j].nb=2;
                    position.cols[j].couleur=JAU;
                    break;
                case 't':
                    position.cols[j].nb=3;
                    position.cols[j].couleur=JAU;
                    break;
                case 'q':
                    position.cols[j].nb=4;
                    position.cols[j].couleur=JAU;
                    break;
                case 'c':
                    position.cols[j].nb=5;
                    position.cols[j].couleur=JAU;
                    break;
                case 'U':
                    position.cols[j].nb=1;
                    position.cols[j].couleur=ROU;
                    break;
                case 'D':
                    position.cols[j].nb=2;
                    position.cols[j].couleur=ROU;
                    break;
                case 'T':
                    position.cols[j].nb=3;
                    position.cols[j].couleur=ROU;
                    break;
                case 'Q':
                    position.cols[j].nb=4;
                    position.cols[j].couleur=ROU;
                    break;
                case 'C':
                    position.cols[j].nb=5;
                    position.cols[j].couleur=ROU;
                    break;

                case 'b':
                    position.evolution.bonusJ=j;
                    break;
                
                case 'm':
                    position.evolution.malusJ=j;
                    break;
                
                case 'B':
                    position.evolution.bonusR=j;
                    break;
                
                case 'M':
                    position.evolution.malusR=j;
                    break;
            }
            j++;
            i++;
        }
    }
    return position;
}