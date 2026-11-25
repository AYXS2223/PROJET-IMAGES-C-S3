#include <stdio.h>
#include "images.h"
#include "mosaique.h"

int main(void)
{
    Image image = lireImagePPM("IMAGES/RECADREES/animaux_chat.ppm");

    if (image.pixels == NULL)
    {
        printf("Erreur de lecture de l'image.\n");
        return 1;
    }

    Pixel bloc[3][4];

    recupererBloc(image, 0, 0, bloc);

    for (int ligne = 0; ligne < 3; ligne++)
    {
        for (int colonne = 0; colonne < 4; colonne++)
        {
            printf("Pixel (%d,%d) : R=%d G=%d B=%d\n",
                   ligne, colonne,
                   bloc[ligne][colonne].rouge,
                   bloc[ligne][colonne].vert,
                   bloc[ligne][colonne].bleu);
        }
    }

    libererImage(&image);
Pixel moyenne = calculerMoyenneRGB(bloc);

printf("Moyenne RGB : R=%d G=%d B=%d\n",
       moyenne.rouge, moyenne.vert, moyenne.bleu);
    return 0;
}