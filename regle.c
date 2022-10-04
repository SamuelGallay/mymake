#include "regle.h"
#include <stdlib.h>
#include <stdio.h>

struct Regle_t { char cible[32] ; char* prerequis[32] ; char* commandes[64] ; };

Regle* Regle_create(char* nom ) {
    char* line = NULL;
    size_t len = 0;
    ssize_t r;
    FILE * fichier = fopen(nom,"r");
    r = getline(&line,&len,fichier);
    Regle regle;
    fscanf(fichier,"&s : &s", regle.cible, regle.prerequis )
    while ((r = getline(&line,&len,fichier)) != -1) {

    };
    fclose(fichier);
}

void Regle_free(Regle * r) {
    free(r) ;
}
