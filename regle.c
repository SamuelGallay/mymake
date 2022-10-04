#include "regle.h"
#include <stdlib.h>
#include <stdio.h>

struct Regle_t { char cible[32] ; char* prerequis[32] ; char* commandes[64] ; };

Regle* Regle_create(char* nom ) {
    char* line = NULL;
    size_t len = 0;
    FILE * fichier = fopen(nom,"r");
    int r = getline(&line,&len,fichier);
    fclose(fichier);
}

void Regle_free(Regle * r) {
    free(r) ;
}
