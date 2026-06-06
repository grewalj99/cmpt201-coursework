#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void input_history(char *history[], int *index, int *count, char *line) {
  if (history[*index] != NULL) {
    free(history[*index]);
  }
  history[*index] = strdup(line);
  *index = (*index + 1) % 5;
  if (*count < 5) {
    (*count)++;
  }
}

int main(void) {
  char *history[5] = {NULL};
  char *line = NULL;
  size_t len = 0;
  int index = 0;
  int count = 0;

  while (1) {
    printf("Enter input: ");
    if (getline(&line, &len, stdin) == -1) {
      break;
    }
    line[strcspn(line, "\n")] = '\0';
    input_history(history, &index, &count, line);
    if (strcmp(line, "print") == 0) {
      int start;
      if (count < 5) {
        start = 0;
      } else {
        start = index;
      }
      for (int i = 0; i < count; i++) {
        int p = (start + i) % 5;
        printf("%s\n", history[p]);
      }
    }
  }

  free(line);

  for (int i = 0; i < 5; i++) {
    free(history[i]);
  }

  return 0;
}
