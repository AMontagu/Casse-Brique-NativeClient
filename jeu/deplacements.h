#ifndef DEPLACEMENTS_H_INCLUDED
#define DEPLACEMENTS_H_INCLUDED

void deplacerBarre(int plateau[NBR_BLOC_LARGEUR][NBR_BLOC_HAUTEUR], Barre *BarreNombre, int direction, Balle *BalleNombre);
void deplacerBalle(int plateau[NBR_BLOC_LARGEUR][NBR_BLOC_HAUTEUR], Barre *BarreNombre, Balle *BalleNombre, int *nvlVie, int *compteurVie, int *commencer, int *chargeTir, Bonus *BonusNombre, int *explose);
void deplacerTir(int plateau[NBR_BLOC_LARGEUR][NBR_BLOC_HAUTEUR],Tir *TirType, Bonus *BonusNombre, Balle *BalleNombre, int *explose);
int checkRencontrerBrique(int plateau[NBR_BLOC_LARGEUR][NBR_BLOC_HAUTEUR], int caseTesti, int caseTestJ, Bonus *BonusNombre, Balle *BalleNombre, int *explose);
void deplacerBonus(Bonus *BonusNombre, Barre *BarreNombre);


#endif // DEPLACEMENTS_H_INCLUDED
