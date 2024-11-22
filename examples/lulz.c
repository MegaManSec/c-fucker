#include <stdarg.h>
#include <stdio.h>
//TODO: _main and __attribute__ ((constructor)) and crt0/_main.
int main(int i, char **j, ...) {
  va_list args;
  va_start(args, i);

  if(i == 5) {
    char *lol = va_arg(args, char *);
    va_end(args);
    printf("hello:%s\n", lol);
    return 0;
  } else {
    main(5, j, "loll");
  }

  va_end(args);

  return 0;
}
