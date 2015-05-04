#ifndef CONSTANTES_H_INCLUDED
#define CONSTANTES_H_INCLUDED

    #define TAILLE_BLOC_LARGEUR    60
    #define TAILLE_BLOC_HAUTEUR    30
    #define NBR_BLOC_LARGEUR       20
    #define NBR_BLOC_HAUTEUR       20
    #define LARGEUR_FENETRE        TAILLE_BLOC_LARGEUR * NBR_BLOC_LARGEUR
    #define HAUTEUR_FENETRE        TAILLE_BLOC_HAUTEUR * NBR_BLOC_HAUTEUR

    enum{BRIQUE_A, BRIQUE_B, BRIQUE_B_CASSER, BRIQUE_C, BRIQUE_C_CASSER1, BRIQUE_C_CASSER2, MUR, VIDE, BRIQUE_INDES, BRIQUE_EXPLO, BARRE, BALLE};
    enum{DROITE, GAUCHE};
    enum{NORMAL, PUISSANT};

    typedef struct Balle Balle;
    struct Balle
    {
        float x; //la vitesse horizontale de la balle
        float y; //la vitesse verticale
        float k; //coefficient multiplicateur de vitesse
        float positionXprecis;
        float positionYprecis;
        float Xancien;
        float Yancien;
        int vivante;
        int principale;
        int explosive;
        int collante;
        int bloque;
        int relance;
        int differenceXBarreBalle;
        int ancienK;
        SDL_Surface *imageBalle;
        SDL_Rect posBalle;
    };

    typedef struct Bonus Bonus;
    struct Bonus
    {
        int bonus;
        int bonusCree;
        int bonusActive;
        int typeBonus;
        int tir;
        SDL_Surface *imageBonus;
        SDL_Rect posBonus;
        int acc;
        int decc;
        int tempsMnt;
        int tempsPrece;
        int score;
        int scoreP;
    };

    typedef struct Barre Barre;
    struct Barre
    {
        int tailleBarre;
        SDL_Rect positionBarre;
        SDL_Surface *imageBarre;
        int anciennePosBarre;
    };

    typedef struct Tir Tir;
    struct Tir
    {
        SDL_Surface *imageTir;
        SDL_Rect positionTir;
        int tirVivant;
        int typeTir;
    };


#endif // CONSTANTES_H_INCLUDED
