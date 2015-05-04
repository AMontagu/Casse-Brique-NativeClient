#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>

#include "constantes.h"
#include "jouer.h"
#include "fichiers.h"

int main(int argc, char *argv[])
{
    SDL_Surface *ecran = NULL, *menu = NULL;
    SDL_Rect positionMenu;

    int continuer = 1;
    Bonus BonusNombre;

    SDL_Init(SDL_INIT_VIDEO);
    SDL_WM_SetIcon(SDL_LoadBMP("arkanoid.bmp"),NULL);
    ecran = SDL_SetVideoMode(LARGEUR_FENETRE, HAUTEUR_FENETRE, 32, SDL_HWSURFACE|SDL_DOUBLEBUF);
    SDL_WM_SetCaption("Casse-Briques",NULL);

    menu = SDL_LoadBMP("menu.bmp");
    positionMenu.x=0;
    positionMenu.y=0;
    int numNiveau=1;
    lireNiveauMax(&numNiveau);

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
                            exit(EXIT_SUCCESS);
                            break;
                        case SDLK_a:
                            choixNiveau(ecran, &numNiveau);
                            jouer(ecran, &numNiveau);
                            break;
                        default:
                            break;
                    }
                    break;
                default:
                    break;
            }
        }
        SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 0, 0, 0)); //effacement de l'écran
        SDL_BlitSurface(menu, NULL, ecran, &positionMenu);
        SDL_Flip(ecran);
    }
    SDL_FreeSurface(menu);
    SDL_FreeSurface(ecran);
    SDL_Quit();

    return EXIT_SUCCESS;
}
