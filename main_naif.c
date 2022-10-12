#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "parser.h"
#include "rules.h"

Rule *search_target(char *t, Rule *lr, int nr) {
  for (int k = 0; k < nr; k++) {
    if (strcmp(lr[k].target, t) == 0) {
      return &lr[k];
    }
  }
  return NULL;
}

void compile(char *t, Rule *lr, int nr) {
  printf("Compiling \'%s\'...\n", t);
  Rule *r = search_target(t, lr, nr);
  if (r == NULL) {
    // printf("No rule corresponding to target, nothing to do.\n");
  } else {
    for (int i = 0; i < r->nb_deps; i++) {
      compile(r->deps[i], lr, nr);
    }
    for (int i = 0; i < r->nb_cmds; i++) {
      printf("Command : %s\n", r->cmds[i]);
      system(r->cmds[i]);
    }
  }
  printf("Done compiling \'%s\' !\n", t);
}

int main() {
  int nr;
  Rule *lr = read_rules(&nr);
  assert(lr != NULL);

  print_list_of_rules(lr, nr);

  compile(lr[0].target, lr, nr);

  // Free memory
  for (int i = 0; i < nr; i++) {
    free_Rule(&lr[i]);
  }
  free(lr);

  // printf("\nHello World !\n");
}
