#include "s21_grep.h"

int main(int argc, char* argv[]) {
  struct flags flag = {0};
  char ef_arg[BUFFER] = {0};

  if (argc > 1) {
    grep_flags(argc, argv, &flag, ef_arg);
    if (flag.e == 0 && flag.f == 0) {
      strcat(ef_arg, argv[optind]);
      optind += 1;
    }

    open_files(argc, argv, ef_arg, flag);
  }
  return 0;
}
