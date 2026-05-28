#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void) {
  char *line = NULL;
  size_t len = 0;
  while (1) {
    printf("Enter programs to run.\n");
    ssize_t characters_read = getline(&line, &len, stdin);
    if (line[characters_read - 1] == '\n') {
      line[characters_read - 1] = '\0';
    }
    pid_t pid = fork();
    if (pid == 0) {
      execl(line, line, NULL);
      printf("Exec failure\n");
    } else {
      waitpid(pid, NULL, 0);
    }
  }
  return 0;
}
