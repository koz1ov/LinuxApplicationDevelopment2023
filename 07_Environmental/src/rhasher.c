#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <config.h>

#include <rhash.h>

#ifdef READLINE_ENABLED
#include <readline/readline.h>
#include <readline/history.h>
#endif

int parse_algorithm(char* cmd) {
  if (!strcmp(cmd, "MD5"))
    return RHASH_MD5;
  if (!strcasecmp(cmd, "SHA1"))
    return RHASH_SHA1;
  if (!strcasecmp(cmd, "TTH"))
    return RHASH_TTH;

  return -1;
}

void print_hash(const char* in, unsigned int algorithm, int output_mode) {
  char digest[64];
  int result;
  if (in[0] == '"') {
    result = rhash_msg(algorithm, in + 1, strlen(in) - 2, digest); 
  } else {
    result = rhash_file(algorithm, in, digest);
  }
  if (result == -1) {
   perror("Rhash error");
   return;
  }

  char out[256];
  rhash_print_bytes(out, digest, rhash_get_digest_size(algorithm), output_mode);
  printf("%s\n", out);
}

int main(int argc, char const *argv[]) {
  rhash_library_init();
  size_t len = 0;
  char *input = NULL;

  #ifdef READLINE_ENABLED
  while ((input = readline(NULL))) {
  #else
  while (getline(&input, &len, stdin) != -1) {
  #endif
    char* str_algorithm = strtok(input, " \n");
    int algorithm = parse_algorithm(str_algorithm);
    if (algorithm == -1) {
     fprintf(stderr, "Unknown algorithm\n");
     continue;
    }

    int output_mode = isupper(str_algorithm[0]) ? RHPR_HEX : RHPR_BASE64;
    char* in = strtok(NULL, " \n");
    if (!in) {
     fprintf(stderr, "Empty string\n");
     continue;
    }

    print_hash(in, algorithm, output_mode);
  }

  return 0;
}
