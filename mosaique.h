#ifndef MOSAIQUE_H
#define MOSAIQUE_H

#include "images.h"
void afficherCoordonneesMorceaux(void);
void decouperImage(Image image);
void recupererBloc(Image image, int debutY, int debutX, Pixel bloc[3][4]);
Pixel calculerMoyenneRGB(Pixel bloc[3][4]);
#endif