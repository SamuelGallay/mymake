//#include "regle.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Rule {
  int nb_deps;
  int nb_cmds;
  char *target;
  char **deps;
  char **cmds;
} Rule;


void print_rule(Rule *r){
  printf("%s: ", r->target);
   for (int i = 0; i < r->nb_deps; i++) {
    printf("%s ", r->deps[i]);
   }
   printf("\n");
   for (int i = 0; i < r->nb_cmds; i++) {
    printf("\t%s\n", r->cmds[i]);
  }
}

void print_list_of_rules(Rule *lr, int nr){
  for(int i = 0; i<nr; i++){
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

// Remove leading and trailing blanks while being completly unsafe O(len(l))
char *remove_blanks(char *l) {
  while (*l == ' ' || *l == '\t' || *l == '\n') {
    l++;
  }
  int k = strlen(l) - 1;
  while (k >= 0 && (l[k] == ' ' || l[k] == '\t' || l[k] == '\n')) {
    l[k] = '\0';
    k--;
  }
  return l;
}

Rule* read_rules(int *nb_rules_allocated) {
  FILE *file = fopen("Makefile", "r");
  size_t buf_size = 0;
  char *line = NULL;
  Rule *lr = NULL; // List of rules
  int nr = 0;      // Number of rules
  while (getline(&line, &buf_size, file) != -1) {
    if (line[0] == '\t' && nr > 0) {
      char *command = remove_blanks(line);
      //printf("COMMAND : %s\n\n", command);
      lr[nr - 1].nb_cmds++;
      lr[nr - 1].cmds =
          realloc(lr[nr - 1].cmds, lr[nr - 1].nb_cmds * sizeof(char *));
      lr[nr - 1].cmds[lr[nr - 1].nb_cmds - 1] = malloc(strlen(command) + 1);
      strcpy(lr[nr - 1].cmds[lr[nr - 1].nb_cmds - 1], command);
    }

    else if (strchr(line, ':') != NULL) {
      char *target = strtok(line, ":");
      assert(target != NULL);
      target = remove_blanks(target);
      assert(strlen(target) != 0);

      char *dependencies = strtok(NULL, ":");
      assert(dependencies != NULL);
      dependencies = remove_blanks(dependencies);
      assert(strlen(dependencies) != 0);

      //printf("TARGET : %s\n", target);
      //printf("DEPENDENCIES : %s\n", dependencies);

      int nb_dependencies = 1;
      char **deps = malloc(nb_dependencies * sizeof(char *));
      char *dep = strtok(dependencies, " \t");

      assert(dependencies != NULL);
      deps[nb_dependencies - 1] = malloc((strlen(dep) + 1));
      strcpy(deps[nb_dependencies - 1], dep);

      while ((dep = strtok(NULL, " \t")) != NULL) {
        nb_dependencies++;
        deps = realloc(deps, nb_dependencies * sizeof(char *));
        deps[nb_dependencies - 1] = malloc(strlen(dep) + 1);
        strcpy(deps[nb_dependencies - 1], dep);
      }
      //printf("NB_DEPS : %i\n", nb_dependencies);
      //printf("\n");

      // Creation of the new rule :
      nr++;
      lr = realloc(lr, nr * sizeof(struct Rule));
      assert(lr != NULL);
      lr[nr - 1].target = malloc(strlen(target) + 1);
      strcpy(lr[nr - 1].target, target);
      lr[nr - 1].deps = deps;
      lr[nr - 1].nb_deps = nb_dependencies;
      lr[nr - 1].nb_cmds = 0;
      lr[nr - 1].cmds = NULL;
    }

    else {
      char *nl = remove_blanks(line);
      if (strlen(nl) > 0) {
        printf("I don't know what to do with this non-trivial line: %s\n\n",
               nl);
        exit(-1);
      }
    }
  }
  free(line);
  fclose(file);
  *nb_rules_allocated = nr;
  return lr;
}

int main(){
  int nr;
  Rule* lr = read_rules(&nr);
  assert(lr != NULL);

  print_list_of_rules(lr, nr);

  for (int i = 0; i < nr; i++) {
    free_Rule(&lr[i]);
  }
  free(lr);
}
