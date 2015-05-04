#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>

#include "constantes.h"
#include "fichiers.h"

void chargerNiveau(int* plateau[NBR_BLOC_HAUTEUR][NBR_BLOC_LARGEUR], int numNiveau)
{
    FILE* fichier = NULL;
    char ligneFichier[NBR_BLOC_LARGEUR * NBR_BLOC_HAUTEUR + 1] = {0};
    int i = 0, j = 0;

    switch(numNiveau)
    {
        case 1:
            fichier = fopen("niveaux1.txt", "r");
            break;
        case 2:
            fichier = fopen("niveaux2.txt", "r");
            break;
        case 3:
            fichier = fopen("niveaux3.txt", "r");
            break;
        case 4:
            fichier = fopen("niveaux4.txt", "r");
            break;
        case 5:
            fichier = fopen("niveaux5.txt", "r");
            break;
        case 6:
            fichier = fopen("niveaux6.txt", "r");
            break;
        case 7:
            fichier = fopen("niveaux7.txt", "r");
            break;
        case 8:
            fichier = fopen("niveaux8.txt", "r");
            break;
        case 9:
            fichier = fopen("niveaux9.txt", "r");
            break;
        case 10:
            fichier = fopen("niveaux10.txt", "r");
            break;
        case 11:
            fichier = fopen("niveaux11.txt", "r");
            break;
        case 12:
            fichier = fopen("niveaux12.txt", "r");
            break;
        case 13:
            fichier = fopen("niveaux13.txt", "r");
            break;
        case 14:
            fichier = fopen("niveaux14.txt", "r");
            break;
        case 15:
            fichier = fopen("niveaux15.txt", "r");
            break;
        case 16:
            fichier = fopen("niveaux16.txt", "r");
            break;
    }

    fgets(ligneFichier, NBR_BLOC_LARGEUR * NBR_BLOC_HAUTEUR + 1, fichier);

    for (i = 0 ; i < NBR_BLOC_HAUTEUR ; i++)
    {
        for (j = 0 ; j < NBR_BLOC_LARGEUR ; j++)
        {
            switch (ligneFichier[(i * NBR_BLOC_HAUTEUR) + j])
            {
                case '0':
                    plateau[i][j] = 0;
                    break;
                case '1':
                    plateau[i][j] = 1;
                    break;
                case '2':
                    plateau[i][j] = 2;
                    break;
                case '3':
                    plateau[i][j] = 3;
                    break;
                case '4':
                    plateau[i][j] = 4;
                    break;
                case '5':
                    plateau[i][j] = 5;
                    break;
                case '6':
                    plateau[i][j] = 6;
                    break;
                case '7':
                    plateau[i][j] = 7;
                    break;
                case '8':
                    plateau[i][j] = 8;
                    break;
                case '9':
                    plateau[i][j] = 9;
                    break;
                default:
                    break;
            }
        }
    }
    fclose(fichier);
}

void sauvegarderNiveau(int plateau[NBR_BLOC_HAUTEUR][NBR_BLOC_LARGEUR], int numNiveau)
{
    FILE* fichier = NULL;
    int i = 0, j = 0;
    switch (numNiveau)
    {
        case 1:
            fichier = fopen("niveaux1.txt", "w");
            break;
        case 2:
            fichier = fopen("niveaux2.txt", "w");
            break;
        case 3:
            fichier = fopen("niveaux3.txt", "w");
            break;
        case 4:
            fichier = fopen("niveaux4.txt", "w");
            break;
        case 5:
            fichier = fopen("niveaux5.txt", "w");
            break;
        case 6:
            fichier = fopen("niveaux6.txt", "w");
            break;
        case 7:
            fichier = fopen("niveaux7.txt", "w");
            break;
        case 8:
            fichier = fopen("niveaux8.txt", "w");
            break;
        case 9:
            fichier = fopen("niveaux9.txt", "w");
            break;
        case 10:
            fichier = fopen("niveaux10.txt", "w");
            break;
        case 11:
            fichier = fopen("niveaux11.txt", "w");
            break;
        case 12:
            fichier = fopen("niveaux12.txt", "w");
            break;
        case 13:
            fichier = fopen("niveaux13.txt", "w");
            break;
        case 14:
            fichier = fopen("niveaux14.txt", "w");
            break;
        case 15:
            fichier = fopen("niveaux15.txt", "w");
            break;
        case 16:
            fichier = fopen("niveaux16.txt", "w");
            break;
    }

    for (i = 0 ; i < NBR_BLOC_HAUTEUR ; i++)
    {
        for (j = 0 ; j < NBR_BLOC_LARGEUR ; j++)
        {
            fprintf(fichier, "%d", plateau[i][j]);
        }
    }
    fclose(fichier);
}

void lireNiveauMax(int* numNiveau)
{
    FILE* fichier = NULL;
    fichier = fopen("niveauMax.txt", "r");
    int niveauMax = 0;

    rewind(fichier);

    niveauMax = fgetc(fichier);
    *numNiveau = niveauMax - '0';

    niveauMax = fgetc(fichier);
    if(niveauMax != EOF)
    {
      *numNiveau = *numNiveau * 10 + (niveauMax - '0');
    }

    fclose(fichier);
}

void ecrireNiveauMax(int* numNiveau)
{
    FILE* fichier = NULL;
    fichier = fopen("niveauMax.txt", "w");

    fprintf(fichier,"%d", *numNiveau);

    fclose(fichier);
}
