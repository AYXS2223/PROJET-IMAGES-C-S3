
#ifndef IMAGES_H
#define IMAGES_H

typedef struct
{
    int rouge;
    int vert;
    int bleu;
} Pixel;

typedef struct
{
    int largeur;
    int hauteur;
    Pixel **pixels;
} Image;

Image lireImagePPM(const char *nomFichier);
Image recadrerImage43(Image image);
void libererImage(Image *image);
void ecrireImagePPM(const char *nomFichier, Image image);

#endif
