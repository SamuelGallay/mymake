#ifndef RULE_H
#define RULE_H

typedef struct Rule {
  int nb_deps;
  int nb_cmds;
  char *target;
  char **deps;
  char **cmds;
} Rule;

void print_rule(Rule *r);

void print_list_of_rules(Rule *lr, int nr); 

int free_Rule(Rule *r); 

#endif
