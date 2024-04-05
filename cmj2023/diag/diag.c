/***********************************************************/
/*Group : La Valeur                                        */
/*Group number : 1                                         */
/*Group composition :                                      */
/* OUAZZANI CHAHDI Oualid                                  */
/* VOROBIEFF -- NAWROT Clément                             */
/* DESVIGNE Arthur                                         */
/* DEBROUCKER Baptiste                                     */
/*Date of original creation : 19/02/24                     */
/*The date of the last modification : 16/03/24             */
/*Version : 2.0 -                                          */
/***********************************************************/

// Path: alpha-valon/cmj2023/diag/diag.c

/***********************************************************/
/*Library declaration. We will need other libraries from C */
/***********************************************************/

#include <stdio.h>                  //standard input output
#include <stdlib.h>                 //standard également
#include <string.h>                 //for the string manipulation
#include <ctype.h>                  //for the character manipulation
#include <unistd.h>                 //for the file manipulation
#include <libgen.h>                 //for the file manipulation
#include "../include/avalam.h"      //for game functions
#include "../include/topologie.h"   //for the topologie
#define MAXNOM 100
#define MAXCHAR 1000
#define MAXLIGNE 10
#define MAXCONTENT 10000
#define COMPENSATION 20
#define MAXPATH 200


/***********************************************************/
/*Prototype Declaration                                    */
/***********************************************************/

void verificationFen(char *chaineFEN);
int chemin_valide(const char *chemin);
char* verificationDescription(char *d);

/***********************************************************/
/*Principal function : main                               */
/***********************************************************/

int main(int argc, char* argv[])
{
    /*******************************************************/
    /*Variables declaration                                */
    /*******************************************************/    

    char *chaineF=argv[2],description[MAXCHAR];                         //chaineF is the FEN string, description is the description of the file
    //char lignes[MAXLIGNE][MAXCHAR];                                     //lignes is a table of characters
    char desc[MAXCHAR],chemin[MAXPATH]="./web/data/diag_ressources.js",cheminModif[MAXPATH],temp[100];       //desc is the description of the file (entered by user in execution of that programm), chemin is the path of the file
    int j,longueur,stockage=0;                                      //these are some variables for the programm
    octet i,stock=0;                                                //i is a variable for the loop, stock is a variable which surves to stock the number of empty cases
    T_Position position;                                            //position is the position of the game
    FILE *fic ;                                                     //fic is a file pointer
    int drap=0,posGen=0,maxBonusMalus=1;
    int bonusJDrap=0,bonusRDrap=0,malusJDrap=0,malusRDrap=0;
    int stockJB=255,stockRB=255,stockJM=255,stockRM=255;
    int stockB=0,stockM=0,stockb=0,stockm=0;
    int posDecal=0,defaultPos=0;
    int comptage=0;
    char transform[3];
    int incremter_i=1;

    /*******************************************************/
    /*Programm start                                       */
    /*******************************************************/

    if(argc != 3)                                                   //here, we verify that the number of arguments is correct
    {
        fprintf(stderr, "!--!--!--!--!--! ERREUR CRITIQUE : NOMBRE D'ARGUMENTS TROP IMPORTANT. SYNTAXE AUTORISÉE: EXE NUMDIAG FEN !--!--!--!--!--!\n");
        exit(EXIT_FAILURE);                                         //if not, we stop the programm
    }       

    printf0("_DEBUG_ CHECKING DU NOMBRE D'ARGUMENTS\n");

    verificationFen(chaineF);                                       //we verify the FEN string

    /*******************************************************/
    /*Checking the turn                                    */
    /*******************************************************/

    longueur=strlen(argv[2]);                                       //longueur is the length of the string argv[2]

    if(argv[2][longueur-1]!='r' && argv[2][longueur-1]!='j')        //if the last character of the string argv[2] is not 'r' or 'j'
    {
        fprintf(stderr,"!--!--!--!--!--! ERREUR CRITIQUE : LE TRAIT N'EST PAS RENSEIGNÉ !--!--!--!--!--!\n");  

        printf0("_DEBUG_ PAS DE TRAIT -> ARRET\n");

        exit(EXIT_FAILURE);                                         //we stop the programm
    }

    if(argv[2][longueur-1]=='r')                                    //if the last character of the string argv[2] is 'r'
        position.trait=ROU;                                         //the trait is for the red player
    else                                                            //if the last character of the string argv[2] is 'j'                
        position.trait=JAU;                                         //the trait is for the yellow player

    printf0("_DEBUG_ TRAIT -> ROUGE OU JAUNE\n");

    /*******************************************************/
    /*Asking of the file path                              */
    /*******************************************************/

    printf("!--!--!--!--!--! VOULEZ-VOUS CHANGER LE NOM DU FICHIER ??? !--!--!--!--!--!\n");

  
    fgets(cheminModif,MAXPATH,stdin);                                      //we ask to the user if he wants to change the path of the file
    chemin_valide(cheminModif);

    if(strcmp(cheminModif,"\n")!=0)
    {
        strtok(cheminModif,"\n");
        strcpy(chemin,cheminModif);
    }



    printf("\n!--!--!--!--!--! CHEMIN DU FICHIER : %s !--!--!--!--!--!\n",chemin);

    printf0("_DEBUG_ RECUPERATION DU CHEMIN D'ACCES DU FICHIER\n");


    /*******************************************************/
    /*Asking of the description of the file                */
    /*******************************************************/

    printf0("_DEBUG_ RECUPERATION DESCRIPTION ENTRÉE PAR REDIRECTION\n");

    printf("!--!--!--!--!--! VEUILLEZ ENTREZ UNE DESCRIPTION POUR LE DIAGRAMME !--!--!--!--!--!\n");

    strcpy(desc,"");

    while(fgets(temp,sizeof(temp),stdin))
    {
        strtok(temp,"\n");
        strcat(temp,"<br/>");
        strcat(desc,temp);
    }
 
    verificationDescription(desc);
    //desc[strlen(desc)-1]='\0';

    if(strcmp(desc,"\n")==0 || strcmp(desc,"")==0)                                          //if the description is empty
    {
        strcpy(desc,"");
        printf("!--!--!--!--!--! DESCRIPTION NON RENSEIGNÉE !--!--!--!--!--!\n");
    }
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

    while(comptage!=NBCASES)                                              //while i is less than the number of cases
    {
        if(stock>0 && incremter_i!=0 || chaineF[j]==' ')                                                 //if stock is positive
        {   
            incremter_i=1;
            if(comptage!=NBCASES && incremter_i==1/*&& chaineF[j]!='B' && chaineF[j]!='b' && chaineF[j]!='M' && chaineF[j]!='m'*/)                      //if i is different from the number of cases and the character is different from 'B', 'b', 'M' and 'm'
            {
                fprintf(fic,"\t{%s:%d, %s:%d},\n",STR_NB, position.cols[i].nb=0,STR_COULEUR, position.cols[i].couleur=0);   //we write the number and the color of the case set to 0 with ','
                comptage++;
                printf0("\n--\n");
            }
            else if(incremter_i==1)//if (chaineF[j]!='B' && chaineF[j]!='b' && chaineF[j]!='M' && chaineF[j]!='m')                              //else
            {
                fprintf(fic,"\t{%s:%d, %s:%d}\n",STR_NB, position.cols[i].nb=0,STR_COULEUR, position.cols[i].couleur=0);    //we write the number and the color of the case set to 0 without ','
                comptage++;
                printf0("\n-FIN-\n");
            }
            stock--;                                                //we decrement stock
            //printf0("--\n");
            
        }
        else if (chaineF[j]>='0' && chaineF[j]<='9' && incremter_i!=0)                //if the character is a number
        {
            incremter_i=1;
            if(chaineF[j+1]>='0' && chaineF[j+1]<='9')              //and if the next character is a number
            {
                stock = (chaineF[j+1]-'0')+10*(chaineF[j]-'0');     //we stock the number in stock
                transform[0]=chaineF[j];
                transform[1]=chaineF[j+1];
                transform[2]='\0';
                j++;                                                //we increment j
            }
            else                                                    //else                              
            {
                stock = (chaineF[j]-'0');                           //we stock the number in stock
                transform[0]=chaineF[j];
                transform[1]='\0';
            }

            stockage=stockage+stock;                                         //we stock the value of stock in stockage
            posDecal=posDecal+atoi(transform);                               //we stock the value of transform in posDecal
            printf1("%d posdecalé\n",posDecal);
        }
        
        else                                                      //if the character is not a number
        {
                switch(chaineF[j])                                      //we enter in a switch case
                {
                case 'u':
                    incremter_i=1;
                    position.cols[i].nb = 1;
                    position.cols[i].couleur = JAU;

                    if(drap==1)
                    {
                        posGen++;
                        drap=0;
                    }
                    if(chaineF[j+1]=='B' || chaineF[j+1]=='b' || chaineF[j+1]=='M' || chaineF[j+1]=='m')
                        posGen++;
                    else
                        drap=1;
                    printf0("\nu\n");
                    break;
                case 'U':
                    incremter_i=1;
                    position.cols[i].nb = 1;
                    position.cols[i].couleur = ROU;

                    if(drap==1)
                    {
                        posGen++;
                        drap=0;
                    }
                    if(chaineF[j+1]=='B' || chaineF[j+1]=='b' || chaineF[j+1]=='M' || chaineF[j+1]=='m')
                        posGen++;
                    else
                        drap=1;
                    printf0("\nU\n");
                    break;
                case 'd':
                    incremter_i=1;
                    position.cols[i].nb = 2;
                    position.cols[i].couleur = JAU;

                    if(drap==1)
                    {
                        posGen++;
                        drap=0;
                    }
                    if(chaineF[j+1]=='B' || chaineF[j+1]=='b' || chaineF[j+1]=='M' || chaineF[j+1]=='m')
                        posGen++;
                    else
                        drap=1;
                    printf0("\nd\n");
                    break;
                case 'D':
                    incremter_i=1;
                    position.cols[i].nb = 2;
                    position.cols[i].couleur = ROU;

                    if(drap==1)
                    {
                        posGen++;
                        drap=0;
                    }
                    if(chaineF[j+1]=='B' || chaineF[j+1]=='b' || chaineF[j+1]=='M' || chaineF[j+1]=='m')
                        posGen++;
                    else
                        drap=1;
                    printf0("\nD\n");
                    break;
                case 't':
                    incremter_i=1;
                    position.cols[i].nb = 3;
                    position.cols[i].couleur = JAU;

                    if(drap==1)
                    {
                        posGen++;
                        drap=0;
                    }
                    if(chaineF[j+1]=='B' || chaineF[j+1]=='b' || chaineF[j+1]=='M' || chaineF[j+1]=='m')
                        posGen++;
                    else
                        drap=1;
                    printf0("\nt\n");
                    break;
                case 'T':
                    incremter_i=1;
                    position.cols[i].nb = 3;
                    position.cols[i].couleur = ROU;

                    if(drap==1)
                    {
                        posGen++;
                        drap=0;
                    }
                    if(chaineF[j+1]=='B' || chaineF[j+1]=='b' || chaineF[j+1]=='M' || chaineF[j+1]=='m')
                        posGen++;
                    else
                        drap=1;
                    printf0("\nT\n");
                    break;
                case 'q':
                    incremter_i=1;
                    position.cols[i].nb = 4;
                    position.cols[i].couleur = JAU;

                    if(drap==1)
                    {
                        posGen++;
                        drap=0;
                    }
                    if(chaineF[j+1]=='B' || chaineF[j+1]=='b' || chaineF[j+1]=='M' || chaineF[j+1]=='m')
                        posGen++;
                    else
                        drap=1;
                    printf0("\nq\n");
                    break;
                case 'Q':
                    incremter_i=1;
                    position.cols[i].nb = 4;
                    position.cols[i].couleur = ROU;

                    if(drap==1)
                    {
                        posGen++;
                        drap=0;
                    }
                    if(chaineF[j+1]=='B' || chaineF[j+1]=='b' || chaineF[j+1]=='M' || chaineF[j+1]=='m')
                        posGen++;
                    else
                        drap=1;
                    printf0("\nQ\n");
                    break;
                case 'c':
                    incremter_i=1;
                    position.cols[i].nb = 5;
                    position.cols[i].couleur = JAU;

                    if(drap==1)
                    {
                        posGen++;
                        drap=0;
                    }
                    if(chaineF[j+1]=='B' || chaineF[j+1]=='b' || chaineF[j+1]=='M' || chaineF[j+1]=='m')
                        posGen++;
                    else
                        drap=1;
                    printf0("\nc\n");
                    break;
                case 'C':
                    incremter_i=1;
                    position.cols[i].nb = 5;
                    position.cols[i].couleur = ROU;

                    if(drap==1)
                    {
                        posGen++;
                        drap=0;
                    }
                    if(chaineF[j+1]=='B' || chaineF[j+1]=='b' || chaineF[j+1]=='M' || chaineF[j+1]=='m')
                        posGen++;
                    else
                        drap=1;
                    printf0("\nC\n");
                    break;
                case 'B':
                    incremter_i=1;
                    stockB++;
                    printf1("%d DINST\n",stockB);
                    printf1("%d DECALAGE\n",stockage);
                    printf1("%d POSDECALE\n",posDecal);
                    if(bonusRDrap<maxBonusMalus)
                    {
                        if(stockB==1)
                        {
                            if(stockage!=0)
                            {
                                printf1("%d defaultPos\n",defaultPos);
                                if(defaultPos>=2)
                                {
                                    defaultPos=defaultPos-(defaultPos-1);
                                }
                                position.evolution.bonusR = posGen + posDecal + defaultPos;              //we stock the value of i-stockage in the bonusR
                                stockRB = position.evolution.bonusR-1;
                                defaultPos=0;
                                printf1("%d :",position.evolution.bonusR);    //writing of the bonus of the red player
                                printf1("%d",stockRB);
                                printf0("\nBONUS DÉCALÉ CAR STOCKAGE NON NUL\n");
                            }
                            else
                            {
                                printf1("%d defaultPos\n",defaultPos);
                                if(defaultPos>=2)
                                {
                                    defaultPos=defaultPos-(defaultPos-1);
                                }
                                position.evolution.bonusR = posGen + defaultPos;              //we stock the value of i-stockage in the bonusR
                                stockRB = position.evolution.bonusR-1;
                                defaultPos=0;
                                printf1("%d :",position.evolution.bonusR);    //writing of the bonus of the red player
                                printf1("%d",stockRB);
                                printf0("\nBONUS PAS DÉCALÉ\n");
                            }
                        }
                        else
                            break;
                    }   
                    break;
                case 'b':
                    incremter_i=1;
                    stockb++;
                    printf1("%d DECALAGE\n",stockage);
                    printf1("%d POSDECALE\n",posDecal);
                    if(bonusJDrap<maxBonusMalus)
                    {
                        if(stockb==1)
                        {
                            if(stockage!=0)
                            {
                                printf1("%d defaultPos\n",defaultPos);
                                if(defaultPos>=2)
                                {
                                    defaultPos=defaultPos-(defaultPos-1);
                                }
                                printf1("%d defaultPos\n",defaultPos);
                                position.evolution.bonusJ = posGen + posDecal + defaultPos;              //we stock the value of i-stockage in the bonusR
                                stockJB = position.evolution.bonusJ-1;
                                defaultPos=0;
                                printf1("%d :",position.evolution.bonusJ);    //writing of the bonus of the red player
                                printf1("%d",stockJB);
                                printf0("\nBONUS DÉCALÉ CAR STOCKAGE NON NUL\n");
                            }
                            else
                            {
                                printf1("%d defaultPos\n",defaultPos);
                                if(defaultPos>=2)
                                {
                                    defaultPos=defaultPos-(defaultPos-1);
                                }
                                position.evolution.bonusJ = posGen + defaultPos;              //we stock the value of i-stockage in the bonusR
                                stockJB = position.evolution.bonusJ-1;
                                defaultPos=0;
                                printf1("%d :",position.evolution.bonusJ);    //writing of the bonus of the red player
                                printf1("%d",stockJB);
                                printf0("\nBONUS PAS DÉCALÉ\n");
                            }
                        }
                        else
                            break;
                    }             
                    break;
                case 'M':
                    incremter_i=1;
                    stockM++;
                    printf1("%d DECALAGE\n",stockage);
                    printf1("%d POSDECALE\n",posDecal);
                    if(malusRDrap<maxBonusMalus)
                    {
                        if(stockM==1)
                        {
                            if(stockage != 0)
                            {
                                printf1("%d defaultPos\n",defaultPos);
                                if(defaultPos>=2)
                                {
                                    defaultPos=defaultPos-(defaultPos-1);
                                }
                                position.evolution.malusR = posGen + posDecal + defaultPos;              //we stock the value of i-stockage in the malusR
                                stockRM = position.evolution.malusR-1;
                                defaultPos=0;
                                printf1("%d :",position.evolution.malusR);    //writing of the bonus of the red player
                                printf1("%d",stockRM);
                                printf0("\nMALUS DÉCALÉ CAR STOCKAGE NON NUL\n");
                            }
                            else
                            {
                                printf1("%d defaultPos\n",defaultPos);
                                if(defaultPos>=2)
                                {
                                    defaultPos=defaultPos-(defaultPos-1);
                                }
                                position.evolution.malusR = posGen + defaultPos;              //we stock the value of i-stockage in the malusR
                                stockRM = position.evolution.malusR-1;
                                defaultPos=0;
                                printf1("%d :",position.evolution.malusR);    //writing of the bonus of the red player
                                printf1("%d",stockRM);
                                printf0("\nMALUS PAS DÉCALÉ\n");
                            }
                        }
                        else
                            break;
                    }
                    break;  
                case 'm':
                    incremter_i=1;
                    stockm++;
                    printf1("%d DECALAGE\n",stockage);
                    printf1("%d POSDECALE\n",posDecal);
                    if(malusJDrap<maxBonusMalus)
                    {
                        if(stockm==1)
                        {
                            if(stockage != 0)
                            {
                                printf1("%d defaultPos\n",defaultPos);
                                if(defaultPos>=2)
                                {
                                    defaultPos=defaultPos-(defaultPos-1);
                                }
                                position.evolution.malusJ = posGen + posDecal + defaultPos;              //we stock the value of i-stockage in the malusJ
                                stockJM = position.evolution.malusJ-1;
                                defaultPos=0;
                                printf1("%d :",position.evolution.malusJ);    //writing of the bonus of the red player
                                printf1("%d",stockJM);
                                printf0("\nMALUS DÉCALÉ CAR STOCKAGE NON NUL\n");
                            }
                            else
                            {
                                printf1("%d defaultPos\n",defaultPos);
                                if(defaultPos>=2)
                                {
                                    defaultPos=defaultPos-(defaultPos-1);
                                }
                                position.evolution.malusJ = posGen + defaultPos;              //we stock the value of i-stockage in the malusJ
                                stockJM = position.evolution.malusJ-1;
                                defaultPos=0;
                                printf1("%d :",position.evolution.malusJ);    //writing of the bonus of the red player
                                printf1("%d",stockJM);
                                printf0("\nMALUS PAS DÉCALÉ\n");
                            }
                        }
                        else
                            break;
                    }
                    break;
                    default:
                        incremter_i=0;
                        defaultPos++;
                        stock=0;
                        printf0("\nDEFAULT\n");
                        break;
            
        }
        
        if(incremter_i==1 && comptage!=NBCASES && chaineF[j]!='B' && chaineF[j]!='b' && chaineF[j]!='M' && chaineF[j]!='m')
        {                     
            fprintf(fic,"\t{%s:%d, %s:%d},\n",STR_NB, position.cols[i].nb,STR_COULEUR, position.cols[i].couleur);           //we write the number and the color of the case with ','
            comptage++;
            printf0("\n::plein::\n");
        } 
        else if ( incremter_i==1 && chaineF[j]!='B' && chaineF[j]!='b' && chaineF[j]!='M' && chaineF[j]!='m')
        {   
            fprintf(fic,"\t{%s:%d, %s:%d}\n",STR_NB, position.cols[i].nb,STR_COULEUR, position.cols[i].couleur);            //we write the number and the color of the case without ','
            comptage++;
            printf0("\n::plein_fin::\n");
        }
    }
    //if(chaineF[j]>='A' && chaineF[j]<='z' || chaineF[j]>='0' && chaineF[j]<='9')
    i++;                                                            //we increment i
    if(stock==0 && chaineF[j]!=' ')                                                    //if stock is equal to 0
        j++;                                                        //we increment j


    }
    

    fprintf(fic,"],\n");
    fprintf(fic, "%s:\"%s\",\n", STR_FEN, chaineF);                     //we write the FEN string
    fprintf(fic, "%s:%d,\n",STR_BONUS_J, stockJB);    //writing of the bonus of the yellow player
    fprintf(fic, "%s:%d,\n",STR_MALUS_J, stockJM);    //writing of the malus of the yellow player
    fprintf(fic, "%s:%d,\n",STR_BONUS_R, stockRB);    //writing of the bonus of the red player
    fprintf(fic, "%s:%d,\n",STR_MALUS_R, stockRM);    //writing of the malus of the red player
    fprintf(fic,"});");
    fclose(fic);
    
    printf0("_DEBUG_ ECRITURE DU FICHIER JSON\n");

    printf0("_DEBUG_ FIN DU PROGRAMME\n");
    return 0;

}

void verificationFen(char *chaineFEN)
{
    int i,j=0;
    
    if(j>1)
    {
        perror("!--!--!--!--!--! ERREUR CRITIQUE : TROP D'ESPACES DANS LA CHAINE FEN !--!--!--!--!--!\n");
        exit(1);
    }

    if(chaineFEN[0] == 'b' || chaineFEN[0] == 'B' || chaineFEN[0] == 'm' || chaineFEN[0] == 'M')
    {
        perror("!--!--!--!--!--! ERREUR CRITIQUE : LA CHAINE FEN NE PEUT PAS COMMENCER PAR UN B, b, M OU m !--!--!--!--!--!\n");
        exit(1);
    }

    for(i=0;i<strlen(chaineFEN);i++)
    {
        if(!isalpha(chaineFEN[i]) && !isdigit(chaineFEN[i]) && chaineFEN[i]!= ' ')
        {
            perror("!--!--!--!--!--! CARACTERE NON AUTORISÉ DANS LA CHAINE FEN !--!--!--!--!--!\n");
            exit(1);
        }

        if(chaineFEN[i]==' ')
        {
            j++;
        }
        if(j>1)
        {
            perror("!--!--!--!--!--! ERREUR CRITIQUE : TROP D'ESPACES DANS LA CHAINE FEN !--!--!--!--!--!\n");
            exit(1);
        }

    }
}

int chemin_valide(const char *chemin) 
{
    char *copieChemin = strdup(chemin);                                               // Copie le chemin d'accès
    char *cheminDir=dirname(copieChemin);                                               // Vérifie si le chemin d'accès existe

    if (access(cheminDir, F_OK) != 0) 
    {   
        printf("!--!--!--! LE CHEMIN N'EXISTE PAS !--!--!--!--!\n");                                                // Le chemin d'accès existe
        exit(1);
    } else {
                                                        // Le chemin d'accès n'existe pas
        return 0;
    }
}

char* verificationDescription(char *d)
{
    int i;
    for(i=0;i<strlen(d);i++)
    {
        if(d[i]=='"' || d[i]=='\'' || d[i]=='/')
        {
            d[i]=' ';
        }
    }

    return d;
}