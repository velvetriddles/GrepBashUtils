#include "s21_grep.h"

void grep_flags(int argc, char* argv[], struct flags* flag, char* ef_arg) {
  int ch = 0;
  int e_count = 0;
  char* optstring = "e:ivclnhsf:o";

  while ((ch = getopt_long(argc, argv, optstring, 0, 0)) != -1) {
    switch (ch) {
      case 'e':
        flag->e = 1;
        add_e_arg(optarg, &e_count, ef_arg);
        break;
      case 'i':
        flag->i = 1;
        break;
      case 'v':
        flag->v = 1;
        break;
      case 'c':
        flag->c = 1;
        break;
      case 'l':
        flag->l = 1;
        break;
      case 'n':
        flag->n = 1;
        break;
      case 'h':
        flag->h = 1;
        break;
      case 's':
        flag->s = 1;
        break;
      case 'f':
        flag->f = 1;
        add_f_arg(optarg, &e_count, ef_arg, argv);
        break;
      case 'o':
        flag->o = 1;
        break;
      case '?':
        exit(1);
      default:
        break;
    }
  }
}

void add_e_arg(char* optarg, int* e_count, char* ef_arg) {
  if (*e_count != 0) {
    strcat(ef_arg, "|");
  }
  strcat(ef_arg, optarg);
  *e_count += 1;
}

void add_f_arg(char* optarg, int* e_count, char* ef_arg, char* argv[]) {
  FILE* fp_f = NULL;
  char line[BUFFER] = {0};

  if ((fp_f = fopen(optarg, "rb")) == NULL) {
    fprintf(stderr, "%s: %s: No such file or directory\n", argv[0], optarg);
    exit(2);
  } else {
    while (fgets(line, BUFFER, fp_f) != NULL) {
      if (line[strlen(line) - 1] == '\n') line[strlen(line) - 1] = 0;
      if (*e_count > 0) strcat(ef_arg, "|");
      strcat(ef_arg, line);
    }
    fclose(fp_f);
  }
}

void open_files(int argc, char* argv[], char* ef_arg, struct flags flag) {
  FILE* fp;
  int files_count = argc - optind;

  for (; optind < argc; optind++) {
    if ((fp = fopen(argv[optind], "rb")) == NULL) {
      if (flag.s == 0) {
        fprintf(stderr, "%s: %s: No such file or directory\n", argv[0],
                argv[optind]);
      }
    } else {
      reg_compile(argv, ef_arg, fp, flag, files_count);
      fclose(fp);
    }
  }
}

void reg_compile(char** argv, char* my_reg, FILE* fp, struct flags flag,
                 int files_count) {
  regex_t pattern;
  regmatch_t pmatch[1] = {0};
  size_t nmatch = 1;

  int err;
  char err_msg[MAX_ERR_LENGTH];
  char str[BUFFER];
  size_t n_line = 1;
  int lines_count = 0;
  int i_option = 0;

  if (flag.i != 0) i_option = REG_ICASE;
  err = regcomp(&pattern, my_reg, REG_EXTENDED | i_option);
  if (err != 0) {
    regerror(err, &pattern, err_msg, MAX_ERR_LENGTH);
    fprintf(stderr, "Error analyzing regular expression '%s': %s.\n", my_reg,
            err_msg);
    exit(3);
  }
  while (feof(fp) == 0) {
    if (fgets(str, BUFFER, fp)) {
      int new_line_o_counter = 1;
      err = regexec(&pattern, str, nmatch, pmatch, 0);
      if (flag.v != 0) err = err ? 0 : 1;
      if (err == 0) {
        if (flag.c == 0 && flag.l == 0) {
          if (files_count > 1 && flag.h == 0) {
            printf("%s:", argv[optind]);
          }
          if (flag.n != 0) {
            printf("%lu:", n_line);
          }
          if (flag.o != 0 && flag.v == 0) {
            new_line_o_counter = 0;
            char* ptr = str;
            while (err == 0) {
              if (pmatch[0].rm_eo == pmatch[0].rm_so) break;
              printf("%.*s\n", (int)(pmatch[0].rm_eo - pmatch[0].rm_so),
                     ptr + pmatch[0].rm_so);
              ptr += pmatch[0].rm_eo;
              err = regexec(&pattern, ptr, nmatch, pmatch, REG_NOTBOL);
            }
          }
          if (!flag.o || flag.v) printf("%s", str);
          if (str[strlen(str) - 1] != '\n' && new_line_o_counter != 0) {
            printf("\n");
          }
        }
        lines_count++;
      }
      n_line++;
    }
  }
  if (flag.c != 0) {
    if (files_count > 1 && !flag.h) {
      printf("%s:", argv[optind]);
    }
    if (flag.l && lines_count)
      printf("1\n");
    else
      printf("%d\n", lines_count);
  }
  if (flag.l && lines_count) {
    printf("%s\n", argv[optind]);
  }
  regfree(&pattern);
}
