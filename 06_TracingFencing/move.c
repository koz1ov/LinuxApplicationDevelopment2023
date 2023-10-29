#include <stdio.h>
#include <stdlib.h>

#define BAD_IN_READ 4
#define BAD_OUT_WRITE 5

void handle_error(FILE* in_file, FILE* out_file, const char* out_filename, int code) {
  fclose(in_file);
  fclose(out_file);
  remove(out_filename);
  exit(code);
}

int main(int argc, char *argv[]) {
  if (argc < 3) {
    fprintf(stderr, "%s\n", "argc < 3");
    return 1;
  }     

  const char *from_filename = argv[1];
  const char *to_filename = argv[2];
  FILE* in_file = fopen(from_filename, "r");
  if (!in_file) {
    perror("Failed to open input file.");
    return 2;
  }
  FILE* out_file = fopen(to_filename, "w");
  if (!out_file) {
    perror("Failed to open output file.");
    return 3;
  }

  int c;
  while ((c = fgetc(in_file)) != EOF) {
    if (fputc(c, out_file) == EOF) {
      handle_error(in_file, out_file, to_filename, BAD_OUT_WRITE); 
    }
  }

  if (ferror(in_file)) {
    handle_error(in_file, out_file, to_filename, BAD_IN_READ);
  }

  fclose(in_file); 
  if (fclose(out_file)) {
    remove(to_filename);
    return 7;
  }
  remove(from_filename);

  return 0;
}

