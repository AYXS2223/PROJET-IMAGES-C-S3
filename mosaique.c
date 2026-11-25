
#include <stdio.h>
#include "images.h"
#include "mosaique.h"

void decouperImage(Image image)
{
    // Parcourir l'image verticalement, par blocs de 3 lignes
    for (int i = 0; i < image.hauteur; i += 3)
    {
        // Parcourir l'image horizontalement, par blocs de 4 colonnes
        for (int j = 0; j < image.largeur; j += 4)
        {
            // Afficher les coordonnées du début du bloc
            printf("Bloc : debut (%d, %d)\n", i, j);
        }
    }
}
void recupererBloc(Image image, int debutY, int debutX, Pixel bloc[3][4])
{
    for (int ligne = 0; ligne < 3; ligne++)
    {
        for (int colonne = 0; colonne < 4; colonne++)
        {
            bloc[ligne][colonne] =
                image.pixels[debutY + ligne][debutX + colonne];
        }
    }
}
Pixel calculerMoyenneRGB(Pixel bloc[3][4])
{
    int sommeR = 0;
    int sommeG = 0;
    int sommeB = 0;

    for (int ligne = 0; ligne < 3; ligne++)
    {
        for (int colonne = 0; colonne < 4; colonne++)
        {
            sommeR += bloc[ligne][colonne].rouge;
            sommeG += bloc[ligne][colonne].vert;
            sommeB += bloc[ligne][colonne].bleu;
        }
    }

    Pixel moyenne;

    moyenne.rouge = sommeR / 12;
    moyenne.vert = sommeG / 12;
    moyenne.bleu = sommeB / 12;

    return moyenne;
}

void afficherCoordonneesMorceaux(void)
{
    for (int ligne = 0; ligne < 3; ligne++)
    {
        for (int colonne = 0; colonne < 4; colonne++)
        {
            int debutY = ligne * 256;
            int debutX = colonne * 256;

            printf("Morceau : %d | debut : (%d, %d)\n",
                   ligne * 4 + colonne + 1,
                   debutY, debutX);
        }
    }
}