#include "regle.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct Regle_t { char cible[32] ; char * prerequis[32] ; char * commandes[64] ; };

Regle Regle_create(char* nom ) {
    char* line = NULL;
    size_t len = 0;
    ssize_t r;
    FILE * fichier = fopen(nom,"r");
    r = getline(&line,&len,fichier);
    Regle regle ;

    char * ligne = strtok(line," : \n");
    regle.cible = ligne;
    int i = 0;
    while (ligne != NULL) {
        ligne = strtok ( NULL, " : \n" );
        regle.prerequis[i] = ligne;
        i =+ 1;
    };

    i = 0;
    while ((r = getline(&line,&len,fichier)) != -1) {
        char * ligne = strtok(line,"\t");
        regle.commandes[i] = line;
        i += 1;
    };
    fclose(fichier);
    return(regle);
}

void Regle_free(Regle * r) {
    free(r) ;
}
