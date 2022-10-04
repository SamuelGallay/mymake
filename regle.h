#ifndef REGLE_H_INCLUDED
#define REGLE_H_INCLUDED

typedef struct Regle_t Regle;

Regle* Regle_create(char* nom );

void Regle_free(Regle * r);

#endif // REGLE_H_INCLUDED
