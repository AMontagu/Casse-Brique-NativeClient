#ifndef FICHIERS_H_INCLUDED
#define FICHIERS_H_INCLUDED

void chargerNiveau(int* plateau[NBR_BLOC_HAUTEUR][NBR_BLOC_LARGEUR],int numNiveau);
void sauvegarderNiveau(int plateau[NBR_BLOC_HAUTEUR][NBR_BLOC_LARGEUR],int numNiveau);
void lireNiveauMax(int* numNiveau);
void ecrireNiveauMax(int* numNiveau);

#endif // FICHIERS_H_INCLUDED
