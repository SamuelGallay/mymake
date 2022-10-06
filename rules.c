#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "rules.h"
void print_rule(Rule *r) {
  printf("%s: ", r->target);
  for (int i = 0; i < r->nb_deps; i++) {
    printf("%s ", r->deps[i]);
  }
  printf("\n");
  for (int i = 0; i < r->nb_cmds; i++) {
    printf("\t%s\n", r->cmds[i]);
  }
}

void print_list_of_rules(Rule *lr, int nr) {
  for (int i = 0; i < nr; i++) {
    print_rule(&lr[i]);
    printf("\n");
  }
}

int free_Rule(Rule *r) {
  free(r->target);
  for (int i = 0; i < r->nb_deps; i++) {
    free(r->deps[i]);
  }
  free(r->deps);
  for (int i = 0; i < r->nb_cmds; i++) {
    free(r->cmds[i]);
  }
  free(r->cmds);
  return 0;
}


