#ifndef BONUS_H_INCLUDED
#define BONUS_H_INCLUDED

void lancementBonus(Bonus *BonusNombre, int *compteurVie, Barre *BarreNombre, Balle *Balle1, Balle *Balle2, Balle *Balle3, Balle *Balle4);
void bonusVie(int *compteurVie);
void bonusBarre(Barre *BarreNombre);
void bonusAcc(Balle *Balle1, Balle *Balle2, Balle *Balle3, Balle *Balle4, Bonus *BonusNombre);
void bonusDec(Balle *Balle1, Balle *Balle2, Balle *Balle3, Balle *Balle4, Bonus *BonusNombre);
void doublementBalle(Balle *Balle1, Balle *Balle2, Balle *Balle3, Balle *Balle4);
void balleCollante(Balle *Balle1, Balle *Balle2, Balle *Balle3, Balle *Balle4);
void balleExplosive(Balle *Balle1, Balle *Balle2, Balle *Balle3, Balle *Balle4);

#endif // BONUS_H_INCLUDED
