#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>

#include "constantes.h"
#include "jouer.h"
#include "fichiers.h"
#include "bonus.h"
#include "VetD.h"

void jouer(SDL_Surface* ecran, int *numNiveau)
{
    SDL_Surface *briqueA = NULL, *briqueB = NULL, *briqueC = NULL, *trois = NULL, *deux = NULL, *un = NULL, *quatre = NULL, *cinq = NULL, *bordure = NULL;
    SDL_Surface *briqueBcasser = NULL, *briqueCcasser1 = NULL, *briqueCcasser2 = NULL, *briqueIndes = NULL, *briqueExplo = NULL;
    SDL_Surface *charge0 = NULL, *charge1 = NULL, *charge2 = NULL, *charge3 = NULL, *charge4 = NULL, *charge5 = NULL, *charge6 = NULL, *charge7 = NULL, *charge8 = NULL, *charge9 = NULL, *charge10 = NULL;
    SDL_Surface *texte = NULL, *fond = NULL;
    SDL_Rect position;
    SDL_Event event;
    TTF_Font *police = NULL;
    SDL_Color blanc = {255, 255, 255};

    int continuer = 1, briqueRestante=0, i=0, j=0, niveauCharge=0, commencer=0, nvlVie=0, compteurVie=3;
    int tempsActuel = 0, tempsPrecedent = 0, tempsPrecedentScore = 0, tempsActuelScore = 0;
    int plateau[NBR_BLOC_HAUTEUR][NBR_BLOC_LARGEUR] = {0};
    int chargeTir=10, explose = 1, test = 0;
    int tpsAvantBonus=0;
    int exTick;
    int optiLoad=-1;
    char score[20] = "20";

    Barre Barre1;
    Balle Balle1, Balle2, Balle3, Balle4;
    Bonus Bonus1, Bonus2;
    Tir TirNormale, TirPuissant;

    initialisationBarre(&Barre1);

    initialisationBalle(&Balle1);

    initialisationBonus(&Bonus1);
    initialisationBonus(&Bonus2);

    if(Bonus1.scoreP != 0)
        Bonus1.score = 0;

    Bonus1.score = 0;

    TirNormale.typeTir = NORMAL;
    TirPuissant.typeTir = PUISSANT;
    TirNormale.tirVivant = 0;
    TirPuissant.tirVivant = 0;

    SDL_SetColorKey(Balle1.imageBalle, SDL_SRCCOLORKEY, SDL_MapRGB(Balle1.imageBalle->format, 0, 0, 0));

    trois = SDL_LoadBMP("art/vies/vie3.bmp");
    deux = SDL_LoadBMP("art/vies/vie2.bmp");
    un = SDL_LoadBMP("art/vies/vie1.bmp");
    quatre = SDL_LoadBMP("art/vies/vie4.bmp");
    cinq = SDL_LoadBMP("art/vies/vie5.bmp");

    SDL_SetColorKey(un, SDL_SRCCOLORKEY, SDL_MapRGB(un->format, 0, 0, 255));
    SDL_SetColorKey(deux, SDL_SRCCOLORKEY, SDL_MapRGB(deux->format, 0, 0, 255));
    SDL_SetColorKey(trois, SDL_SRCCOLORKEY, SDL_MapRGB(trois->format, 0, 0, 255));
    SDL_SetColorKey(quatre, SDL_SRCCOLORKEY, SDL_MapRGB(quatre->format, 0, 0, 255));
    SDL_SetColorKey(cinq, SDL_SRCCOLORKEY, SDL_MapRGB(cinq->format, 0, 0, 255));

    charge0 = SDL_LoadBMP("charge0.bmp");
    charge1 = SDL_LoadBMP("charge1.bmp");
    charge2 = SDL_LoadBMP("charge2.bmp");
    charge3 = SDL_LoadBMP("charge3.bmp");
    charge4 = SDL_LoadBMP("charge4.bmp");
    charge5 = SDL_LoadBMP("charge5.bmp");
    charge6 = SDL_LoadBMP("charge6.bmp");
    charge7 = SDL_LoadBMP("charge7.bmp");
    charge8 = SDL_LoadBMP("charge8.bmp");
    charge9 = SDL_LoadBMP("charge9.bmp");
    charge10 = SDL_LoadBMP("charge10.bmp");

    TirNormale.imageTir = SDL_LoadBMP("tirNormale.bmp");
    TirPuissant.imageTir = SDL_LoadBMP("tirPuissant.bmp");

    TTF_Init();
    police = TTF_OpenFont("brush.ttf", 25);

    if(niveauCharge == 0)
    {
        chargerNiveau(&plateau, *numNiveau);
        niveauCharge=1;
    }
    SDL_EnableKeyRepeat(1, 1);

    while(continuer)
    {
        tpsAvantBonus = SDL_GetTicks();

        if(optiLoad != *numNiveau)
        {
            if(*numNiveau < 5 && *numNiveau >= 1)
            {
                briqueA = SDL_LoadBMP("art/prehistoire/briqueA.bmp");
                briqueB = SDL_LoadBMP("art/prehistoire/briqueB.bmp");
                briqueBcasser = SDL_LoadBMP("art/prehistoire/briqueBcasser.bmp");
                briqueC = SDL_LoadBMP("art/prehistoire/briqueC.bmp");
                briqueCcasser1 = SDL_LoadBMP("art/prehistoire/briqueCcasser1.bmp");
                briqueCcasser2 = SDL_LoadBMP("art/prehistoire/briqueCcasser2.bmp");
                briqueIndes = SDL_LoadBMP("art/prehistoire/briqueIndes.bmp");
                briqueExplo = SDL_LoadBMP("art/prehistoire/briqueExplo.bmp");
                bordure = SDL_LoadBMP("art/prehistoire/bordurePrehistoire.bmp");
            }
            if(*numNiveau < 9 && *numNiveau >= 5)
            {
                briqueA = SDL_LoadBMP("art/egypte/briqueA.bmp");
                briqueB = SDL_LoadBMP("art/egypte/briqueB.bmp");
                briqueBcasser = SDL_LoadBMP("art/egypte/briqueBcasser.bmp");
                briqueC = SDL_LoadBMP("art/egypte/briqueC.bmp");
                briqueCcasser1 = SDL_LoadBMP("art/egypte/briqueCcasser1.bmp");
                briqueCcasser2 = SDL_LoadBMP("art/egypte/briqueCcasser2.bmp");
                briqueIndes = SDL_LoadBMP("art/egypte/briqueIndes.bmp");
                briqueExplo = SDL_LoadBMP("art/egypte/briqueExplo.bmp");
                bordure = SDL_LoadBMP("art/egypte/bordureEgypte.bmp");
            }
            if(*numNiveau < 13 && *numNiveau >= 9)
            {
                briqueA = SDL_LoadBMP("art/romeantique/briqueA.bmp");
                briqueB = SDL_LoadBMP("art/romeantique/briqueB.bmp");
                briqueBcasser = SDL_LoadBMP("art/romeantique/briqueBcasser.bmp");
                briqueC = SDL_LoadBMP("art/romeantique/briqueC.bmp");
                briqueCcasser1 = SDL_LoadBMP("art/romeantique/briqueCcasser1.bmp");
                briqueCcasser2 = SDL_LoadBMP("art/romeantique/briqueCcasser2.bmp");
                briqueIndes = SDL_LoadBMP("art/romeantique/briqueIndes.bmp");
                briqueExplo = SDL_LoadBMP("art/romeantique/briqueExplo.bmp");
                bordure = SDL_LoadBMP("art/romeantique/bordureRomeAntique.bmp");
            }
            if(*numNiveau < 17 && *numNiveau >= 13)
            {
                briqueA = SDL_LoadBMP("art/moyenage/briqueA.bmp");
                briqueB = SDL_LoadBMP("art/moyenage/briqueB.bmp");
                briqueBcasser = SDL_LoadBMP("art/moyenage/briqueBcasser.bmp");
                briqueC = SDL_LoadBMP("art/moyenage/briqueC.bmp");
                briqueCcasser1 = SDL_LoadBMP("art/moyenage/briqueCcasser1.bmp");
                briqueCcasser2 = SDL_LoadBMP("art/moyenage/briqueCcasser2.bmp");
                briqueIndes = SDL_LoadBMP("art/moyenage/briqueIndes.bmp");
                briqueExplo = SDL_LoadBMP("art/moyenage/briqueExplo.bmp");
                bordure = SDL_LoadBMP("art/moyenage/bordureMoyenAge.bmp");
            }
            optiLoad =  *numNiveau;
        }

        test++;
        briqueRestante = 0;
        for(i=0;i<NBR_BLOC_HAUTEUR;i++)
        {
            for(j=0;j<NBR_BLOC_LARGEUR;j++)
            {
                switch(plateau[i][j])
                {
                    case BRIQUE_A:
                        briqueRestante++;
                        break;
                    case BRIQUE_B:
                        briqueRestante++;
                        break;
                    case BRIQUE_C:
                        briqueRestante++;
                        break;
                    case BRIQUE_B_CASSER:
                        briqueRestante++;
                        break;
                    case BRIQUE_C_CASSER1:
                        briqueRestante++;
                        break;
                    case BRIQUE_C_CASSER2:
                        briqueRestante++;
                        break;
                    case BRIQUE_EXPLO:
                        briqueRestante++;
                        break;
                }
            }
        }
        if(Bonus1.bonusActive == 1)
        {
            lancementBonus(&Bonus1, &compteurVie, &Barre1, &Balle1, &Balle2, &Balle3, &Balle4);
            exTick = tpsAvantBonus;
        }
        else if(Bonus2.bonusActive == 1)
        {
            lancementBonus(&Bonus2, &compteurVie, &Barre1, &Balle1, &Balle2, &Balle3, &Balle4);
            exTick = tpsAvantBonus;
        }

        if(tpsAvantBonus >= exTick + 10000 && (Bonus1.acc == 1 || Bonus2.acc == 1 || Bonus1.decc == 1 || Bonus2.decc == 1))
        {
            if(Bonus1.acc == 1)
                Bonus1.acc == 0;
            if(Bonus2.acc == 1)
                Bonus2.acc == 0;
            if(Bonus1.decc == 1)
                Bonus1.decc == 0;
            if(Bonus2.decc == 1)
                Bonus2.decc == 0;

            if(Balle1.k != 3)
            {
                Balle1.k = Balle1.ancienK;

                if(Balle2.vivante == 1)
                {
                    Balle2.k = Balle1.k;
                }
                if(Balle3.vivante == 1)
                {
                    Balle3.k = Balle1.k;
                }
                if(Balle4.vivante == 1)
                {
                    Balle4.k = Balle1.k;
                }
            }

            if (Barre1.tailleBarre == 180)
            {
                Barre1.tailleBarre = 120;
                Barre1.imageBarre = SDL_LoadBMP("art/barres/12020.bmp");
            }
            if (Barre1.tailleBarre == 240)
            {
                Barre1.tailleBarre = 180;
                Barre1.imageBarre = SDL_LoadBMP("art/barres/18020.bmp");
            }
            exTick = tpsAvantBonus;
        }
        if(nvlVie == 1)
        {
            initialisationBarre(&Barre1);

            nvlVie = 0;
        }
        if(compteurVie == 0)
        {
            defaite(ecran, *numNiveau);
        }
        if(briqueRestante > 0)
        {
            if(TirNormale.tirVivant == 0)
            {
                TirNormale.positionTir.x = Barre1.positionBarre.x + Barre1.tailleBarre;
                TirNormale.positionTir.y = Barre1.positionBarre.y - 20;
            }
            if(TirPuissant.tirVivant == 0)
            {
                TirPuissant.positionTir.x = Barre1.positionBarre.x + Barre1.tailleBarre;
                TirPuissant.positionTir.y = Barre1.positionBarre.y - 20;
            }
            if(TirPuissant.tirVivant == 1)
            {
                if(Bonus1.bonus == 0)
                {
                    deplacerTir(plateau, &TirPuissant, &Bonus1, &Balle1, &explose);
                }
                else
                {
                    deplacerTir(plateau, &TirPuissant, &Bonus2, &Balle1, &explose);
                }
            }
            if(TirNormale.tirVivant == 1)
            {
                if(Bonus1.bonus == 0)
                {
                    deplacerTir(plateau, &TirNormale, &Bonus2, &Balle1, &explose);
                }
                else
                {
                    deplacerTir(plateau, &TirNormale, &Bonus2, &Balle1, &explose);
                }
            }
            Bonus1.tempsMnt = SDL_GetTicks();
            if(Bonus1.tempsMnt - Bonus1.tempsPrece > 1)
            {
                if(Bonus1.bonus == 1)
                {
                    if(Bonus1.bonusCree == 1)
                    {
                        Bonus1.posBonus.x = Balle1.posBalle.x;
                        Bonus1.posBonus.y = Balle1.posBalle.y;
                        Bonus1.bonusCree = 0;
                    }
                    deplacerBonus(&Bonus1, &Barre1);
                }
                if(Bonus2.bonus == 1)
                {
                    if(Bonus2.bonusCree == 1)
                    {
                        Bonus2.posBonus.x = Balle1.posBalle.x;
                        Bonus2.posBonus.y = Balle1.posBalle.y;
                        Bonus2.bonusCree = 0;
                    }
                    deplacerBonus(&Bonus2, &Barre1.positionBarre);
                }
                Bonus1.tempsPrece = Bonus1.tempsMnt;
            }
            if(commencer >= 1)
            {
                tempsActuel = SDL_GetTicks();
                if (tempsActuel - tempsPrecedent > 10)
                {
                    if(Bonus1.bonus == 0)
                    {
                        deplacerBalle(plateau ,&Barre1, &Balle1, &nvlVie, &compteurVie, &commencer, &chargeTir, &Bonus1, &explose);
                        if(Balle2.vivante == 1)
                        {
                            deplacerBalle(plateau ,&Barre1, &Balle2, &nvlVie, &compteurVie, &commencer, &chargeTir, &Bonus1, &explose);
                        }
                        if(Balle3.vivante == 1)
                        {
                            deplacerBalle(plateau ,&Barre1, &Balle3, &nvlVie, &compteurVie, &commencer, &chargeTir, &Bonus1, &explose);
                        }
                        if(Balle4.vivante == 1)
                        {
                            deplacerBalle(plateau ,&Barre1, &Balle4, &nvlVie, &compteurVie, &commencer, &chargeTir, &Bonus1, &explose);
                        }
                    }
                    else
                    {
                        deplacerBalle(plateau ,&Barre1, &Balle1, &nvlVie, &compteurVie, &commencer, &chargeTir, &Bonus2, &explose);
                        if(Balle2.vivante == 1)
                        {
                            deplacerBalle(plateau ,&Barre1, &Balle2, &nvlVie, &compteurVie, &commencer, &chargeTir, &Bonus2, &explose);
                        }
                        if(Balle3.vivante == 1)
                        {
                            deplacerBalle(plateau ,&Barre1, &Balle3, &nvlVie, &compteurVie, &commencer, &chargeTir, &Bonus2, &explose);
                        }
                        if(Balle4.vivante == 1)
                        {
                            deplacerBalle(plateau ,&Barre1, &Balle4, &nvlVie, &compteurVie, &commencer, &chargeTir, &Bonus2, &explose);
                        }
                    }
                    tempsPrecedent = tempsActuel;
                }
            }

            SDL_Event event;
            while(SDL_PollEvent(&event))
            {
                switch(event.type)
                {
                    case SDL_QUIT:
                        exit(EXIT_SUCCESS);
                        break;
                    case SDL_KEYDOWN:
                        switch(event.key.keysym.sym)
                        {
                            case SDLK_ESCAPE:
                                main(NULL,NULL);
                                break;
                            case SDLK_RIGHT:
                                deplacerBarre(plateau, &Barre1, DROITE);
                                break;
                            case SDLK_LEFT:
                                deplacerBarre(plateau, &Barre1, GAUCHE);
                                break;
                            case SDLK_SPACE:
                                commencer = 1;
                                if(Balle1.bloque == 1)
                                {
                                    Balle1.bloque = 0;
                                    Balle1.relance = 1;
                                }
                                else if(Balle2.bloque == 1)
                                {
                                    Balle2.bloque = 0;
                                    Balle2.relance = 1;
                                }
                                else if(Balle3.bloque == 1)
                                {
                                    Balle3.bloque = 0;
                                    Balle3.relance = 1;
                                }
                                else if(Balle4.bloque == 1)
                                {
                                    Balle4.bloque = 0;
                                    Balle4.relance = 1;
                                }
                                break;
                            case SDLK_UP:
                                commencer = 1;
                                if(Balle1.bloque == 1)
                                {
                                    Balle1.bloque = 0;
                                    Balle1.relance = 1;
                                }
                                else if(Balle2.bloque == 1)
                                {
                                    Balle2.bloque = 0;
                                    Balle2.relance = 1;
                                }
                                else if(Balle3.bloque == 1)
                                {
                                    Balle3.bloque = 0;
                                    Balle3.relance = 1;
                                }
                                else if(Balle4.bloque == 1)
                                {
                                    Balle4.bloque = 0;
                                    Balle4.relance = 1;
                                }

                                if(chargeTir >= 10)
                                {
                                    TirPuissant.tirVivant = 1;
                                    chargeTir = 0;
                                }
                                else if(chargeTir >=5)
                                {
                                    TirNormale.tirVivant = 1;
                                    chargeTir = 0;
                                }
                                break;
                            default:
                                break;
                        }
                        break;
                }
            }
        }
        else
        {
            victoire(ecran, &(*numNiveau));
        }

        SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));

        position.x = 0;
        position.y = 0;
        SDL_BlitSurface(bordure, NULL, ecran, &position);

        for(i=0;i<NBR_BLOC_HAUTEUR;i++)
        {
            for(j=0;j<NBR_BLOC_LARGEUR;j++)
            {
                position.x=j*TAILLE_BLOC_LARGEUR;
                position.y=i*TAILLE_BLOC_HAUTEUR;

                switch(plateau[i][j])
                {
                    case BRIQUE_A:
                        SDL_BlitSurface(briqueA, NULL, ecran, &position);
                        break;
                    case BRIQUE_B:
                        SDL_BlitSurface(briqueB, NULL, ecran, &position);
                        break;
                    case BRIQUE_B_CASSER:
                        SDL_BlitSurface(briqueBcasser, NULL, ecran, &position);
                        break;
                    case BRIQUE_C:
                        SDL_BlitSurface(briqueC, NULL, ecran, &position);
                        break;
                    case BRIQUE_C_CASSER1:
                        SDL_BlitSurface(briqueCcasser1, NULL, ecran, &position);
                        break;
                    case BRIQUE_C_CASSER2:
                        SDL_BlitSurface(briqueCcasser2, NULL, ecran, &position);
                        break;
                    case BRIQUE_INDES:
                        SDL_BlitSurface(briqueIndes, NULL, ecran, &position);
                        break;
                    case BRIQUE_EXPLO:
                        SDL_BlitSurface(briqueExplo, NULL, ecran, &position);
                        break;
                }
            }
        }

        SDL_BlitSurface(Barre1.imageBarre, NULL, ecran, &Barre1.positionBarre);

        if(commencer==0 || nvlVie == 1)
        {
            initialisationBalle(&Balle1);
            SDL_SetColorKey(Balle1.imageBalle, SDL_SRCCOLORKEY, SDL_MapRGB(Balle1.imageBalle->format, 0, 0, 0));
            Balle1.posBalle.x = Barre1.positionBarre.x+50;
            Balle1.posBalle.y = Barre1.positionBarre.y-20;
            Balle1.positionXprecis = Barre1.positionBarre.x+50;
            Balle1.positionYprecis = Barre1.positionBarre.y-20;
            Balle2.vivante = 0;
            Balle3.vivante = 0;
            Balle4.vivante = 0;

            Balle1.collante = 0;
            Balle2.collante = 0;
            Balle3.collante = 0;
            Balle4.collante = 0;

            Balle1.bloque = 0;
            Balle2.bloque = 0;
            Balle3.bloque = 0;
            Balle4.bloque = 0;

            Balle1.explosive = 0;
            Balle2.explosive = 0;
            Balle3.explosive = 0;
            Balle4.explosive = 0;
        }
        else if(Balle1.bloque == 1 && Balle1.collante == 1)
        {
            Balle1.posBalle.x = Barre1.positionBarre.x + Balle1.differenceXBarreBalle;
            Balle1.positionXprecis = Barre1.positionBarre.x + Balle1.differenceXBarreBalle;
            Balle1.posBalle.y = Barre1.positionBarre.y - 20;
        }
        SDL_BlitSurface(Balle1.imageBalle, NULL, ecran, &Balle1.posBalle);
        if(Balle2.vivante == 1)
        {
            if(Balle2.bloque == 1 && Balle2.collante == 1)
            {
                Balle2.posBalle.x = Barre1.positionBarre.x + Balle2.differenceXBarreBalle;
                Balle2.positionXprecis = Barre1.positionBarre.x + Balle2.differenceXBarreBalle;
                Balle2.posBalle.y = Barre1.positionBarre.y - 20;
            }
            SDL_BlitSurface(Balle2.imageBalle, NULL, ecran, &Balle2.posBalle);
        }
        if(Balle3.vivante == 1)
        {
            if(Balle3.bloque == 1 && Balle3.collante == 1)
            {
                Balle3.posBalle.x = Barre1.positionBarre.x + Balle3.differenceXBarreBalle;
                Balle3.positionXprecis = Barre1.positionBarre.x + Balle3.differenceXBarreBalle;
                Balle3.posBalle.y = Barre1.positionBarre.y - 20;
            }
            SDL_BlitSurface(Balle3.imageBalle, NULL, ecran, &Balle3.posBalle);
        }
        if(Balle4.vivante == 1)
        {
            if(Balle4.bloque == 1 && Balle4.collante == 1)
            {
                Balle4.posBalle.x = Barre1.positionBarre.x + Balle4.differenceXBarreBalle;
                Balle4.positionXprecis = Barre1.positionBarre.x + Balle4.differenceXBarreBalle;
                Balle4.posBalle.y = Barre1.positionBarre.y - 20;
            }
            SDL_BlitSurface(Balle4.imageBalle, NULL, ecran, &Balle4.posBalle);
        }

        position.x = 35;
        position.y = 10;

        if(compteurVie==5)
        {
            SDL_BlitSurface(cinq, NULL, ecran, &position);
        }
        else if(compteurVie==4)
        {
            SDL_BlitSurface(quatre, NULL, ecran, &position);
        }
        else if(compteurVie==3)
        {
            SDL_BlitSurface(trois, NULL, ecran, &position);
        }
        else if(compteurVie==2)
        {
            SDL_BlitSurface(deux, NULL, ecran, &position);
        }
        else if(compteurVie==1)
        {
            SDL_BlitSurface(un, NULL, ecran, &position);
        }
        position.x=5;
        position.y=80;
        switch(chargeTir)
        {
            case 0:
                SDL_BlitSurface(charge0, NULL, ecran, &position);
                break;
            case 1:
                SDL_BlitSurface(charge1, NULL, ecran, &position);
                break;
            case 2:
                SDL_BlitSurface(charge2, NULL, ecran, &position);
                break;
            case 3:
                SDL_BlitSurface(charge3, NULL, ecran, &position);
                break;
            case 4:
                SDL_BlitSurface(charge4, NULL, ecran, &position);
                break;
            case 5:
                SDL_BlitSurface(charge5, NULL, ecran, &position);
                break;
            case 6:
                SDL_BlitSurface(charge6, NULL, ecran, &position);
                break;
            case 7:
                SDL_BlitSurface(charge7, NULL, ecran, &position);
                break;
            case 8:
                SDL_BlitSurface(charge8, NULL, ecran, &position);
                break;
            case 9:
                SDL_BlitSurface(charge9, NULL, ecran, &position);
                break;
            case 10:
                SDL_BlitSurface(charge10, NULL, ecran, &position);
                break;
        }
        if(chargeTir > 10)
            SDL_BlitSurface(charge10, NULL, ecran, &position);

        if(TirNormale.tirVivant == 1)
            SDL_BlitSurface(TirNormale.imageTir, NULL, ecran, &TirNormale.positionTir);

        if(TirPuissant.tirVivant == 1)
            SDL_BlitSurface(TirPuissant.imageTir, NULL, ecran, &TirPuissant.positionTir);

        if(Bonus1.bonus == 1)
        {
            SDL_BlitSurface(Bonus1.imageBonus, NULL, ecran, &Bonus1.posBonus);
        }
        if(Bonus2.bonus == 1)
        {
            SDL_BlitSurface(Bonus2.imageBonus, NULL, ecran, &Bonus2.posBonus);
        }

        sprintf(score, "Score : %d", Bonus1.score);
        texte = TTF_RenderText_Blended(police, score, blanc);

        position.x = 1090;
        position.y = 10;
        SDL_BlitSurface(texte, NULL, ecran, &position);

        position.x = 0;
        position.y = 600;
        SDL_BlitSurface(bordure, NULL, ecran, &position);

        SDL_Flip(ecran);
    }

    Bonus1.scoreP = 0;

    SDL_FreeSurface(un);
    SDL_FreeSurface(deux);
    SDL_FreeSurface(trois);
    SDL_FreeSurface(quatre);
    SDL_FreeSurface(cinq);
    SDL_FreeSurface(Bonus1.imageBonus);
    SDL_FreeSurface(Bonus2.imageBonus);
    SDL_FreeSurface(charge0);
    SDL_FreeSurface(charge1);
    SDL_FreeSurface(charge2);
    SDL_FreeSurface(charge3);
    SDL_FreeSurface(charge4);
    SDL_FreeSurface(charge5);
    SDL_FreeSurface(charge6);
    SDL_FreeSurface(charge7);
    SDL_FreeSurface(charge8);
    SDL_FreeSurface(charge9);
    SDL_FreeSurface(charge10);
    SDL_FreeSurface(briqueA);
    SDL_FreeSurface(briqueB);
    SDL_FreeSurface(briqueBcasser);
    SDL_FreeSurface(briqueC);
    SDL_FreeSurface(briqueCcasser1);
    SDL_FreeSurface(briqueCcasser2);
    SDL_FreeSurface(briqueIndes);
    SDL_FreeSurface(briqueExplo);
    SDL_FreeSurface(Barre1.imageBarre);
    SDL_FreeSurface(Balle1.imageBalle);
    SDL_FreeSurface(Balle2.imageBalle);
    SDL_FreeSurface(Balle3.imageBalle);
    SDL_FreeSurface(Balle4.imageBalle);
    SDL_FreeSurface(TirNormale.imageTir);
    SDL_FreeSurface(TirPuissant.imageTir);
    SDL_FreeSurface(texte);
    SDL_FreeSurface(bordure);

    TTF_CloseFont(police);
    TTF_Quit();
}


void choixNiveau(SDL_Surface* ecran, int* numNiveau)
{
    SDL_Rect position;

    SDL_Surface *choixLvlJouer = NULL, *apercu2 = NULL, *apercu3 = NULL, *apercu4 = NULL, *apercu5 = NULL, *apercu6 = NULL, *apercu7 = NULL, *apercu8 = NULL, *bloque = NULL;
    choixLvlJouer = SDL_LoadBMP("choisirLvlJouer.bmp");

    int continuer=1, numMonde = 0;

    while(continuer==1)
    {
        SDL_Event event;
        while(SDL_PollEvent(&event))
        {
            switch(event.type)
            {
                case SDL_QUIT:
                    exit(EXIT_SUCCESS);
                    break;
                case SDL_KEYDOWN:
                    switch(event.key.keysym.sym)
                    {
                        case SDLK_ESCAPE:
                            main(NULL,NULL);
                            break;
                        case SDLK_1:
                            numMonde=0;
                            choixNiveau2(ecran, &(*numNiveau), numMonde);
                            continuer=0;
                            break;
                        case SDLK_2:
                            numMonde=1;
                            choixNiveau2(ecran, &(*numNiveau), numMonde);
                            continuer=0;
                            break;
                        case SDLK_3:
                            numMonde=2;
                            choixNiveau2(ecran, &(*numNiveau), numMonde);
                            continuer=0;
                            break;
                        case SDLK_4:
                            numMonde=3;
                            choixNiveau2(ecran, &(*numNiveau), numMonde);
                            continuer=0;
                            break;
                        default:
                            break;
                    }
                    break;
            }
        }
        SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 0, 0, 0)); //effacement de l'écran
        position.x=0;
        position.y=0;
        SDL_BlitSurface(choixLvlJouer, NULL, ecran, &position);
        SDL_Flip(ecran);
    }
    SDL_FreeSurface(choixLvlJouer);
}

void choixNiveau2(SDL_Surface* ecran, int* numNiveau, int numMonde)
{
    SDL_Rect position;

    SDL_Surface *fond = NULL, *apercu1 = NULL, *apercu2 = NULL, *apercu3 = NULL, *apercu4 = NULL, *bloque = NULL;
    if(numMonde == 0)
    {
        apercu1 = SDL_LoadBMP("art/prehistoire/apercu1.bmp");
        apercu2 = SDL_LoadBMP("art/prehistoire/apercu2.bmp");
        apercu3 = SDL_LoadBMP("art/prehistoire/apercu3.bmp");
        apercu4 = SDL_LoadBMP("art/prehistoire/apercu4.bmp");
        fond = SDL_LoadBMP("fondPrehistoire.bmp");
    }
    else if(numMonde == 1)
    {
        apercu1 = SDL_LoadBMP("art/egypte/apercu1.bmp");
        apercu2 = SDL_LoadBMP("art/egypte/apercu2.bmp");
        apercu3 = SDL_LoadBMP("art/egypte/apercu3.bmp");
        apercu4 = SDL_LoadBMP("art/egypte/apercu4.bmp");
        fond = SDL_LoadBMP("fondEgypte.bmp");
    }
    else if(numMonde == 2)
    {
        apercu1 = SDL_LoadBMP("art/romeantique/apercu1.bmp");
        apercu2 = SDL_LoadBMP("art/romeantique/apercu2.bmp");
        apercu3 = SDL_LoadBMP("art/romeantique/apercu3.bmp");
        apercu4 = SDL_LoadBMP("art/romeantique/apercu4.bmp");
        fond = SDL_LoadBMP("fondRomeAntique.bmp");
    }
    else if(numMonde == 3)
    {
        apercu1 = SDL_LoadBMP("art/moyenage/apercu1.bmp");
        apercu2 = SDL_LoadBMP("art/moyenage/apercu2.bmp");
        apercu3 = SDL_LoadBMP("art/moyenage/apercu3.bmp");
        apercu4 = SDL_LoadBMP("art/moyenage/apercu4.bmp");
        fond = SDL_LoadBMP("fondMoyenAge.bmp");
    }

    bloque = SDL_LoadBMP("bloque.bmp");

    int continuer=1;

    while(continuer==1)
    {
        SDL_Event event;
        while(SDL_PollEvent(&event))
        {
            switch(event.type)
            {
                case SDL_QUIT:
                    exit(EXIT_SUCCESS);
                    break;
                case SDL_KEYDOWN:
                    switch(event.key.keysym.sym)
                    {
                        case SDLK_ESCAPE:
                            main(NULL,NULL);
                            break;
                        case SDLK_a:
                            if(*numNiveau >= numMonde*4 + 1)
                            {
                                *numNiveau= numMonde*4 + 1;
                                continuer=0;
                            }
                            break;
                        case SDLK_b:
                            if(*numNiveau >= numMonde*4 + 2)
                            {
                                *numNiveau= numMonde*4 + 2;
                                continuer=0;
                            }
                            break;
                        case SDLK_c:
                            if(*numNiveau >= numMonde*4 + 3)
                            {
                                *numNiveau= numMonde*4 + 3;
                                continuer=0;
                            }
                            break;
                        case SDLK_d:
                            if(*numNiveau >= numMonde*4 + 4)
                            {
                                *numNiveau= numMonde*4 + 4;
                                continuer=0;
                            }
                            break;
                        default:
                            break;
                    }
                    break;
            }
        }
        SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 0, 0, 0)); //effacement de l'écran
        position.x=0;
        position.y=0;
        SDL_BlitSurface(fond, NULL, ecran, &position);

        position.x=50;
        position.y=250;
        if(*numNiveau >= numMonde*4 + 1)
            SDL_BlitSurface(apercu1, NULL, ecran, &position);
        else
            SDL_BlitSurface(bloque, NULL, ecran, &position);

        position.x=350;
        position.y=250;
        if(*numNiveau >= numMonde*4 + 2)
            SDL_BlitSurface(apercu2, NULL, ecran, &position);
        else
            SDL_BlitSurface(bloque, NULL, ecran, &position);

        position.x=650;
        position.y=250;
        if(*numNiveau >= numMonde*4 + 3)
            SDL_BlitSurface(apercu3, NULL, ecran, &position);
        else
            SDL_BlitSurface(bloque, NULL, ecran, &position);

        position.x=950;
        position.y=250;
        if(*numNiveau >= numMonde*4 + 4)
            SDL_BlitSurface(apercu4, NULL, ecran, &position);
        else
            SDL_BlitSurface(bloque, NULL, ecran, &position);

        SDL_Flip(ecran);
    }
    SDL_FreeSurface(fond);
    SDL_FreeSurface(apercu2);
    SDL_FreeSurface(apercu3);
    SDL_FreeSurface(apercu4);
}

void initialisationBonus(Bonus *BonusNombre)
{
    BonusNombre->bonus=0;
    BonusNombre->bonusCree=0;
    BonusNombre->typeBonus=0;
    BonusNombre->bonusActive=0;
    BonusNombre->tir=0;
    BonusNombre->tempsMnt = 0;
    BonusNombre->tempsPrece = 0;
    BonusNombre->acc = 0;
    BonusNombre->decc = 0;
}

void initialisationBalle(Balle *BalleNombre)
{
    BalleNombre->x = 0;
    BalleNombre->y = -2;
    BalleNombre->k = 3;
    BalleNombre->Xancien = 0;
    BalleNombre->Yancien = -2;
    BalleNombre->vivante = 1;
    BalleNombre->principale = 1;
    BalleNombre->explosive = 0;
    BalleNombre->collante = 0;
    BalleNombre->bloque = 0;
    BalleNombre->relance = 0;
    BalleNombre->differenceXBarreBalle = 0;
    BalleNombre->imageBalle = SDL_LoadBMP("art/balle.bmp");
}

void initialisationBarre(Barre *BarreNombre)
{
    BarreNombre->tailleBarre = 120;
    BarreNombre->positionBarre.x = 565;
    BarreNombre->positionBarre.y = 570;
    BarreNombre->anciennePosBarre = BarreNombre->positionBarre.x;
    BarreNombre->imageBarre = SDL_LoadBMP("art/barres/12020.bmp");
}
