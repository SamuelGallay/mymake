#ifndef REGLE_H_INCLUDED
#define REGLE_H_INCLUDED

typedef struct Regle Regle_t;

void Regle_free(Regle_t * r) {
    free(r)
}


#endif // REGLE_H_INCLUDED
