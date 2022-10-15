#include <assert.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>

#include "parser.h"
#include "rules.h"

int max2(int a, int b) { return a < b ? b : a; }

int modified_time(char *path) {
  struct stat attr;
  if (stat(path, &attr) == 0) {
    return attr.st_mtime;
  } else {
    return 0;
  }
}

// Find a rule by its name
Rule *search_target(char *t, Rule *lr, int nr) {
  for (int k = 0; k < nr; k++) {
    if (strcmp(lr[k].target, t) == 0) {
      return &lr[k];
    }
  }
  return NULL;
}

void compile(char *t, Rule *lr, int nr, int max_rec_level) {
  assert(max_rec_level >= 0);
  // printf("Compiling \'%s\'...\n", t);
  Rule *r = search_target(t, lr, nr);
  if (r == NULL) {
    // printf("No rule corresponding to target, nothing to do.\n");
  } else {
    int t_dep = 0; // Most recent dependency modification
    for (int i = 0; i < r->nb_deps; i++) {
      compile(r->deps[i], lr, nr, max_rec_level - 1);
      t_dep = max2(t_dep, modified_time(r->deps[i]));
    }
    if (modified_time(t) == 0 || modified_time(t) <= t_dep) {
      for (int i = 0; i < r->nb_cmds; i++) {
        printf("Command : %s\n", r->cmds[i]);
        system(r->cmds[i]);
      }
    }
  }
  // printf("Done compiling \'%s\' !\n", t);
}

int main(int argc, char *argv[]) {
  int nr;
  Rule *lr = read_rules(&nr);
  assert(lr != NULL);

  // print_list_of_rules(lr, nr);

  if (argc >= 2) {
    compile(argv[1], lr, nr, nr);
  } else {
    compile(lr[0].target, lr, nr, nr);
  }

  // Free memory
  for (int i = 0; i < nr; i++) {
    free_Rule(&lr[i]);
  }
  free(lr);

  // printf("\nHello World !\n");
}
