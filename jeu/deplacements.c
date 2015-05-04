#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <math.h>
#include <time.h>

#include "constantes.h"
#include "jouer.h"

void deplacerBarre(int plateau[NBR_BLOC_HAUTEUR][NBR_BLOC_LARGEUR], Barre *BarreNombre, int direction)
{
    switch(direction)
    {
        case DROITE:
            if(plateau[BarreNombre->positionBarre.y/TAILLE_BLOC_HAUTEUR][(BarreNombre->positionBarre.x + BarreNombre->tailleBarre)/TAILLE_BLOC_LARGEUR] == MUR)
                break;
            if (BarreNombre->positionBarre.x + BarreNombre->tailleBarre+8 > LARGEUR_FENETRE)//Si on ne veux pas mettre de mur
                break;
            BarreNombre->positionBarre.x=BarreNombre->positionBarre.x+8;
            break;
        case GAUCHE:
            if(plateau[BarreNombre->positionBarre.y/TAILLE_BLOC_HAUTEUR][BarreNombre->positionBarre.x/TAILLE_BLOC_LARGEUR] == MUR)
                break;
            if (BarreNombre->positionBarre.x - 8 < 0)
                break;
            BarreNombre->positionBarre.x=BarreNombre->positionBarre.x-8;
            break;
    }
}

void deplacerBalle(int plateau[NBR_BLOC_LARGEUR][NBR_BLOC_HAUTEUR], Barre *BarreNombre, Balle *BalleNombre, int *nvlVie, int *compteurVie, int *commencer, int *chargeTir, Bonus *BonusNombre, int *explose)
{
    int colision = 0;
    int colisionMur = 0;
    int valeurRetourner = 0;

    float vitesse = BalleNombre->k * sqrt(BalleNombre->Xancien * BalleNombre->Xancien  + BalleNombre->Yancien * BalleNombre->Yancien); // Permet de définir la vitesse de la balle en fonction de son deplacmeent en largeur et hauteur et du coefficient
    float nvlVitesse = 0;

    int differenceBalleBarreBloque = BarreNombre->positionBarre.x - BarreNombre->anciennePosBarre;

    BalleNombre->Xancien = BalleNombre->x;
    BalleNombre->Yancien = BalleNombre->y;

    float nvlCoorAxeXGauche = BalleNombre->positionXprecis + BalleNombre->k * BalleNombre->x;
    float nvlCoorAxeYHaut = BalleNombre->positionYprecis + BalleNombre->k * BalleNombre->y;

    float nvlCoorAxeXDroite = BalleNombre->positionXprecis + BalleNombre->k * BalleNombre->x + 20;
    float nvlCoorAxeYBas = BalleNombre->positionYprecis + BalleNombre->k * BalleNombre->y + 20;

    int tailleBarre=120;
    int largeurBarre=20;

    int caseActuelHaut = ((BalleNombre->posBalle.x + 10) / TAILLE_BLOC_LARGEUR) + ((BalleNombre->posBalle.y / TAILLE_BLOC_HAUTEUR) * NBR_BLOC_LARGEUR);
    int caseSuivanteHaut = ( ((int) nvlCoorAxeXGauche + 10) / TAILLE_BLOC_LARGEUR) + (( (int) nvlCoorAxeYHaut / TAILLE_BLOC_HAUTEUR) * NBR_BLOC_LARGEUR);

    int caseActuelBas = ((BalleNombre->posBalle.x + 10) / TAILLE_BLOC_LARGEUR) + (((BalleNombre->posBalle.y + 20) / TAILLE_BLOC_HAUTEUR) * NBR_BLOC_LARGEUR);
    int caseSuivanteBas = ( ((int) nvlCoorAxeXDroite - 10) / TAILLE_BLOC_LARGEUR) + (( (int) nvlCoorAxeYBas / TAILLE_BLOC_HAUTEUR) * NBR_BLOC_LARGEUR);

    int caseActuelGauche = (BalleNombre->posBalle.x / TAILLE_BLOC_LARGEUR) + (((BalleNombre->posBalle.y + 10) / TAILLE_BLOC_HAUTEUR) * NBR_BLOC_LARGEUR);
    int caseSuivanteGauche = ( (int) nvlCoorAxeXGauche / TAILLE_BLOC_LARGEUR) + (( ((int) nvlCoorAxeYBas - 10) / TAILLE_BLOC_HAUTEUR) * NBR_BLOC_LARGEUR);

    int caseActuelDroit = ((BalleNombre->posBalle.x + 20) / TAILLE_BLOC_LARGEUR) + (((BalleNombre->posBalle.y + 10) / TAILLE_BLOC_HAUTEUR) * NBR_BLOC_LARGEUR);
    int caseSuivanteDroit = ( (int) nvlCoorAxeXDroite / TAILLE_BLOC_LARGEUR) + (( ((int) nvlCoorAxeYBas - 10) / TAILLE_BLOC_HAUTEUR) * NBR_BLOC_LARGEUR);

    *explose = 0;

    if(nvlCoorAxeXGauche < 0 || nvlCoorAxeXDroite > LARGEUR_FENETRE)
    {
        BalleNombre->x = -BalleNombre->x;
        colision = 1;
    }
    //collision en haut
    else if(nvlCoorAxeYHaut <= 0)
    {
        BalleNombre->y = -BalleNombre->y;
        colision = 1;
    }
    //collision en bas
    else if(nvlCoorAxeYBas >= HAUTEUR_FENETRE)
    {
        if(BalleNombre->principale == 1)
        {
            *nvlVie = 1;
            *compteurVie = *compteurVie - 1;
            *commencer = 0;
            *chargeTir=0;
        }
        else
        {
            BalleNombre->vivante = 0;
            BalleNombre->collante = 0;
            BalleNombre->explosive = 0;
        }
    }
    else if((nvlCoorAxeXDroite >= (float)BarreNombre->positionBarre.x && nvlCoorAxeXGauche <= (float)BarreNombre->positionBarre.x + BarreNombre->tailleBarre) && (nvlCoorAxeYBas >= (float)BarreNombre->positionBarre.y && nvlCoorAxeYHaut <= (float)BarreNombre->positionBarre.y))
    {
        if(BalleNombre->bloque == 0 && BalleNombre->collante == 1 && BalleNombre->relance == 0)
        {
            BalleNombre->bloque = 1;
        }
        BalleNombre->differenceXBarreBalle = BalleNombre->positionXprecis - BarreNombre->positionBarre.x;
        colision = 1;

        if(BalleNombre->collante == 0 || BalleNombre->bloque == 0)
        {
            BalleNombre->relance = 0;
            if(nvlCoorAxeXDroite >= (float)BarreNombre->positionBarre.x && nvlCoorAxeXDroite <=  (float)BarreNombre->positionBarre.x + round((((float)BarreNombre->tailleBarre+20)/100)*6))
            {
                BalleNombre->y = -1;
                BalleNombre->x = -3;
            }
            else if(nvlCoorAxeXDroite >= (float)BarreNombre->positionBarre.x + round((((float)BarreNombre->tailleBarre+20)/100)*6) && nvlCoorAxeXDroite <= (float)BarreNombre->positionBarre.x + round((((float)BarreNombre->tailleBarre+20)/100)*12))
            {
                BalleNombre->y = -1;
                BalleNombre->x = -2;
            }
            else if(nvlCoorAxeXDroite >= (float)BarreNombre->positionBarre.x + round((((float)BarreNombre->tailleBarre+20)/100)*12) && nvlCoorAxeXDroite <= (float)BarreNombre->positionBarre.x + round((((float)BarreNombre->tailleBarre+20)/100)*19))
            {
                BalleNombre->y = -2;
                BalleNombre->x = -3;
            }
            else if(nvlCoorAxeXDroite >= (float)BarreNombre->positionBarre.x + round((((float)BarreNombre->tailleBarre+20)/100)*19) && nvlCoorAxeXDroite <= (float)BarreNombre->positionBarre.x + round((((float)BarreNombre->tailleBarre+20)/100)*26))
            {
                BalleNombre->y = -2;
                BalleNombre->x = -2;
            }
            else if(nvlCoorAxeXDroite >= (float)BarreNombre->positionBarre.x + round((((float)BarreNombre->tailleBarre+20)/100)*26) && nvlCoorAxeXDroite <= (float)BarreNombre->positionBarre.x + round((((float)BarreNombre->tailleBarre+20)/100)*33))
            {
                BalleNombre->y = -3;
                BalleNombre->x = -2;
            }
            else if(nvlCoorAxeXDroite >= (float)BarreNombre->positionBarre.x + round((((float)BarreNombre->tailleBarre+20)/100)*33) && nvlCoorAxeXDroite <= (float)BarreNombre->positionBarre.x + round((((float)BarreNombre->tailleBarre+20)/100)*40))
            {
                BalleNombre->y = -2;
                BalleNombre->x = -1;
            }
            else if(nvlCoorAxeXDroite >= (float)BarreNombre->positionBarre.x + round((((float)BarreNombre->tailleBarre+20)/100)*40) && nvlCoorAxeXDroite <=  (float)BarreNombre->positionBarre.x + round((((float)BarreNombre->tailleBarre+20)/100)*47))
            {
                BalleNombre->y = -3;
                BalleNombre->x = -1;
            }
            else if(nvlCoorAxeXDroite >= (float)BarreNombre->positionBarre.x + round((((float)BarreNombre->tailleBarre+20)/100)*47) && nvlCoorAxeXDroite <=  (float)BarreNombre->positionBarre.x + round((((float)BarreNombre->tailleBarre+20)/100)*53))
            {
                BalleNombre->y = -4;
                BalleNombre->x = 0;
            }
            else if(nvlCoorAxeXDroite >= (float)BarreNombre->positionBarre.x + round((((float)BarreNombre->tailleBarre+20)/100)*53) && nvlCoorAxeXDroite <=  (float)BarreNombre->positionBarre.x + round((((float)BarreNombre->tailleBarre+20)/100)*60))
            {
                BalleNombre->y = -3;
                BalleNombre->x = 1;
            }
            else if(nvlCoorAxeXDroite >= (float)BarreNombre->positionBarre.x + round((((float)BarreNombre->tailleBarre+20)/100)*60) && nvlCoorAxeXDroite <=  (float)BarreNombre->positionBarre.x + round((((float)BarreNombre->tailleBarre+20)/100)*67))
            {
                BalleNombre->y = -2;
                BalleNombre->x = 1;
            }
            else if(nvlCoorAxeXDroite >= (float)BarreNombre->positionBarre.x + round((((float)BarreNombre->tailleBarre+20)/100)*67) && nvlCoorAxeXDroite <=  (float)BarreNombre->positionBarre.x + round((((float)BarreNombre->tailleBarre+20)/100)*74))
            {
                BalleNombre->y = -3;
                BalleNombre->x = 2;
            }
            else if(nvlCoorAxeXDroite >= (float)BarreNombre->positionBarre.x + round((((float)BarreNombre->tailleBarre+20)/100)*74) && nvlCoorAxeXDroite <=  (float)BarreNombre->positionBarre.x + round((((float)BarreNombre->tailleBarre+20)/100)*81))
            {
                BalleNombre->y = -2;
                BalleNombre->x = 2;
            }
            else if(nvlCoorAxeXDroite >= (float)BarreNombre->positionBarre.x + round((((float)BarreNombre->tailleBarre+20)/100)*81) && nvlCoorAxeXDroite <=  (float)BarreNombre->positionBarre.x + round((((float)BarreNombre->tailleBarre+20)/100)*88))
            {
                BalleNombre->y = -2;
                BalleNombre->x = 3;
            }
            else if(nvlCoorAxeXDroite >= (float)BarreNombre->positionBarre.x + round((((float)BarreNombre->tailleBarre+20)/100)*88) && nvlCoorAxeXDroite <=  (float)BarreNombre->positionBarre.x + round((((float)BarreNombre->tailleBarre+20)/100)*94))
            {
                BalleNombre->y = -1;
                BalleNombre->x = 2;
            }
            else if(nvlCoorAxeXDroite >= (float)BarreNombre->positionBarre.x + round((((float)BarreNombre->tailleBarre+20)/100)*94) && nvlCoorAxeXDroite <=  (float)BarreNombre->positionBarre.x + (float)BarreNombre->tailleBarre+20)
            {
                BalleNombre->y = -1;
                BalleNombre->x = 3;
            }
        }
    }
    //gestion rencontre éléments du tableau!
    else if(caseActuelHaut != caseSuivanteHaut || caseActuelBas != caseSuivanteBas || caseActuelGauche != caseSuivanteGauche || caseActuelDroit != caseSuivanteDroit)
    {
        //On regarde si le coté haut change pas en diagonale a gauche
        if(caseActuelHaut - caseSuivanteHaut == NBR_BLOC_LARGEUR+1)
        {
            valeurRetourner = checkRencontrerBrique(plateau,caseSuivanteHaut, caseSuivanteHaut, &(*BonusNombre), &(*BalleNombre), &(*explose));
            if(valeurRetourner == 1 || valeurRetourner == 3 || valeurRetourner == 4)
            {
                BalleNombre->y = - BalleNombre->y;
                BalleNombre->x = -BalleNombre->x;
                colision++;
                *chargeTir = *chargeTir + 1;
            }
            else if(valeurRetourner == 2)
            {
                BalleNombre->x = -BalleNombre->x;
                colision ++;
                colisionMur ++;
            }
        }
        //On regarde si le coté haut change pas en diagonale a droite
        if(caseActuelHaut - caseSuivanteHaut == NBR_BLOC_LARGEUR-1)
        {
            valeurRetourner = checkRencontrerBrique(plateau,caseSuivanteHaut, caseSuivanteHaut, &(*BonusNombre), &(*BalleNombre), &(*explose));
            if(valeurRetourner == 1 || valeurRetourner == 3 || valeurRetourner == 4)
            {
                BalleNombre->y = - BalleNombre->y;
                BalleNombre->x = -BalleNombre->x;
                colision++;
                *chargeTir = *chargeTir + 1;
            }
            else if(valeurRetourner == 2)
            {
                BalleNombre->x = -BalleNombre->x;
                colision ++;
                colisionMur ++;
            }
        }
        //On regarde si le coté bas change pas en diagonale a gauche
        if(caseActuelBas - caseSuivanteBas == -NBR_BLOC_LARGEUR+1)
        {
            valeurRetourner = checkRencontrerBrique(plateau,caseSuivanteBas, caseSuivanteBas, &(*BonusNombre), &(*BalleNombre), &(*explose));
            if(valeurRetourner == 1 || valeurRetourner == 3 || valeurRetourner == 4)
            {
                BalleNombre->y = - BalleNombre->y;
                BalleNombre->x = -BalleNombre->x;
                colision++;
                *chargeTir = *chargeTir + 1;
            }
            else if(valeurRetourner == 2)
            {
                BalleNombre->x = -BalleNombre->x;
                colision ++;
                colisionMur ++;
            }
        }
        //On regarde si le coté bas change pas en diagonale à droite
        if(caseActuelBas - caseSuivanteBas == -NBR_BLOC_LARGEUR-1)
        {
            valeurRetourner = checkRencontrerBrique(plateau,caseSuivanteBas, caseSuivanteBas, &(*BonusNombre), &(*BalleNombre), &(*explose));
            if(valeurRetourner == 1 || valeurRetourner == 3 || valeurRetourner == 4)
            {
                BalleNombre->y = - BalleNombre->y;
                BalleNombre->x = -BalleNombre->x;
                colision++;
                *chargeTir = *chargeTir + 1;
            }
            else if(valeurRetourner == 2)
            {
                BalleNombre->x = -BalleNombre->x;
                colision ++;
                colisionMur ++;
            }
        }
        //On regarde si le coté gauche change pas en diagonale en bas
        if(caseActuelGauche - caseSuivanteGauche == -NBR_BLOC_LARGEUR+1)
        {
            valeurRetourner = checkRencontrerBrique(plateau,caseSuivanteGauche, caseSuivanteGauche, &(*BonusNombre), &(*BalleNombre), &(*explose));
            if(valeurRetourner == 1 || valeurRetourner == 3 || valeurRetourner == 4)
            {
                BalleNombre->y = - BalleNombre->y;
                BalleNombre->x = -BalleNombre->x;
                colision++;
                *chargeTir = *chargeTir + 1;
            }
            else if(valeurRetourner == 2)
            {
                BalleNombre->x = -BalleNombre->x;
                colision ++;
                colisionMur ++;
            }
        }
        //On regarde coté gauche change pas en diagonale en haut
        if(caseActuelGauche - caseSuivanteGauche == NBR_BLOC_LARGEUR+1)
        {
            valeurRetourner = checkRencontrerBrique(plateau,caseSuivanteGauche, caseSuivanteGauche, &(*BonusNombre), &(*BalleNombre), &(*explose));
            if(valeurRetourner == 1 || valeurRetourner == 3 || valeurRetourner == 4)
            {
                BalleNombre->y = - BalleNombre->y;
                BalleNombre->x = -BalleNombre->x;
                colision++;
                *chargeTir = *chargeTir + 1;
            }
            else if(valeurRetourner == 2)
            {
                BalleNombre->x = -BalleNombre->x;
                colision ++;
                colisionMur ++;
            }
        }
        //On regarde si coté droit change pas en diagonale en bas
        if(caseActuelDroit - caseSuivanteDroit == -NBR_BLOC_LARGEUR-1)
        {
            valeurRetourner = checkRencontrerBrique(plateau,caseSuivanteDroit, caseSuivanteDroit, &(*BonusNombre), &(*BalleNombre), &(*explose));
            if(valeurRetourner == 1 || valeurRetourner == 3 || valeurRetourner == 4)
            {
                BalleNombre->y = -BalleNombre->y;
                BalleNombre->x = -BalleNombre->x;
                colision++;
                *chargeTir = *chargeTir + 1;
            }
            else if(valeurRetourner == 2)
            {
                BalleNombre->x = -BalleNombre->x;
                colision ++;
                colisionMur ++;
            }
        }
        //On regarde si coté droit diagonale haut
        if(caseActuelDroit - caseSuivanteDroit == NBR_BLOC_LARGEUR-1)
        {
            valeurRetourner = checkRencontrerBrique(plateau,caseSuivanteDroit, caseSuivanteDroit, &(*BonusNombre), &(*BalleNombre), &(*explose));
            if(valeurRetourner == 1 || valeurRetourner == 3 || valeurRetourner == 4)
            {
                BalleNombre->y = - BalleNombre->y;
                BalleNombre->x = -BalleNombre->x;
                colision++;
                *chargeTir = *chargeTir + 1;
            }
            else if(valeurRetourner == 2)
            {
                BalleNombre->x = -BalleNombre->x;
                colision ++;
                colisionMur ++;
            }
        }
        //Diagonale touche case haut gauche
        if(caseActuelHaut - caseSuivanteHaut == NBR_BLOC_LARGEUR && caseActuelGauche - caseSuivanteGauche == 1)
        {
            valeurRetourner = checkRencontrerBrique(plateau,caseSuivanteHaut, caseSuivanteGauche, &(*BonusNombre), &(*BalleNombre), &(*explose));
            if(valeurRetourner == 1 || valeurRetourner == 3 || valeurRetourner == 4)
            {
                BalleNombre->y = -BalleNombre->y;
                if(BalleNombre->x<0)
                {
                    BalleNombre->x = -BalleNombre->x;
                }
                else if(BalleNombre->x == 0)
                {
                    BalleNombre->x = 2;
                }
                colision ++;
                *chargeTir = *chargeTir + 1;
            }
            else if(valeurRetourner == 2)
            {
                BalleNombre->x = -BalleNombre->x;
                colision ++;
                colisionMur ++;
            }
        }
        // On regarde si on arrive pas sur une case en haut avec la partie de gauche de la balle
        if(caseActuelHaut - caseActuelGauche == -NBR_BLOC_LARGEUR+1)
        {
            valeurRetourner = checkRencontrerBrique(plateau,caseSuivanteHaut, caseSuivanteGauche, &(*BonusNombre), &(*BalleNombre), &(*explose));
            if(valeurRetourner == 1 || valeurRetourner == 3 || valeurRetourner == 4)
            {
                if(BalleNombre->x<0)
                {
                    BalleNombre->x = -BalleNombre->x;
                }
                else if(BalleNombre->x == 0)
                {
                    BalleNombre->x = 2;
                }
                if(BalleNombre->y < 0)
                {
                    BalleNombre->y = -BalleNombre->y;
                }
                colision ++;
                *chargeTir = *chargeTir + 1;
            }
            else if(valeurRetourner == 2)
            {
                BalleNombre->x = -BalleNombre->x;
                colision ++;
                colisionMur ++;
            }
        }
        //On regarde si on touche en haut droite
        if(caseActuelHaut - caseSuivanteHaut == NBR_BLOC_LARGEUR && caseActuelDroit - caseSuivanteDroit == -1)
        {
            valeurRetourner = checkRencontrerBrique(plateau,caseSuivanteHaut, caseSuivanteDroit, &(*BonusNombre), &(*BalleNombre), &(*explose));
            if(valeurRetourner == 1 || valeurRetourner == 3 || valeurRetourner == 4)
            {
                BalleNombre->y = -BalleNombre->y;
                if(BalleNombre->x>0)
                {
                    BalleNombre->x = -BalleNombre->x;
                }
                else if(BalleNombre->x == 0)
                {
                    BalleNombre->x = -2;
                }
                colision ++;
                *chargeTir = *chargeTir + 1;
            }
            else if(valeurRetourner == 2)
            {
                BalleNombre->x = -BalleNombre->x;
                colision ++;
                colisionMur ++;
            }
        }
        // On regarde si on arrive pas sur une case en haut avec la partie de droite de la balle
        if(caseActuelHaut - caseActuelDroit == -NBR_BLOC_LARGEUR-1)
        {
            valeurRetourner = checkRencontrerBrique(plateau,caseSuivanteHaut, caseSuivanteDroit, &(*BonusNombre), &(*BalleNombre), &(*explose));
            if(valeurRetourner == 1 || valeurRetourner == 3 || valeurRetourner == 4)
            {
                if(BalleNombre->y < 0)
                {
                    BalleNombre->y = -BalleNombre->y;
                }
                if(BalleNombre->x>0)
                {
                    BalleNombre->x = -BalleNombre->x;
                }
                else if(BalleNombre->x == 0)
                {
                    BalleNombre->x = -2;
                }
                colision ++;
                *chargeTir = *chargeTir + 1;
            }
            else if(valeurRetourner == 2)
            {
                BalleNombre->x = -BalleNombre->x;
                colision ++;
                colisionMur ++;
            }
        }
        //On regarde si on touche la case en bas gauche
        if(caseActuelBas - caseSuivanteBas == -NBR_BLOC_LARGEUR && caseActuelGauche - caseSuivanteGauche == 1)
        {
            valeurRetourner = checkRencontrerBrique(plateau,caseSuivanteBas, caseSuivanteGauche, &(*BonusNombre), &(*BalleNombre), &(*explose));
            if(valeurRetourner == 1 || valeurRetourner == 3 || valeurRetourner == 4)
            {
                BalleNombre->y = -BalleNombre->y;
                if(BalleNombre->x>0)
                {
                    BalleNombre->x = -BalleNombre->x;
                }
                colision ++;
                *chargeTir = *chargeTir + 1;
            }
            else if(valeurRetourner == 2)
            {
                BalleNombre->x = -BalleNombre->x;
                colision ++;
                colisionMur ++;
            }
        }
        //On regarde si on arrive pas sur une case en bas avec la partie gauche de la balle
        if(caseActuelBas - caseActuelGauche == NBR_BLOC_LARGEUR+1)
        {
            valeurRetourner = checkRencontrerBrique(plateau,caseSuivanteBas, caseSuivanteGauche, &(*BonusNombre), &(*BalleNombre), &(*explose));
            if(valeurRetourner == 1 || valeurRetourner == 3 || valeurRetourner == 4)
            {
                if(BalleNombre->y > 0)
                {
                 BalleNombre->y = -BalleNombre->y;
                }
                if(BalleNombre->x < 0)
                {
                    BalleNombre->x = -BalleNombre->x;
                }
                colision ++;
                *chargeTir = *chargeTir + 1;
            }
            else if(valeurRetourner == 2)
            {
                BalleNombre->x = -BalleNombre->x;
                colision ++;
                colisionMur ++;
            }
        }
        //On regarde si on touche la case en bas droite
        if(caseActuelBas - caseSuivanteBas == -NBR_BLOC_LARGEUR && caseActuelDroit - caseSuivanteDroit == -1)
        {
            valeurRetourner = checkRencontrerBrique(plateau,caseSuivanteBas, caseSuivanteDroit, &(*BonusNombre), &(*BalleNombre), &(*explose));
            if(valeurRetourner == 1 || valeurRetourner == 3 || valeurRetourner == 4)
            {
                BalleNombre->y = -BalleNombre->y;
                if(BalleNombre->x<0)
                {
                    BalleNombre->x = -BalleNombre->x;
                }
                colision ++;
                *chargeTir = *chargeTir + 1;
            }
            else if(valeurRetourner == 2)
            {
                BalleNombre->x = -BalleNombre->x;
                colision ++;
                colisionMur ++;
            }
        }
        //On regarde si on arrive pas sur une case en bas avec la partie droite de la balle
        if(caseActuelBas - caseActuelDroit == NBR_BLOC_LARGEUR-1)
        {
            valeurRetourner = checkRencontrerBrique(plateau,caseSuivanteBas, caseSuivanteDroit, &(*BonusNombre), &(*BalleNombre), &(*explose));
            if(valeurRetourner == 1 || valeurRetourner == 3 || valeurRetourner == 4)
            {
                if(BalleNombre->y > 0)
                {
                    BalleNombre->y = -BalleNombre->y;
                }
                if(BalleNombre->x>0)
                {
                    BalleNombre->x = -BalleNombre->x;
                }
                colision ++;
                *chargeTir = *chargeTir + 1;
            }
            else if(valeurRetourner == 2)
            {
                BalleNombre->x = -BalleNombre->x;
                colision ++;
                colisionMur ++;
            }
        }
        //On regarde si on touche la case d'en haut
        if(caseActuelHaut - caseSuivanteHaut == NBR_BLOC_LARGEUR)
        {
            valeurRetourner = checkRencontrerBrique(plateau,caseSuivanteHaut, caseSuivanteHaut, &(*BonusNombre), &(*BalleNombre), &(*explose));
            if(valeurRetourner == 1 || valeurRetourner == 3 || valeurRetourner == 4)
            {
                BalleNombre->y = -BalleNombre->y;
                colision ++;
                *chargeTir = *chargeTir + 1;
            }
            else if(valeurRetourner == 2)
            {
                BalleNombre->y = -BalleNombre->y;
                colision ++;
                colisionMur ++;
            }
        }
        //On regarde si on touche la case d'en bas
        if(caseActuelBas - caseSuivanteBas == -NBR_BLOC_LARGEUR)
        {
            valeurRetourner = checkRencontrerBrique(plateau,caseSuivanteBas, caseSuivanteBas, &(*BonusNombre), &(*BalleNombre), &(*explose));
            if(valeurRetourner == 1 || valeurRetourner == 3 || valeurRetourner == 4)
            {
                BalleNombre->y = -BalleNombre->y;
                colision ++;
                *chargeTir = *chargeTir + 1;
            }
            else if(valeurRetourner == 2)
            {
                BalleNombre->y = -BalleNombre->y;
                colision ++;
                colisionMur ++;
            }
        }
        //On regarde si on touche la case de gauche
        if(caseActuelGauche - caseSuivanteGauche == 1)
        {
            valeurRetourner = checkRencontrerBrique(plateau,caseSuivanteGauche, caseSuivanteGauche, &(*BonusNombre), &(*BalleNombre), &(*explose));
            if(valeurRetourner == 1 || valeurRetourner == 3 || valeurRetourner == 4)
            {
                BalleNombre->x = -BalleNombre->x;
                colision ++;
                *chargeTir = *chargeTir + 1;
            }
            else if(valeurRetourner == 2)
            {
                BalleNombre->x = -BalleNombre->x;
                colision ++;
                colisionMur ++;
            }
        }
        //On regarde si on touche la case de droite
        if(caseActuelDroit - caseSuivanteDroit == -1)
        {
            valeurRetourner = checkRencontrerBrique(plateau,caseSuivanteDroit, caseSuivanteDroit, &(*BonusNombre), &(*BalleNombre), &(*explose));
            if(valeurRetourner == 1 || valeurRetourner == 3 || valeurRetourner == 4)
            {
                BalleNombre->x = -BalleNombre->x;
                colision ++;
                *chargeTir = *chargeTir + 1;
            }
            else if(valeurRetourner == 2)
            {
                BalleNombre->x = -BalleNombre->x;
                colision ++;
                colisionMur ++;
            }
        }
    }
    //déplacement
    if(colision == 0 )
    {
        nvlVitesse = BalleNombre->k * sqrt(BalleNombre->x * BalleNombre->x  + BalleNombre->y * BalleNombre->y);
        BalleNombre->k *= (vitesse / nvlVitesse);

        BalleNombre->positionXprecis += BalleNombre->k * BalleNombre->x;
        BalleNombre->positionYprecis += BalleNombre->k * BalleNombre->y;

        BalleNombre->posBalle.x = (int) BalleNombre->positionXprecis;
        BalleNombre->posBalle.y = (int) BalleNombre->positionYprecis;
    }
    else if(colision%2==0)
    {
        BalleNombre->y = -BalleNombre->y;
        if(colisionMur%2==0)
        {
            BalleNombre->y = -BalleNombre->y;
            BalleNombre->x = -BalleNombre->x;
        }
    }
    *explose = 1;
    BarreNombre->anciennePosBarre = BarreNombre->positionBarre.x;
}

void deplacerTir(int plateau[NBR_BLOC_LARGEUR][NBR_BLOC_HAUTEUR], Tir *TirType, Bonus *BonusNombre, Balle *BalleNombre, int *explose)
{
    int vitesseTir = -10;

    int nvlCoordonneesTirY = TirType->positionTir.y + vitesseTir;

    int actuelPositionTirNormaleQauche = (TirType->positionTir.x/ TAILLE_BLOC_LARGEUR) + ((TirType->positionTir.y / TAILLE_BLOC_HAUTEUR) * NBR_BLOC_LARGEUR);
    int futurPositionTirNormaleQauche = (TirType->positionTir.x/ TAILLE_BLOC_LARGEUR) + ((nvlCoordonneesTirY / TAILLE_BLOC_HAUTEUR) * NBR_BLOC_LARGEUR);

    int actuelPositionTirNormaleDroite = ((TirType->positionTir.x+3)/ TAILLE_BLOC_LARGEUR) + ((TirType->positionTir.y / TAILLE_BLOC_HAUTEUR) * NBR_BLOC_LARGEUR);
    int futurPositionTirNormaleDroite = ((TirType->positionTir.x+3)/ TAILLE_BLOC_LARGEUR) + ((nvlCoordonneesTirY / TAILLE_BLOC_HAUTEUR) * NBR_BLOC_LARGEUR);

    int actuelPositionTirPuissantQauche = (TirType->positionTir.x/ TAILLE_BLOC_LARGEUR) + ((TirType->positionTir.y / TAILLE_BLOC_HAUTEUR) * NBR_BLOC_LARGEUR);
    int futurPositionTirPuissantQauche = (TirType->positionTir.x/ TAILLE_BLOC_LARGEUR) + ((nvlCoordonneesTirY / TAILLE_BLOC_HAUTEUR) * NBR_BLOC_LARGEUR);

    int actuelPositionTirPuissantDroite = ((TirType->positionTir.x)/ TAILLE_BLOC_LARGEUR) + ((TirType->positionTir.y / TAILLE_BLOC_HAUTEUR) * NBR_BLOC_LARGEUR);
    int futurPositionTirPuissantDroite = ((TirType->positionTir.x+6)/ TAILLE_BLOC_LARGEUR) + ((nvlCoordonneesTirY / TAILLE_BLOC_HAUTEUR) * NBR_BLOC_LARGEUR);

    BonusNombre->tir = 1;
    *explose = 1;

    if(TirType->typeTir == NORMAL)
    {
        if(actuelPositionTirNormaleQauche - futurPositionTirNormaleQauche == NBR_BLOC_LARGEUR)
        {
            if(checkRencontrerBrique(plateau, futurPositionTirNormaleQauche, futurPositionTirNormaleQauche, &(*BonusNombre), &(BalleNombre), &(*explose)) == 1)
            {
                TirType->tirVivant = 0;
            }
            else if(checkRencontrerBrique(plateau, futurPositionTirNormaleQauche, futurPositionTirNormaleQauche, &(*BonusNombre), &(BalleNombre), &(*explose)) == 2 || checkRencontrerBrique(plateau, futurPositionTirNormaleQauche, futurPositionTirNormaleQauche, &(*BonusNombre), &(BalleNombre), &(*explose)) == 3)
            {
                TirType->tirVivant = 0;
            }
        }
        else if(actuelPositionTirNormaleDroite - futurPositionTirNormaleDroite == NBR_BLOC_LARGEUR)
        {
            if(checkRencontrerBrique(plateau, futurPositionTirNormaleDroite, futurPositionTirNormaleDroite, &(*BonusNombre), &(BalleNombre), &(*explose)) == 1)
            {
                TirType->tirVivant = 0;
            }
            else if(checkRencontrerBrique(plateau, futurPositionTirNormaleDroite, futurPositionTirNormaleDroite, &(*BonusNombre), &(BalleNombre), &(*explose)) == 2 || checkRencontrerBrique(plateau, futurPositionTirNormaleDroite, futurPositionTirNormaleDroite, &(*BonusNombre), &(BalleNombre), &(*explose)) == 3)
            {
                TirType->tirVivant = 0;
            }
        }
        else if(nvlCoordonneesTirY <= 0)
        {
            TirType->tirVivant = 0;
        }
    }
    else if(TirType->typeTir == PUISSANT)
    {
        if(actuelPositionTirPuissantQauche - futurPositionTirPuissantQauche == NBR_BLOC_LARGEUR)
        {
            if(checkRencontrerBrique(plateau, futurPositionTirPuissantQauche, futurPositionTirPuissantQauche, &(*BonusNombre), &(BalleNombre), &(*explose)) == 1)
            {
                plateau[futurPositionTirPuissantQauche/NBR_BLOC_HAUTEUR][futurPositionTirPuissantQauche%NBR_BLOC_LARGEUR] = VIDE;
            }
            else if(checkRencontrerBrique(plateau, futurPositionTirPuissantQauche, futurPositionTirPuissantQauche, &(*BonusNombre), &(BalleNombre), &(*explose)) == 2 || checkRencontrerBrique(plateau, futurPositionTirPuissantQauche, futurPositionTirPuissantQauche, &(*BonusNombre), &(BalleNombre), &(*explose)) == 3)
            {
                TirType->tirVivant = 0;
            }
        }
        else if(actuelPositionTirPuissantDroite - futurPositionTirPuissantDroite == NBR_BLOC_LARGEUR)
        {
            if(checkRencontrerBrique(plateau, futurPositionTirPuissantDroite, futurPositionTirPuissantDroite, &(*BonusNombre), &(BalleNombre), &(*explose)) == 1)
            {
                plateau[futurPositionTirPuissantDroite/NBR_BLOC_HAUTEUR][futurPositionTirPuissantDroite%NBR_BLOC_LARGEUR] = VIDE;
            }
            else if(checkRencontrerBrique(plateau, futurPositionTirPuissantDroite, futurPositionTirPuissantDroite, &(*BonusNombre), &(BalleNombre), &(*explose)) == 2 || checkRencontrerBrique(plateau, futurPositionTirPuissantDroite, futurPositionTirPuissantDroite, &(*BonusNombre), &(BalleNombre), &(*explose)) == 3)
            {
                TirType->tirVivant = 0;
            }
        }
        else if(nvlCoordonneesTirY <= 0)
        {
            TirType->tirVivant = 0;
        }
    }
    if(TirType->tirVivant == 1)
    {
        TirType->positionTir.y += vitesseTir;
    }
    BonusNombre->tir = 0;
}

int checkRencontrerBrique(int plateau[NBR_BLOC_LARGEUR][NBR_BLOC_HAUTEUR], int caseTesti, int caseTestJ, Bonus *BonusNombre, Balle *BalleNombre, int *explose)
{
    int valeurRetourner;
    int nombreAlea;
    int siExplo;


    if(plateau[caseTesti/NBR_BLOC_HAUTEUR][caseTestJ%NBR_BLOC_LARGEUR] == BRIQUE_A || plateau[caseTesti/NBR_BLOC_HAUTEUR][caseTestJ%NBR_BLOC_LARGEUR] == BRIQUE_B_CASSER || plateau[caseTesti/NBR_BLOC_HAUTEUR][caseTestJ%NBR_BLOC_LARGEUR] == BRIQUE_C_CASSER2 )
    {
        srand(time(NULL));
        nombreAlea = rand()%40;
        if(nombreAlea >= 1 && nombreAlea < 8)
        {
            BonusNombre->typeBonus = nombreAlea;
            //BonusNombre->typeBonus = 1; // je fixe à 1 pour tester le bonus vie
            if(BonusNombre->typeBonus == 1)
            {
                BonusNombre->imageBonus = SDL_LoadBMP("art/bonus/vie.bmp");
                SDL_SetColorKey(BonusNombre->imageBonus, SDL_SRCCOLORKEY, SDL_MapRGB(BonusNombre->imageBonus->format, 255, 255, 255));
            }
            if(BonusNombre->typeBonus == 2)
                BonusNombre->imageBonus = SDL_LoadBMP("art/bonus/aggrandissement.bmp");
            if(BonusNombre->typeBonus == 3)
                BonusNombre->imageBonus = SDL_LoadBMP("art/bonus/acceleration.bmp");
            if(BonusNombre->typeBonus == 4)
            {
                BonusNombre->imageBonus = SDL_LoadBMP("art/bonus/lent.bmp");
                SDL_SetColorKey(BonusNombre->imageBonus, SDL_SRCCOLORKEY, SDL_MapRGB(BonusNombre->imageBonus->format, 255, 255, 255));
            }
            if(BonusNombre->typeBonus == 5)
            {
                BonusNombre->imageBonus = SDL_LoadBMP("art/bonus/balle_bonus.bmp");
                SDL_SetColorKey(BonusNombre->imageBonus, SDL_SRCCOLORKEY, SDL_MapRGB(BonusNombre->imageBonus->format, 255, 255, 255));
            }
            if(BonusNombre->typeBonus == 6)
                BonusNombre->imageBonus = SDL_LoadBMP("art/bonus/collante.bmp");
            if(BonusNombre->typeBonus == 7)
                BonusNombre->imageBonus = SDL_LoadBMP("art/bonus/balle_explosive.bmp");

            BonusNombre->bonus = 1;
            if(BonusNombre->tir == 1)
            {
                BonusNombre->posBonus.x = (caseTestJ % 20) * 60 + 30;
                BonusNombre->posBonus.y = (caseTesti / 20) * 30 + 15;
            }
            else if(BonusNombre->tir == 0)
            {
                BonusNombre->bonusCree = 1;
            }
        }
        plateau[caseTesti/NBR_BLOC_HAUTEUR][caseTestJ%NBR_BLOC_LARGEUR] = VIDE;
        if(BalleNombre->explosive == 1 && *explose == 0)
        {
            //rajouter un test sur la valeur de la briques a coté et si c'est une autre explo remmetre explose a 0
            *explose = 1;
            siExplo = checkRencontrerBrique(plateau, caseTesti, caseTestJ-1, &(*BonusNombre), &(*BalleNombre), &(*explose));
            if(siExplo == 4)
            {
                *explose = 0;
                checkRencontrerBrique(plateau, caseTesti, caseTestJ-1, &(*BonusNombre), &(*BalleNombre), &(*explose));
            }
            siExplo = checkRencontrerBrique(plateau, caseTesti, caseTestJ+1, &(*BonusNombre), &(*BalleNombre), &(*explose));
            if(siExplo == 4)
            {
                *explose = 0;
                checkRencontrerBrique(plateau, caseTesti, caseTestJ+1, &(*BonusNombre), &(*BalleNombre), &(*explose));
            }
            siExplo = checkRencontrerBrique(plateau, caseTesti-20, caseTestJ, &(*BonusNombre), &(*BalleNombre), &(*explose));
            if(siExplo == 4)
            {
                *explose = 0;
                checkRencontrerBrique(plateau, caseTesti-20, caseTestJ, &(*BonusNombre), &(*BalleNombre), &(*explose));
            }
            siExplo = checkRencontrerBrique(plateau, caseTesti+20, caseTestJ, &(*BonusNombre), &(*BalleNombre), &(*explose));
            if(siExplo == 4)
            {
                *explose = 0;
                checkRencontrerBrique(plateau, caseTesti+20, caseTestJ, &(*BonusNombre), &(*BalleNombre), &(*explose));
            }
            siExplo = checkRencontrerBrique(plateau, caseTesti-20, caseTestJ-1, &(*BonusNombre), &(*BalleNombre), &(*explose));
            if(siExplo == 4)
            {
                *explose = 0;
                checkRencontrerBrique(plateau, caseTesti-20, caseTestJ-1, &(*BonusNombre), &(*BalleNombre), &(*explose));
            }
            siExplo = checkRencontrerBrique(plateau, caseTesti-20, caseTestJ+1, &(*BonusNombre), &(*BalleNombre), &(*explose));
            if(siExplo == 4)
            {
                *explose = 0;
                checkRencontrerBrique(plateau, caseTesti-20, caseTestJ+1, &(*BonusNombre), &(*BalleNombre), &(*explose));
            }
            siExplo = checkRencontrerBrique(plateau, caseTesti+20, caseTestJ-1, &(*BonusNombre), &(*BalleNombre), &(*explose));
            if(siExplo == 4)
            {
                *explose = 0;
                checkRencontrerBrique(plateau, caseTesti+20, caseTestJ-1, &(*BonusNombre), &(*BalleNombre), &(*explose));
            }
            siExplo = checkRencontrerBrique(plateau, caseTesti+20, caseTestJ+1, &(*BonusNombre), &(*BalleNombre), &(*explose));
            if(siExplo == 4)
            {
                *explose = 0;
                checkRencontrerBrique(plateau, caseTesti+20, caseTestJ+1, &(*BonusNombre), &(*BalleNombre), &(*explose));
            }
        }
        valeurRetourner = 1;
        BonusNombre->score = BonusNombre->score + 100;
    }
    else if(plateau[caseTesti/NBR_BLOC_HAUTEUR][caseTestJ%NBR_BLOC_LARGEUR] == BRIQUE_B)
    {
        plateau[caseTesti/NBR_BLOC_HAUTEUR][caseTestJ%NBR_BLOC_LARGEUR] = BRIQUE_B_CASSER;
        if(BalleNombre->explosive == 1 && *explose == 0)
        {
            *explose = 1;
            siExplo = checkRencontrerBrique(plateau, caseTesti, caseTestJ-1, &(*BonusNombre), &(*BalleNombre), &(*explose));
            if(siExplo == 4)
            {
                *explose = 0;
                checkRencontrerBrique(plateau, caseTesti, caseTestJ-1, &(*BonusNombre), &(*BalleNombre), &(*explose));
            }
            siExplo = checkRencontrerBrique(plateau, caseTesti, caseTestJ+1, &(*BonusNombre), &(*BalleNombre), &(*explose));
            if(siExplo == 4)
            {
                *explose = 0;
                checkRencontrerBrique(plateau, caseTesti, caseTestJ+1, &(*BonusNombre), &(*BalleNombre), &(*explose));
            }
            siExplo = checkRencontrerBrique(plateau, caseTesti-20, caseTestJ, &(*BonusNombre), &(*BalleNombre), &(*explose));
            if(siExplo == 4)
            {
                *explose = 0;
                checkRencontrerBrique(plateau, caseTesti-20, caseTestJ, &(*BonusNombre), &(*BalleNombre), &(*explose));
            }
            siExplo = checkRencontrerBrique(plateau, caseTesti+20, caseTestJ, &(*BonusNombre), &(*BalleNombre), &(*explose));
            if(siExplo == 4)
            {
                *explose = 0;
                checkRencontrerBrique(plateau, caseTesti+20, caseTestJ, &(*BonusNombre), &(*BalleNombre), &(*explose));
            }
            siExplo = checkRencontrerBrique(plateau, caseTesti-20, caseTestJ-1, &(*BonusNombre), &(*BalleNombre), &(*explose));
            if(siExplo == 4)
            {
                *explose = 0;
                checkRencontrerBrique(plateau, caseTesti-20, caseTestJ-1, &(*BonusNombre), &(*BalleNombre), &(*explose));
            }
            siExplo = checkRencontrerBrique(plateau, caseTesti-20, caseTestJ+1, &(*BonusNombre), &(*BalleNombre), &(*explose));
            if(siExplo == 4)
            {
                *explose = 0;
                checkRencontrerBrique(plateau, caseTesti-20, caseTestJ+1, &(*BonusNombre), &(*BalleNombre), &(*explose));
            }
            siExplo = checkRencontrerBrique(plateau, caseTesti+20, caseTestJ-1, &(*BonusNombre), &(*BalleNombre), &(*explose));
            if(siExplo == 4)
            {
                *explose = 0;
                checkRencontrerBrique(plateau, caseTesti+20, caseTestJ-1, &(*BonusNombre), &(*BalleNombre), &(*explose));
            }
            siExplo = checkRencontrerBrique(plateau, caseTesti+20, caseTestJ+1, &(*BonusNombre), &(*BalleNombre), &(*explose));
            if(siExplo == 4)
            {
                *explose = 0;
                checkRencontrerBrique(plateau, caseTesti+20, caseTestJ+1, &(*BonusNombre), &(*BalleNombre), &(*explose));
            }
        }
        valeurRetourner = 1;
        BonusNombre->score = BonusNombre->score + 100;
    }
    else if(plateau[caseTesti/NBR_BLOC_HAUTEUR][caseTestJ%NBR_BLOC_LARGEUR] == BRIQUE_C_CASSER1)
    {
        plateau[caseTesti/NBR_BLOC_HAUTEUR][caseTestJ%NBR_BLOC_LARGEUR] = BRIQUE_C_CASSER2;
        if(BalleNombre->explosive == 1 && *explose == 0)
        {
            *explose = 1;
            siExplo = checkRencontrerBrique(plateau, caseTesti, caseTestJ-1, &(*BonusNombre), &(*BalleNombre), &(*explose));
            if(siExplo == 4)
            {
                *explose = 0;
                checkRencontrerBrique(plateau, caseTesti, caseTestJ-1, &(*BonusNombre), &(*BalleNombre), &(*explose));
            }
            siExplo = checkRencontrerBrique(plateau, caseTesti, caseTestJ+1, &(*BonusNombre), &(*BalleNombre), &(*explose));
            if(siExplo == 4)
            {
                *explose = 0;
                checkRencontrerBrique(plateau, caseTesti, caseTestJ+1, &(*BonusNombre), &(*BalleNombre), &(*explose));
            }
            siExplo = checkRencontrerBrique(plateau, caseTesti-20, caseTestJ, &(*BonusNombre), &(*BalleNombre), &(*explose));
            if(siExplo == 4)
            {
                *explose = 0;
                checkRencontrerBrique(plateau, caseTesti-20, caseTestJ, &(*BonusNombre), &(*BalleNombre), &(*explose));
            }
            siExplo = checkRencontrerBrique(plateau, caseTesti+20, caseTestJ, &(*BonusNombre), &(*BalleNombre), &(*explose));
            if(siExplo == 4)
            {
                *explose = 0;
                checkRencontrerBrique(plateau, caseTesti+20, caseTestJ, &(*BonusNombre), &(*BalleNombre), &(*explose));
            }
            siExplo = checkRencontrerBrique(plateau, caseTesti-20, caseTestJ-1, &(*BonusNombre), &(*BalleNombre), &(*explose));
            if(siExplo == 4)
            {
                *explose = 0;
                checkRencontrerBrique(plateau, caseTesti-20, caseTestJ-1, &(*BonusNombre), &(*BalleNombre), &(*explose));
            }
            siExplo = checkRencontrerBrique(plateau, caseTesti-20, caseTestJ+1, &(*BonusNombre), &(*BalleNombre), &(*explose));
            if(siExplo == 4)
            {
                *explose = 0;
                checkRencontrerBrique(plateau, caseTesti-20, caseTestJ+1, &(*BonusNombre), &(*BalleNombre), &(*explose));
            }
            siExplo = checkRencontrerBrique(plateau, caseTesti+20, caseTestJ-1, &(*BonusNombre), &(*BalleNombre), &(*explose));
            if(siExplo == 4)
            {
                *explose = 0;
                checkRencontrerBrique(plateau, caseTesti+20, caseTestJ-1, &(*BonusNombre), &(*BalleNombre), &(*explose));
            }
            siExplo = checkRencontrerBrique(plateau, caseTesti+20, caseTestJ+1, &(*BonusNombre), &(*BalleNombre), &(*explose));
            if(siExplo == 4)
            {
                *explose = 0;
                checkRencontrerBrique(plateau, caseTesti+20, caseTestJ+1, &(*BonusNombre), &(*BalleNombre), &(*explose));
            }
        }
        valeurRetourner = 1;
        BonusNombre->score = BonusNombre->score + 100;
    }
    else if(plateau[caseTesti/NBR_BLOC_HAUTEUR][caseTestJ%NBR_BLOC_LARGEUR] == BRIQUE_C)
    {
        plateau[caseTesti/NBR_BLOC_HAUTEUR][caseTestJ%NBR_BLOC_LARGEUR] = BRIQUE_C_CASSER1;
        if(BalleNombre->explosive == 1 && *explose == 0)
        {
            *explose = 1;
            siExplo = checkRencontrerBrique(plateau, caseTesti, caseTestJ-1, &(*BonusNombre), &(*BalleNombre), &(*explose));
            if(siExplo == 4)
            {
                *explose = 0;
                checkRencontrerBrique(plateau, caseTesti, caseTestJ-1, &(*BonusNombre), &(*BalleNombre), &(*explose));
            }
            siExplo = checkRencontrerBrique(plateau, caseTesti, caseTestJ+1, &(*BonusNombre), &(*BalleNombre), &(*explose));
            if(siExplo == 4)
            {
                *explose = 0;
                checkRencontrerBrique(plateau, caseTesti, caseTestJ+1, &(*BonusNombre), &(*BalleNombre), &(*explose));
            }
            siExplo = checkRencontrerBrique(plateau, caseTesti-20, caseTestJ, &(*BonusNombre), &(*BalleNombre), &(*explose));
            if(siExplo == 4)
            {
                *explose = 0;
                checkRencontrerBrique(plateau, caseTesti-20, caseTestJ, &(*BonusNombre), &(*BalleNombre), &(*explose));
            }
            siExplo = checkRencontrerBrique(plateau, caseTesti+20, caseTestJ, &(*BonusNombre), &(*BalleNombre), &(*explose));
            if(siExplo == 4)
            {
                *explose = 0;
                checkRencontrerBrique(plateau, caseTesti+20, caseTestJ, &(*BonusNombre), &(*BalleNombre), &(*explose));
            }
            siExplo = checkRencontrerBrique(plateau, caseTesti-20, caseTestJ-1, &(*BonusNombre), &(*BalleNombre), &(*explose));
            if(siExplo == 4)
            {
                *explose = 0;
                checkRencontrerBrique(plateau, caseTesti-20, caseTestJ-1, &(*BonusNombre), &(*BalleNombre), &(*explose));
            }
            siExplo = checkRencontrerBrique(plateau, caseTesti-20, caseTestJ+1, &(*BonusNombre), &(*BalleNombre), &(*explose));
            if(siExplo == 4)
            {
                *explose = 0;
                checkRencontrerBrique(plateau, caseTesti-20, caseTestJ+1, &(*BonusNombre), &(*BalleNombre), &(*explose));
            }
            siExplo = checkRencontrerBrique(plateau, caseTesti+20, caseTestJ-1, &(*BonusNombre), &(*BalleNombre), &(*explose));
            if(siExplo == 4)
            {
                *explose = 0;
                checkRencontrerBrique(plateau, caseTesti+20, caseTestJ-1, &(*BonusNombre), &(*BalleNombre), &(*explose));
            }
            siExplo = checkRencontrerBrique(plateau, caseTesti+20, caseTestJ+1, &(*BonusNombre), &(*BalleNombre), &(*explose));
            if(siExplo == 4)
            {
                *explose = 0;
                checkRencontrerBrique(plateau, caseTesti+20, caseTestJ+1, &(*BonusNombre), &(*BalleNombre), &(*explose));
            }
        }
        valeurRetourner = 1;
        BonusNombre->score = BonusNombre->score + 100;
    }
    else if(plateau[caseTesti/NBR_BLOC_HAUTEUR][caseTestJ%NBR_BLOC_LARGEUR] == BRIQUE_INDES)
    {
        valeurRetourner = 3;
        BonusNombre->score = BonusNombre->score + 100;
    }
    else if(plateau[caseTesti/NBR_BLOC_HAUTEUR][caseTestJ%NBR_BLOC_LARGEUR] == BRIQUE_EXPLO)
    {
        plateau[caseTesti/NBR_BLOC_HAUTEUR][caseTestJ%NBR_BLOC_LARGEUR] = VIDE;
        *explose = 1;
        siExplo = checkRencontrerBrique(plateau, caseTesti, caseTestJ-1, &(*BonusNombre), &(*BalleNombre), &(*explose));
            if(siExplo == 4)
            {
                *explose = 0;
                checkRencontrerBrique(plateau, caseTesti, caseTestJ-1, &(*BonusNombre), &(*BalleNombre), &(*explose));
            }
            siExplo = checkRencontrerBrique(plateau, caseTesti, caseTestJ+1, &(*BonusNombre), &(*BalleNombre), &(*explose));
            if(siExplo == 4)
            {
                *explose = 0;
                checkRencontrerBrique(plateau, caseTesti, caseTestJ+1, &(*BonusNombre), &(*BalleNombre), &(*explose));
            }
            siExplo = checkRencontrerBrique(plateau, caseTesti-20, caseTestJ, &(*BonusNombre), &(*BalleNombre), &(*explose));
            if(siExplo == 4)
            {
                *explose = 0;
                checkRencontrerBrique(plateau, caseTesti-20, caseTestJ, &(*BonusNombre), &(*BalleNombre), &(*explose));
            }
            siExplo = checkRencontrerBrique(plateau, caseTesti+20, caseTestJ, &(*BonusNombre), &(*BalleNombre), &(*explose));
            if(siExplo == 4)
            {
                *explose = 0;
                checkRencontrerBrique(plateau, caseTesti+20, caseTestJ, &(*BonusNombre), &(*BalleNombre), &(*explose));
            }
            siExplo = checkRencontrerBrique(plateau, caseTesti-20, caseTestJ-1, &(*BonusNombre), &(*BalleNombre), &(*explose));
            if(siExplo == 4)
            {
                *explose = 0;
                checkRencontrerBrique(plateau, caseTesti-20, caseTestJ-1, &(*BonusNombre), &(*BalleNombre), &(*explose));
            }
            siExplo = checkRencontrerBrique(plateau, caseTesti-20, caseTestJ+1, &(*BonusNombre), &(*BalleNombre), &(*explose));
            if(siExplo == 4)
            {
                *explose = 0;
                checkRencontrerBrique(plateau, caseTesti-20, caseTestJ+1, &(*BonusNombre), &(*BalleNombre), &(*explose));
            }
            siExplo = checkRencontrerBrique(plateau, caseTesti+20, caseTestJ-1, &(*BonusNombre), &(*BalleNombre), &(*explose));
            if(siExplo == 4)
            {
                *explose = 0;
                checkRencontrerBrique(plateau, caseTesti+20, caseTestJ-1, &(*BonusNombre), &(*BalleNombre), &(*explose));
            }
            siExplo = checkRencontrerBrique(plateau, caseTesti+20, caseTestJ+1, &(*BonusNombre), &(*BalleNombre), &(*explose));
            if(siExplo == 4)
            {
                *explose = 0;
                checkRencontrerBrique(plateau, caseTesti+20, caseTestJ+1, &(*BonusNombre), &(*BalleNombre), &(*explose));
            }

        valeurRetourner = 4;
        BonusNombre->score = BonusNombre->score + 100;
    }
    else if(plateau[caseTesti/NBR_BLOC_HAUTEUR][caseTestJ%NBR_BLOC_LARGEUR] == MUR)
    {
        valeurRetourner = 2;
    }
    else
    {
        valeurRetourner = 0;
    }
    return valeurRetourner;
}

void deplacerBonus(Bonus *BonusNombre, Barre *BarreNombre)
{
    int vitesseBonus = 4;
    int futurPositionBonus = BonusNombre->posBonus.y + vitesseBonus;

    if((BonusNombre->posBonus.y + 20) >= HAUTEUR_FENETRE)
    {
        BonusNombre->bonus = 0;
    }

    if(((BonusNombre->posBonus.x + 20) >= BarreNombre->positionBarre.x && BonusNombre->posBonus.x <= BarreNombre->positionBarre.x + BarreNombre->tailleBarre) && ((futurPositionBonus + 20) >= BarreNombre->positionBarre.y && futurPositionBonus <= BarreNombre->positionBarre.y ))
    {
        BonusNombre->bonus = 0;
        BonusNombre->bonusActive =1;
    }

    if(BonusNombre->bonus == 1)
    {
        BonusNombre->posBonus.y += vitesseBonus;
    }
}
