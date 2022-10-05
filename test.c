#include "regle.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main() {
    char texte[] = "mymake: main.o regle.o regle.h";
    char * ligne = strtok(texte," : \n");
    while (ligne != NULL) {
        printf("%s \n",ligne);
        ligne = strtok ( NULL, " : \n" );
    };
}

