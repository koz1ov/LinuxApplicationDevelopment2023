#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <regex.h>

typedef struct string
{
  char *buf;
  int size;
  int capacity;
} string;

void push_char(string *str, char ch)
{
  if (str->size >= str->capacity) {
      str->capacity = str->capacity * 2 + 1;
      str->buf = realloc(str->buf, str->capacity * sizeof(char));
  }

  str->buf[str->size++] = ch;
}

void handle_error_and_exit(regex_t *regex, int err_code) {
  char buff[128];
  regerror(err_code, regex, buff, sizeof(buff) / sizeof(char));
  printf("%s\n", buff);
  exit(2);
}

char *get_substituted(char **argv, regmatch_t* bags, int bags_num) {
  string res = {NULL, 0, 0};
  
  const char* substituion_str = argv[2];
  const char* original_str = argv[3];

  for (int i = 0; substituion_str[i]; ++i) {
    char ch = substituion_str[i];   
    char next_ch = substituion_str[i + 1];

    if (ch != '\\' || !next_ch) {
      push_char(&res, ch);
      continue;
    }
    
    if (next_ch == '\\') {
      push_char(&res, ch);
      i++;
      continue;
    }

    if (!isdigit(next_ch)) {
      push_char(&res, ch); 
      continue;
    }

    int bag = next_ch - '0';
    if (bag >= bags_num) {
      printf("bag %d doesn't exist\n", bag);
      exit(1); 
    }
    for (int j = bags[bag].rm_so; j < bags[bag].rm_eo; ++j) {
      push_char(&res, original_str[j]); 
    } 
    
    i++;
  }
  push_char(&res, 0);
  return res.buf;
}

#define MAX_BAGS 10

int main(int argc, char **argv) {
  if (argc != 4) {
    printf("argc != 4\n");
    return 1;
  }

  const char* regexp_str = argv[1];
  const char* original_str = argv[3];

  regex_t regex; 
  int reg_comp_code = regcomp(&regex, regexp_str, REG_EXTENDED);
  if (reg_comp_code) 
    handle_error_and_exit(&regex, reg_comp_code);

  regmatch_t bags[MAX_BAGS];
  int reg_exec_code = regexec(&regex, original_str, MAX_BAGS, bags, 0);
  if (reg_exec_code) {
    printf("%s\n", original_str);
    return 0;
  }

  char *substituted = get_substituted(argv, bags, regex.re_nsub + 1);
  char *res = calloc(strlen(substituted) + strlen(original_str) + 1, sizeof(char));
  strncpy(res, original_str, bags[0].rm_so);
  strcat(res, substituted);
  strcat(res, original_str + bags[0].rm_eo);

  printf("%s\n", res);

  regfree(&regex);
  free(substituted);
  free(res);

  return 0;
}
