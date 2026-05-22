#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
  char *buffer = NULL;
  size_t size = 0;
  while (1) {
    printf("Please enter some text: ");
    ssize_t characters_read = getline(&buffer, &size, stdin);

    if (buffer[characters_read - 1] == '\n') {
      buffer[characters_read - 1] = '\0';
    }
    printf("Tokens:\n");
    char *saveptr;
    char *token = strtok_r(buffer, " ", &saveptr);
    while (token != NULL) {
      printf("%s\n", token);
      token = strtok_r(NULL, " ", &saveptr);
    }
  }
}
