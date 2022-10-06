#ifndef PARSER_H
#define PARSER_H

#include "rules.h"

char *remove_blanks(char *l);
Rule *read_rules(int *nb_rules_allocated); 

#endif
