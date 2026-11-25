
#include <stdio.h>
#include <stdlib.h>
#include "images.h"

Image lireImagePPM(const char *nomFichier)
{
    Image image;
    FILE *fichier;

    image.largeur = 0;
    image.hauteur = 0;
    image.pixels = NULL;

    fichier = fopen(nomFichier, "r");

    if (fichier == NULL)
    {
        printf("Erreur : impossible d'ouvrir %s\n", nomFichier);
        return image;
    }

    char format[3];
    int valeurMax;

    if (fscanf(fichier, "%2s", format) != 1 ||
        fscanf(fichier, "%d %d", &image.largeur, &image.hauteur) != 2 ||
        fscanf(fichier, "%d", &valeurMax) != 1)
    {
        printf("Erreur : fichier PPM invalide.\n");
        fclose(fichier);
        return image;
    }

    if (format[0] != 'P' || format[1] != '3' ||
        image.largeur <= 0 || image.hauteur <= 0)
    {
        printf("Erreur : format PPM P3 attendu.\n");
        fclose(fichier);
        image.largeur = 0;
        image.hauteur = 0;
        return image;
    }

    image.pixels = malloc(image.hauteur * sizeof(Pixel *));

    if (image.pixels == NULL)
    {
        fclose(fichier);
        image.largeur = 0;
        image.hauteur = 0;
        return image;
    }

    for (int i = 0; i < image.hauteur; i++)
    {
        image.pixels[i] = malloc(image.largeur * sizeof(Pixel));

        if (image.pixels[i] == NULL)
        {
            for (int j = 0; j < i; j++)
                free(image.pixels[j]);

            free(image.pixels);
            image.pixels = NULL;
            image.largeur = 0;
            image.hauteur = 0;
            fclose(fichier);
            return image;
        }
    }

    for (int i = 0; i < image.hauteur; i++)
    {
        for (int j = 0; j < image.largeur; j++)
        {
            if (fscanf(fichier, "%d %d %d",
                       &image.pixels[i][j].rouge,
                       &image.pixels[i][j].vert,
                       &image.pixels[i][j].bleu) != 3)
            {
                printf("Erreur : pixels incomplets.\n");
                libererImage(&image);
                fclose(fichier);
                return image;
            }
        }
    }

    fclose(fichier);

    printf("Image lue : %s (%d x %d)\n",
           nomFichier, image.largeur, image.hauteur);

    return image;
}

void libererImage(Image *image)
{
    if (image->pixels != NULL)
    {
        for (int i = 0; i < image->hauteur; i++)
            free(image->pixels[i]);

        free(image->pixels);
        image->pixels = NULL;
    }

    image->largeur = 0;
    image->hauteur = 0;
}

Image recadrerImage43(Image image)
{
    Image resultat = {0, 0, NULL};

    int nouvelleLargeur;
    int nouvelleHauteur;
    int debutX = 0;
    int debutY = 0;

    if (image.pixels == NULL)
        return resultat;

    if (image.largeur * 3 > image.hauteur * 4)
    {
        nouvelleLargeur = (image.hauteur * 4) / 3;
        nouvelleHauteur = image.hauteur;
        debutX = (image.largeur - nouvelleLargeur) / 2;
    }
    else
    {
        nouvelleLargeur = image.largeur;
        nouvelleHauteur = (image.largeur * 3) / 4;
        debutY = (image.hauteur - nouvelleHauteur) / 2;
    }

    resultat.largeur = nouvelleLargeur;
    resultat.hauteur = nouvelleHauteur;

    resultat.pixels = malloc(nouvelleHauteur * sizeof(Pixel *));

    if (resultat.pixels == NULL)
        return (Image){0, 0, NULL};

    for (int i = 0; i < nouvelleHauteur; i++)
    {
        resultat.pixels[i] = malloc(nouvelleLargeur * sizeof(Pixel));

        if (resultat.pixels[i] == NULL)
        {
            for (int j = 0; j < i; j++)
                free(resultat.pixels[j]);

            free(resultat.pixels);
            return (Image){0, 0, NULL};
        }

        for (int j = 0; j < nouvelleLargeur; j++)
        {
            resultat.pixels[i][j] =
                image.pixels[i + debutY][j + debutX];
        }
    }

    return resultat;
}
void ecrireImagePPM(const char *nomFichier, Image image)
{
    FILE *fichier = fopen(nomFichier, "w");

    if (fichier == NULL)
    {
        printf("Erreur : impossible de creer %s\n", nomFichier);
        return;
    }

    fprintf(fichier, "P3\n");
    fprintf(fichier, "%d %d\n", image.largeur, image.hauteur);
    fprintf(fichier, "255\n");

    for (int i = 0; i < image.hauteur; i++)
    {
        for (int j = 0; j < image.largeur; j++)
        {
            fprintf(fichier, "%d %d %d\n",
                    image.pixels[i][j].rouge,
                    image.pixels[i][j].vert,
                    image.pixels[i][j].bleu);
        }
    }

    fclose(fichier);

    printf("Image enregistree : %s\n", nomFichier);
}

