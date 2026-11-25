
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <dirent.h>
#include "initialiser.h"
#include "images.h"

void convertirImages(void)
{
    DIR *dossier;
    struct dirent *fichier;

    char commande[1024];
    char nomImage[256];
    char nomSansExtension[256];
    char *extension;

    dossier = opendir("IMAGES/BASE");

    if (dossier == NULL)
    {
        printf("Erreur : impossible d'ouvrir le dossier BASE.\n");
        return;
    }

    system("mkdir -p IMAGES/BASE_PPM");

    while ((fichier = readdir(dossier)) != NULL)
    {
        extension = strrchr(fichier->d_name, '.');

        if (extension != NULL &&
            (strcasecmp(extension, ".jpg") == 0 ||
             strcasecmp(extension, ".jpeg") == 0))
        {
            if (strlen(fichier->d_name) >= sizeof(nomImage))
    continue;

snprintf(nomImage, sizeof(nomImage), "%s", fichier->d_name);
snprintf(nomSansExtension, sizeof(nomSansExtension), "%s", nomImage);

            extension = strrchr(nomSansExtension, '.');

            if (extension != NULL)
            {
                *extension = '\0';
            }

            snprintf(commande, sizeof(commande),
                     "magick \"IMAGES/BASE/%s\" -compress none \"IMAGES/BASE_PPM/%s.ppm\"",
                     nomImage, nomSansExtension);

            printf("Conversion : %s\n", nomImage);

            if (system(commande) != 0)
            {
                printf("Erreur de conversion : %s\n", nomImage);
            }
        }
    }

    closedir(dossier);

    printf("Conversion terminee !\n");
}
void recadrerImages(void)
{
    DIR *dossier;
    struct dirent *fichier;
    char cheminSource[512];
    char cheminDestination[512];
    char *extension;

    system("mkdir -p IMAGES/RECADREES");

    dossier = opendir("IMAGES/BASE_PPM");

    if (dossier == NULL)
    {
        printf("Erreur : impossible d'ouvrir BASE_PPM.\n");
        return;
    }

    while ((fichier = readdir(dossier)) != NULL)
    {
        extension = strrchr(fichier->d_name, '.');

        if (extension != NULL && strcasecmp(extension, ".ppm") == 0)
        {
            snprintf(cheminSource, sizeof(cheminSource),
                     "IMAGES/BASE_PPM/%s", fichier->d_name);

            snprintf(cheminDestination, sizeof(cheminDestination),
                     "IMAGES/RECADREES/%s", fichier->d_name);

            Image image = lireImagePPM(cheminSource);

            if (image.pixels != NULL)
            {
                Image recadree = recadrerImage43(image);

                if (recadree.pixels != NULL)
                {
                    ecrireImagePPM(cheminDestination, recadree);
                    libererImage(&recadree);
                }

                libererImage(&image);
            }
        }
    }

    closedir(dossier);

    printf("Recadrage termine !\n");
}
