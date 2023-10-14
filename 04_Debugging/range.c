#include <stdio.h>

int main(int argc, char **argv) {
  int start = 0;
  int end = -1;
  int step = 1;
  if (argc == 1) {
    printf("./range (N|[M N [S]]) # print nums from M to N with step S\n");
    return 0;
  }
  if (argc == 2) {
    sscanf(argv[1], "%d", &end);
  }
  if (argc >= 3) {
    sscanf(argv[1], "%d", &start);
    sscanf(argv[2], "%d", &end);
  }
  if (argc >= 4) {
    sscanf(argv[3], "%d", &step);
  }
  for (int i = start; i < end; i += step) {
    printf("%d\n", i);
  }
  return 0;
}
