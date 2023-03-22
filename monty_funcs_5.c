#include <stdio.h>
#include <stdlib.h>

#define STACK_SIZE 1024

int stack[STACK_SIZE];
int sp = -1;

void push(int value, int line_number) {
  if (sp >= STACK_SIZE - 1) {
    fprintf(stderr, "L%d: Stack overflow\n", line_number);
    exit(EXIT_FAILURE);
  }
  stack[++sp] = value;
}

void pall() {
  int i;
  for (i = sp; i >= 0; i--) {
    printf("%d\n", stack[i]);
  }
}

int main(int argc, char **argv) {
  if (argc != 2) {
    fprintf(stderr, "Usage: %s <input_file>\n", argv[0]);
    return EXIT_FAILURE;
  }

  FILE *fp = fopen(argv[1], "r");
  if (fp == NULL) {
    perror("fopen");
    return EXIT_FAILURE;
  }

  char line[1024];
  int line_number = 0;
  while (fgets(line, sizeof(line), fp)) {
    line_number++;
    if (line[0] == 'p' && line[1] == 'u' && line[2] == 's' && line[3] == 'h') {
      int value = atoi(line + 4);
      if (value == 0 && line[4] != '0') {
        fprintf(stderr, "L%d: usage: push integer\n", line_number);
        return EXIT_FAILURE;
      }
      push(value, line_number);
    } else if (strcmp(line, "pall\n") == 0) {
      pall();
    }
  }

  fclose(fp);
  return EXIT_SUCCESS;
}

