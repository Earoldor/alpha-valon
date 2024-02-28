#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../include/avalam.h"
#include "../include/topologie.h"

void fonctionFen(T_Position position);
T_Position interpreterFen(char* argv[]);

int main(int argc, char *argv[])
{
    T_Position positionInitiale = getPositionInitiale();
    positionInitiale.cols[4].nb = 2;
    positionInitiale.cols[5].nb = 0;
    positionInitiale.cols[6].nb = 4;
    positionInitiale.evolution.bonusJ = 26;
    fonctionFen(positionInitiale);
    positionInitiale=interpreterFen(argv);
    fonctionFen(positionInitiale);
    return 0;

}

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