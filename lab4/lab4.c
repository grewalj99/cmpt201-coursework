#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define EXTRA_SIZE 256
#define BLOCK_SIZE 128
#define BUF_SIZE 100

struct header {
  uint64_t size;
  struct header *next;
};

void handle_error(char *msg) {
  perror(msg);
  exit(1);
}

void print_out(char *format, void *data, size_t data_size) {
  char buf[BUF_SIZE];
  ssize_t len = snprintf(buf, BUF_SIZE, format,
                         data_size == sizeof(uint64_t) ? *(uint64_t *)data : *(void **)data);
  if (len < 0) {
    handle_error("snprintf");
  }
  write(STDOUT_FILENO, buf, len);
}

int main() {
  void *new_space = sbrk(EXTRA_SIZE);
  struct header *first_block = (struct header *)new_space;
  struct header *second_block = (struct header *)((char *)new_space + BLOCK_SIZE);

  first_block->size = BLOCK_SIZE;
  first_block->next = NULL;
  second_block->size = BLOCK_SIZE;
  second_block->next = first_block;

  char *first_data = (char *)first_block + sizeof(struct header);
  char *second_data = (char *)second_block + sizeof(struct header);
  int data_size = BLOCK_SIZE - sizeof(struct header);

  memset(first_data, 0, data_size);
  memset(second_data, 1, data_size);

  print_out("First block: %p\n", &first_block, sizeof(first_block));
  print_out("Second_block: %p\n", &second_block, sizeof(second_block));

  print_out("First block size: %lu\n", &first_block->size, sizeof(first_block->size));
  print_out("First block next: %p\n", &first_block->next, sizeof(first_block->next));

  print_out("Second block size: %lu\n", &second_block->size, sizeof(second_block->size));
  print_out("Second block next: %p\n", &second_block->next, sizeof(second_block->next));

  for (int i = 0; i < data_size; i++) {
    uint64_t value = first_data[i];
    print_out("%lu\n", &value, sizeof(value));
  }
  for (int i = 0; i < data_size; i++) {
    uint64_t value = second_data[i];
    print_out("%lu\n", &value, sizeof(value));
  }

  return 0;
}
