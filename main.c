#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "rules.h"
#include "parser.h"
int main() {
  int nr;
  Rule *lr = read_rules(&nr);
  assert(lr != NULL);

  print_list_of_rules(lr, nr);

  for (int i = 0; i < nr; i++) {
    free_Rule(&lr[i]);
  }
  free(lr);
}
