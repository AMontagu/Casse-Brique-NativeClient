#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>

#include "constantes.h"
#include "VetD.h"
#include "fichiers.h"

void victoire(SDL_Surface* ecran, int *numNiveau)
{
    SDL_Surface *gagne = NULL;
    SDL_Rect position;

    gagne = SDL_LoadBMP("gagne.bmp");

    int continuer = 1;
    int niveauActuel;
    int niveauTest=0;

    *numNiveau = *numNiveau+1;

    lireNiveauMax(&niveauTest);
    if(niveauTest < *numNiveau)
    {
        ecrireNiveauMax(&(*numNiveau));
    }

    while(continuer)
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
                            main(NULL, NULL);
                            break;
                        case SDLK_a:
                            niveauActuel = *numNiveau-1;
                            jouer(ecran, &niveauActuel);
                            break;
                        case SDLK_z:
                            jouer(ecran, &(*numNiveau));
                            break;
                        case SDLK_e:
                            main(NULL,NULL);
                            break;
                        default:
                            break;
                    }
                    break;
                default:
                    break;
            }
        }
        SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));

        position.x=0;
        position.y=0;
        SDL_BlitSurface(gagne, NULL, ecran, &position);

        SDL_Flip(ecran);
    }
    SDL_FreeSurface(gagne);
}

//--------------------------------------------------------------------------------------------------------------------

void defaite(SDL_Surface* ecran, int numNiveau)
{
    SDL_Surface *perdu = NULL;
    SDL_Rect position;

    perdu = SDL_LoadBMP("perdu.bmp");

    int continuer = 1;

    while(continuer)
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
                            main(NULL, NULL);
                            break;
                        case SDLK_a:
                            jouer(ecran, &numNiveau);
                            break;
                        case SDLK_z:
                            main(NULL,NULL); //Pensez rajouter paramètres niveau ici
                            break;
                        default:
                            break;
                    }
                    break;
                default:
                    break;
            }
        }
        SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));

        position.x=0;
        position.y=0;
        SDL_BlitSurface(perdu, NULL, ecran, &position);

        SDL_Flip(ecran);
    }
    SDL_FreeSurface(perdu);
}
