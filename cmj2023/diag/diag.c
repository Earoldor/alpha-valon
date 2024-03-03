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

// Path: alpha-valon/cmj2023/diag/diag.c

/***********************************************************/
/*Library declaration. We will need other libraries from C */
/***********************************************************/

#include <stdio.h>                  //standard input output
#include <stdlib.h>                 //standard également
#include <string.h>                 //for the string manipulation
#include "../include/avalam.h"      //for game functions
#include "../include/topologie.h"   //for the topologie
#define MAXNOM 20
#define MAXCHAR 1000

/***********************************************************/
/*Prototype Declaration                                    */
/***********************************************************/

void fonctionFen(T_Position position);                              //prototype de la fonction d'écriture du format FEN (rajouté par Clément)

/***********************************************************/
/*Principal function : main                               */
/***********************************************************/

int main(int argc, char* argv[])
{
    /*******************************************************/
    /*Variables declaration                                */
    /*******************************************************/    

    char *chaineF=argv[2],*description="";;                         //chaineF is the FEN string, description is the description of the file
    char desc[MAXCHAR],chemin[MAXNOM]="diag_ressources.json";       //desc is the description of the file (entered by user in execution of that programm), chemin is the path of the file
    int rep,c,j,longueur,stockage;                                  //these are some variables for the programm
    octet i,stock=0;                                                //i is a variable for the loop, stock is a variable which surves to stock the number of empty cases
    T_Position position;                                            //position is the position of the game
    FILE *fic ;                                                     //fic is a file pointer

    /*******************************************************/
    /*Programm start                                       */
    /*******************************************************/

    if(argc != 3)                                                   //here, we verify that the number of arguments is correct
    {
        fprintf(stderr, "!--!--!--!--!--! ERREUR CRITIQUE : NOMBRE D'ARGUMENTS TROP IMPORTANT. SYNTAXE AUTORISÉE: EXE NUMDIAG FEN !--!--!--!--!--!\n");
        exit(EXIT_FAILURE);                                         //if not, we stop the programm
    }       

    printf0("_DEBUG_ CHECKING DU NOMBRE D'ARGUMENTS\n");

    /*******************************************************/
    /*Checking the turn                                    */
    /*******************************************************/

    longueur=strlen(argv[2]);                                       //longueur is the length of the string argv[2]

    if(argv[2][longueur-1]!='r' && argv[2][longueur-1]!='j')        //if the last character of the string argv[2] is not 'r' or 'j'
    {
        printf("!--!--!--!--!--! ERREUR CRITIQUE : LE TRAIT N'EST PAS RENSEIGNÉ !--!--!--!--!--!\n");  

        printf0("_DEBUG_ PAS DE TRAIT -> ARRET\n");

        exit(EXIT_FAILURE);                                         //we stop the programm
    }

    if(argv[2][longueur-1]=='r')                                    //if the last character of the string argv[2] is 'r'
        position.trait=ROU;                                         //the trait is for the red player
    else                                                            //if the last character of the string argv[2] is 'j'                
        position.trait=JAU;                                         //the trait is for the yellow player

    printf0("_DEBUG_ TRAIT -> ROUGE OU JAUNE\n");

    /*******************************************************/
    /*Asking of the description of the file                */
    /*******************************************************/

    //FILE *ficdesc;                                                 //we declare a file pointer                               

    //ficdesc=fopen("description.txt","r");                          //we open the file description.txt in read mode
    //fread(description,1,MAXCHAR,ficdesc);                          //we read the file description.txt which contains the description of the file
    //fclose(ficdesc);                                               //we close the file description.txt      

    printf0("_DEBUG_ RECUPERATION DESCRIPTION ENTRÉE PAR REDIRECTION\n");

    printf("!--!--!--!--!--! VEUILLEZ ENTREZ UNE DESCRIPTION POUR LE DIAGRAMME !--!--!--!--!--!\n");

    fgets(desc, MAXCHAR, stdin);                                    //we ask to the user to enter the description of the file
    strtok(desc, "\n");                                             //we remove the '\n' character at the end of the string because fgets() keeps it
    
    if(strcmp(desc,"")==0)                                          //if the description is empty
        printf("!--!--!--!--!--! DESCRIPTION NON RENSEIGNÉE !--!--!--!--!--!\n");

    printf0("_DEBUG_ RECUPERATION DESCRIPTION ENTRÉE PAR CLAVIER\n");

    /*******************************************************/
    /*Display of the characteristics of the file           */
    /*******************************************************/


    printf("!--!--!--!--!--! CARACTÉRISTIQUES DU FICHIER !--!--!--!--!--!\n");

    printf("!--! DIAGRAMME NUMÉRO : %s !--!\n", argv[1]);           //we display the number of the diagram
    printf("!--! CHAINE FEN : %s !--!\n",chaineF);                  //we display the FEN string
    
    if(strcmp(desc,"")==0)                                          //if the description is empty
        printf("!--! DESCRIPTION : %s !--!\n",description);         //we display the description enters via a redirection
    else                                                            //else
        printf("!--! DESCRIPTION : %s !--!\n",desc);                //we display the description enters via the keyboard
    
    printf("!--!--!--!--!--! FIN DES CARACTÉRISTIQUES !--!--!--!--!--!--!\n");

    printf0("_DEBUG_ AFFICHAGE DES CARACTERISTIQUES DU FICHIER\n");

    /*******************************************************/
    /*Asking of the file path                              */
    /*******************************************************/


    printf("!--!--!--!--!--! VOULEZ-VOUS CHANGER LE CHEMIN D'ACCES DU FICHIER ??? 1 POUR OUI, 0 POUR NON !--!--!--!--!--!\n");
    scanf("%d",&rep);                                                //we ask to the user if he wants to change the path of the file
    
    if(rep == 1)                                                    //if the user wants to change the path of the file
    {
        printf("!--!--!--!--!--! VEUILLEZ RENSEIGNER LE NOUVEAU CHEMIN D'ACCES !--!--!--!--!--!\n");

        while ((c = getchar()) != '\n' && c != EOF) { }             //we clear the buffer

        fgets(chemin, MAXNOM, stdin);                               //we ask to the user to enter the new path of the file
        strtok(chemin, "\n");                                       //we remove the '\n' character at the end of the string because fgets() keeps it
    }

    printf0("_DEBUG_ RECUPERATION DU CHEMIN D'ACCES DU FICHIER\n");

    /*******************************************************/
    /*Writting of the JSON File                            */
    /*******************************************************/

    fic = fopen(chemin, "w");                                       //we open the file in write mode

    fprintf(fic,"traiterJson({\n");                                 //we write the beginning of the file

    fprintf(fic, "%s:%s,\n", STR_NUMDIAG, argv[1]);                 //we write the number of the diagram

    if(strcmp(desc,"")==0)
        fprintf(fic, "%s:\"%s\",\n", STR_NOTES, description);       //we write the description of the file if the description by the keyboard is empty
    else
        fprintf(fic, "%s:\"%s\",\n", STR_NOTES, desc);              //we write the description of the file if the description by the keyboard is not empty

    fprintf(fic, "%s:%d,\n", STR_TURN,position.trait);              //we write the turn of the game

    fprintf(fic,"\"cols\":[\n");                                    //we write the beginning of the columns

    i=0,j=0;                                                        //we initialize the variables i and j

    while(i<NBCASES+1)                                              //while i is less than the number of cases
    {
        if(stock>0)                                                 //if stock is positive
        {
            if(i!=NBCASES && chaineF[j]!='B' && chaineF[j]!='b' && chaineF[j]!='M' && chaineF[j]!='m')                      //if i is different from the number of cases and the character is different from 'B', 'b', 'M' and 'm'
                fprintf(fic,"\t{%s:%d, %s:%d},\n",STR_NB, position.cols[i].nb=0,STR_COULEUR, position.cols[i].couleur=0);   //we write the number and the color of the case set to 0 with ','
            else if (chaineF[j]!='B' && chaineF[j]!='b' && chaineF[j]!='M' && chaineF[j]!='m')                              //else
                fprintf(fic,"\t{%s:%d, %s:%d}\n",STR_NB, position.cols[i].nb=0,STR_COULEUR, position.cols[i].couleur=0);    //we write the number and the color of the case set to 0 without ','

            stock--;                                                //we decrement stock
        }
        else if (chaineF[j]>='0' && chaineF[j]<='9')                //if the character is a number
        {
            if(chaineF[j+1]>='0' && chaineF[j+1]<='9')              //and if the next character is a number
            {
                stock = (chaineF[j+1]-'0')+10*(chaineF[j]-'0');     //we stock the number in stock
                j++;                                                //we increment j
            }
            else                                                    //else                              
            {
                stock = (chaineF[j]-'0');                           //we stock the number in stock
            }

            stockage=stock;                                         //we stock the value of stock in stockage
        }
        
        else                                                        //if the character is not a number
        {
            switch(chaineF[j])                                      //we enter in a switch case
            {
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
            case 'B':
                position.evolution.bonusR = i-stockage;              //we stock the value of i-stockage in the bonusR
                break;
            case 'b':
                position.evolution.bonusJ = 0;                      
                position.evolution.bonusJ = i-stockage;             //we stock the value of i-stockage in the bonusJ
                break;
            case 'M':
                position.evolution.malusR = i-stockage;             //we stock the value of i-stockage in the malusR
                break;  
            case 'm':
                position.evolution.malusJ = 0;
                position.evolution.malusJ = i-stockage;             //we stock the value of i-stockage in the malusJ
                break;
        }

        if(i!=NBCASES && chaineF[j]!='B' && chaineF[j]!='b' && chaineF[j]!='M' && chaineF[j]!='m')                      
            fprintf(fic,"\t{%s:%d, %s:%d},\n",STR_NB, position.cols[i].nb,STR_COULEUR, position.cols[i].couleur);           //we write the number and the color of the case with ','
        else if (chaineF[j]!='B' && chaineF[j]!='b' && chaineF[j]!='M' && chaineF[j]!='m')
            fprintf(fic,"\t{%s:%d, %s:%d}\n",STR_NB, position.cols[i].nb,STR_COULEUR, position.cols[i].couleur);            //we write the number and the color of the case without ','
    }

    i++;                                                            //we increment i

    if(stock==0)                                                    //if stock is equal to 0
        j++;                                                        //we increment j

    }

    fprintf(fic,"],\n");
    fprintf(fic, "%s:%d,\n",STR_BONUS_J, position.evolution.bonusJ);    //writing of the bonus of the yellow player
    fprintf(fic, "%s:%d,\n",STR_MALUS_J, position.evolution.malusJ);    //writing of the malus of the yellow player
    fprintf(fic, "%s:%d,\n",STR_BONUS_R, position.evolution.bonusR);    //writing of the bonus of the red player
    fprintf(fic, "%s:%d,\n",STR_MALUS_R, position.evolution.malusR);    //writing of the malus of the red player
    fprintf(fic,"});");
    fclose(fic);
    
    printf0("_DEBUG_ ECRITURE DU FICHIER JSON\n");

    printf0("_DEBUG_ FIN DU PROGRAMME\n");
    return 0;

}

/***********************************************************/
/*Writing function of position to FEN                      */
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
