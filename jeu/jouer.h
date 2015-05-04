#ifndef JOUER_H_INCLUDED
#define JOUER_H_INCLUDED

void jouer(SDL_Surface* ecran,int* numNiveau);
void choixNiveau(SDL_Surface* ecran, int* numNiveau);
void choixNiveau2(SDL_Surface* ecran, int* numNiveau, int numMonde);
void initialisationBonus(Bonus *BonusNombre);
void initialisationBalle(Balle *BalleNombre);
void initialisationBarre(Barre *BarreNombre);

#endif // JOUER_H_INCLUDED
