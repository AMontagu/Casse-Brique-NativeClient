#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>

#include "constantes.h"
#include "jouer.h"

void lancementBonus(Bonus *BonusNombre,int *compteurVie, Barre *BarreNombre, Balle *Balle1, Balle *Balle2, Balle *Balle3, Balle *Balle4)
{
    if(BonusNombre->typeBonus == 1)
    {
        bonusVie(&(*compteurVie));
        BonusNombre->bonusActive = 0;
    }
    else if(BonusNombre->typeBonus == 2)
    {
        bonusBarre(&(*BarreNombre));
        BonusNombre->bonusActive = 0;
    }
    else if(BonusNombre->typeBonus == 3)
    {
        bonusAcc(&(*Balle1), &(*Balle2), &(*Balle3), &(*Balle4), &(*BonusNombre));
        BonusNombre->bonusActive = 0;
    }
    else if(BonusNombre->typeBonus == 4)
    {
        bonusDec(&(*Balle1), &(*Balle2), &(*Balle3), &(*Balle4), &(*BonusNombre));
        BonusNombre->bonusActive = 0;
    }
    else if(BonusNombre->typeBonus == 5)
    {
        doublementBalle(&(*Balle1), &(*Balle2), &(*Balle3), &(*Balle4));
        BonusNombre->bonusActive = 0;
    }
    else if(BonusNombre->typeBonus == 6)
    {
        balleCollante(&(*Balle1), &(*Balle2), &(*Balle3), &(*Balle4));
        BonusNombre->bonusActive = 0;
    }
    else if(BonusNombre->typeBonus == 7)
    {
        balleExplosive(&(*Balle1), &(*Balle2), &(*Balle3), &(*Balle4));
        BonusNombre->bonusActive = 0;
    }
}

void bonusVie(int *compteurVie)
{
    if(*compteurVie < 5)
    {
        *compteurVie = *compteurVie + 1;
    }
}

void bonusBarre(Barre *BarreNombre)
{
    if(BarreNombre->tailleBarre == 120)
    {
        BarreNombre->tailleBarre = 180;
        if(BarreNombre->positionBarre.x > LARGEUR_FENETRE-270)
        {
            BarreNombre->positionBarre.x = LARGEUR_FENETRE-BarreNombre->tailleBarre-120;
        }
        else if(BarreNombre->positionBarre.x < 150)
        {
            BarreNombre->positionBarre.x = 120;
        }
        else
        {
            BarreNombre->positionBarre.x = BarreNombre->positionBarre.x - 10;
        }
        BarreNombre->imageBarre = SDL_LoadBMP("art/barres/18020.bmp");
    }
    else if(BarreNombre->tailleBarre == 180)
    {
        BarreNombre->tailleBarre = 240;
        if(BarreNombre->positionBarre.x > LARGEUR_FENETRE-300)
        {
            BarreNombre->positionBarre.x = LARGEUR_FENETRE-BarreNombre->tailleBarre-120;
        }
        else if(BarreNombre->positionBarre.x < 180)
        {
            BarreNombre->positionBarre.x = 120;
        }
        else
        {
            BarreNombre->positionBarre.x = BarreNombre->positionBarre.x - 20;
        }
        BarreNombre->imageBarre = SDL_LoadBMP("art/barres/24020.bmp");
    }
}

void bonusAcc(Balle *Balle1, Balle *Balle2, Balle *Balle3, Balle *Balle4, Bonus *BonusNombre)
{
    if(Balle1->k <= 2)
    {
        Balle1->ancienK = Balle1->k;
        Balle1->k = 2;
        BonusNombre->acc = 1;

        if(Balle2->vivante == 1)
        {
            Balle2->ancienK = Balle2->k;
            Balle2->k = Balle1->k;
        }
        if(Balle3->vivante == 1)
        {
            Balle3->ancienK = Balle3->k;
            Balle3->k = Balle1->k;
        }
        if(Balle4->vivante == 1)
        {
            Balle4->ancienK = Balle4->k;
            Balle4->k = Balle1->k;
        }
    }
    else if(Balle1->k < 3)
    {
        Balle1->ancienK = Balle1->k;
        Balle1->k = 4;
        BonusNombre->acc = 1;
        if(Balle2->vivante == 1)
        {
            Balle2->ancienK = Balle2->k;
            Balle2->k = Balle1->k;
        }
        if(Balle3->vivante == 1)
        {
            Balle3->ancienK = Balle3->k;
            Balle3->k = Balle1->k;
        }
        if(Balle4->vivante == 1)
        {
            Balle4->ancienK = Balle4->k;
            Balle4->k = Balle1->k;
        }
    }
}

void bonusDec(Balle *Balle1, Balle *Balle2, Balle *Balle3, Balle *Balle4, Bonus *BonusNombre)
{
    if(Balle1->k >= 4)
    {
        Balle1->ancienK = Balle1->k;
        Balle1->k = 3;
        BonusNombre->decc = 1;

        if(Balle2->vivante == 1)
        {
            Balle2->ancienK = Balle2->k;
            Balle2->k = Balle1->k;
        }
        if(Balle3->vivante == 1)
        {
            Balle3->ancienK = Balle3->k;
            Balle3->k = Balle1->k;
        }
        if(Balle4->vivante == 1)
        {
            Balle4->ancienK = Balle4->k;
            Balle4->k = Balle1->k;
        }
    }
    else if(Balle1->k >= 3)
    {
        Balle1->ancienK = Balle1->k;
        Balle1->k = 2;
        BonusNombre->decc = 1;

        if(Balle2->vivante == 1)
        {
            Balle2->ancienK = Balle2->k;
            Balle2->k = Balle1->k;
        }
        if(Balle3->vivante == 1)
        {
            Balle3->ancienK = Balle3->k;
            Balle3->k = Balle1->k;
        }
        if(Balle4->vivante == 1)
        {
            Balle4->ancienK = Balle4->k;
            Balle4->k = Balle1->k;
        }
    }
    else if(Balle1->k < 3)
    {
        Balle1->ancienK = Balle1->k;
        Balle1->k = 1;
        BonusNombre->decc = 1;

        if(Balle2->vivante == 1)
        {
            Balle2->ancienK = Balle2->k;
            Balle2->k = Balle1->k;
        }
        if(Balle3->vivante == 1)
        {
            Balle3->ancienK = Balle3->k;
            Balle3->k = Balle1->k;
        }
        if(Balle4->vivante == 1)
        {
            Balle4->ancienK = Balle4->k;
            Balle4->k = Balle1->k;
        }
    }
}

void doublementBalle(Balle *Balle1, Balle *Balle2, Balle *Balle3, Balle *Balle4)
{
    if(Balle2->vivante == 0)
    {
        Balle2->vivante = 1;
        Balle2->principale = 0;
        Balle2->x = -Balle1->x;
        Balle2->y = -Balle1->y;
        Balle2->k = Balle1->k;
        Balle2->Xancien = Balle1->Xancien;
        Balle2->Yancien = Balle1->Yancien;
        Balle2->positionXprecis = Balle1->positionXprecis;
        Balle2->positionYprecis = Balle1->positionYprecis;
        Balle2->posBalle.x = Balle1->posBalle.x;
        Balle2->posBalle.y = Balle1->posBalle.y;
        Balle2->collante = Balle1->collante;
        Balle2->explosive = Balle1->explosive;
        Balle2->imageBalle = SDL_LoadBMP("balleBonus.bmp");
        SDL_SetColorKey(Balle2->imageBalle, SDL_SRCCOLORKEY, SDL_MapRGB(Balle2->imageBalle->format, 255, 255, 255));
    }
    else if(Balle2->vivante == 1 || Balle3->vivante == 1 || Balle4->vivante == 1)
    {
        if(Balle3->vivante == 0 && Balle4->vivante == 0)
        {
            Balle3->vivante = 1;
            Balle3->principale = 0;
            Balle3->x = -Balle1->x;
            Balle3->y = -Balle1->y;
            Balle3->k = Balle1->k;
            Balle3->Xancien = Balle1->Xancien;
            Balle3->Yancien = Balle1->Yancien;
            Balle3->positionXprecis = Balle1->positionXprecis;
            Balle3->positionYprecis = Balle1->positionYprecis;
            Balle3->posBalle.x = Balle1->posBalle.x;
            Balle3->posBalle.y = Balle1->posBalle.y;
            Balle3->collante = Balle1->collante;
            Balle3->explosive = Balle1->explosive;
            Balle3->imageBalle = SDL_LoadBMP("balleBonus.bmp");
            SDL_SetColorKey(Balle3->imageBalle, SDL_SRCCOLORKEY, SDL_MapRGB(Balle3->imageBalle->format, 255, 255, 255));

            Balle4->vivante = 1;
            Balle4->principale = 0;
            Balle4->x = -Balle2->x;
            Balle4->y = -Balle2->y;
            Balle4->k = Balle2->k;
            Balle4->Xancien = Balle2->Xancien;
            Balle4->Yancien = Balle2->Yancien;
            Balle4->positionXprecis = Balle2->positionXprecis;
            Balle4->positionYprecis = Balle2->positionYprecis;
            Balle4->posBalle.x = Balle2->posBalle.x;
            Balle4->posBalle.y = Balle2->posBalle.y;
            Balle4->collante = Balle2->collante;
            Balle4->explosive = Balle2->explosive;
            Balle4->imageBalle = SDL_LoadBMP("balleBonus.bmp");
            SDL_SetColorKey(Balle4->imageBalle, SDL_SRCCOLORKEY, SDL_MapRGB(Balle4->imageBalle->format, 255, 255, 255));
        }

        else if(Balle2->vivante == 0 && Balle4->vivante == 0)
        {
            Balle2->vivante = 1;
            Balle2->principale = 0;
            Balle2->x = -Balle1->x;
            Balle2->y = -Balle1->y;
            Balle2->k = Balle1->k;
            Balle2->Xancien = Balle1->Xancien;
            Balle2->Yancien = Balle1->Yancien;
            Balle2->positionXprecis = Balle1->positionXprecis;
            Balle2->positionYprecis = Balle1->positionYprecis;
            Balle2->posBalle.x = Balle1->posBalle.x;
            Balle2->posBalle.y = Balle1->posBalle.y;
            Balle2->collante = Balle1->collante;
            Balle2->explosive = Balle1->explosive;
            Balle2->imageBalle = SDL_LoadBMP("balleBonus.bmp");
            SDL_SetColorKey(Balle2->imageBalle, SDL_SRCCOLORKEY, SDL_MapRGB(Balle2->imageBalle->format, 255, 255, 255));

            Balle4->vivante = 1;
            Balle4->principale = 0;
            Balle4->x = -Balle3->x;
            Balle4->y = -Balle3->y;
            Balle4->k = Balle3->k;
            Balle4->Xancien = Balle3->Xancien;
            Balle4->Yancien = Balle3->Yancien;
            Balle4->positionXprecis = Balle3->positionXprecis;
            Balle4->positionYprecis = Balle3->positionYprecis;
            Balle4->posBalle.x = Balle3->posBalle.x;
            Balle4->posBalle.y = Balle3->posBalle.y;
            Balle4->collante = Balle3->collante;
            Balle4->explosive = Balle3->explosive;
            Balle4->imageBalle = SDL_LoadBMP("balleBonus.bmp");
            SDL_SetColorKey(Balle4->imageBalle, SDL_SRCCOLORKEY, SDL_MapRGB(Balle4->imageBalle->format, 255, 255, 255));
        }
        else if(Balle2->vivante == 0 && Balle3->vivante == 0)
        {
            Balle2->vivante = 1;
            Balle2->principale = 0;
            Balle2->x = -Balle1->x;
            Balle2->y = -Balle1->y;
            Balle2->k = Balle1->k;
            Balle2->Xancien = Balle1->Xancien;
            Balle2->Yancien = Balle1->Yancien;
            Balle2->positionXprecis = Balle1->positionXprecis;
            Balle2->positionYprecis = Balle1->positionYprecis;
            Balle2->posBalle.x = Balle1->posBalle.x;
            Balle2->posBalle.y = Balle1->posBalle.y;
            Balle2->collante = Balle1->collante;
            Balle2->explosive = Balle1->explosive;
            Balle2->imageBalle = SDL_LoadBMP("balleBonus.bmp");
            SDL_SetColorKey(Balle2->imageBalle, SDL_SRCCOLORKEY, SDL_MapRGB(Balle2->imageBalle->format, 255, 255, 255));

            Balle3->vivante = 1;
            Balle3->principale = 0;
            Balle3->x = -Balle4->x;
            Balle3->y = -Balle4->y;
            Balle3->k = Balle4->k;
            Balle3->Xancien = Balle4->Xancien;
            Balle3->Yancien = Balle4->Yancien;
            Balle3->positionXprecis = Balle4->positionXprecis;
            Balle3->positionYprecis = Balle4->positionYprecis;
            Balle3->posBalle.x = Balle4->posBalle.x;
            Balle3->posBalle.y = Balle4->posBalle.y;
            Balle3->collante = Balle4->collante;
            Balle3->explosive = Balle4->explosive;
            Balle3->imageBalle = SDL_LoadBMP("balleBonus.bmp");
            SDL_SetColorKey(Balle3->imageBalle, SDL_SRCCOLORKEY, SDL_MapRGB(Balle3->imageBalle->format, 255, 255, 255));
        }
    }
}

void balleCollante(Balle *Balle1, Balle *Balle2, Balle *Balle3, Balle *Balle4)
{
    Balle1->collante = 1;
    if(Balle2->vivante == 1)
    {
        Balle2->collante = 1;
    }
    if(Balle3->vivante == 1)
    {
        Balle3->collante = 1;
    }
    if(Balle4->vivante == 1)
    {
        Balle4->collante = 1;
    }
}

void balleExplosive(Balle *Balle1, Balle *Balle2, Balle *Balle3, Balle *Balle4)
{
    Balle1->explosive = 1;
    if(Balle2->vivante == 1)
    {
        Balle2->explosive = 1;
    }
    if(Balle3->vivante == 1)
    {
        Balle3->explosive = 1;
    }
    if(Balle4->vivante == 1)
    {
        Balle4->explosive = 1;
    }
}
