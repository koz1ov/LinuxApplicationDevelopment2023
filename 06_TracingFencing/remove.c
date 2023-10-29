#define _GNU_SOURCE
#include <dlfcn.h>
#include <string.h>
#include <stdio.h>
 
typedef int (*remove_func_t)(const char *pathname);

int remove(const char *path)
{
  if (strstr(path, "PROTECT") != NULL) {
    return 0;
  } else {
    remove_func_t libc_remove = dlsym(RTLD_NEXT, "remove");
    return libc_remove(path);
  }
}
