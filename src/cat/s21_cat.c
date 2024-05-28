#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 10000

typedef enum {
  MODE_NORMAL,
  MODE_NUMBER_NONBLANK,
  MODE_SHOW_ENDS,
  MODE_NUMBER,
  MODE_SQUEEZE_BLANK,
  MODE_SHOW_TABS,
  MODE_SHOW_NONPRINTING,
  MODE_SHOW_NONPRINTING_ENDS,
  MODE_SHOW_TABS_NONPRINTING,
  MODE_UNKNOWN
} CatMode;

void process_file(CatMode mode, const char* filename);
void print_normal(FILE* file);
void print_number_nonblank(FILE* file);
void print_show_ends(FILE* file);
void print_number(FILE* file);
void print_squeeze_blank(FILE* file);
void print_show_tabs(FILE* file);
void print_show_nonprinting(FILE* file);
void print_show_nonprinting_ends(FILE* file);
void print_show_tabs_nonprinting(FILE* file);

CatMode get_mode(const char* flag);

int main(int argc, char* argv[]) {
  CatMode mode = MODE_NORMAL;
  int i = 1;

  if (argc < 2) {
    fprintf(stderr, "Usage: %s [FLAG]... [FILE]...\n", argv[0]);
    return 1;
  }

  if (argc > 2) {
    mode = get_mode(argv[1]);
    if (mode == MODE_UNKNOWN) {
      fprintf(stderr, "Unknown flag: %s\n", argv[1]);
      return 1;
    }
    i = 2;
  }

  for (; i < argc; i++) {
    process_file(mode, argv[i]);
  }

  return 0;
}

void process_file(CatMode mode, const char* filename) {
  FILE* file = fopen(filename, "r");
  if (file == NULL) {
    fprintf(stderr, "Cannot open file: %s\n", filename);
    return;
  }

  switch (mode) {
    case MODE_NORMAL:
      print_normal(file);
      break;
    case MODE_NUMBER_NONBLANK:
      print_number_nonblank(file);
      break;
    case MODE_SHOW_ENDS:
      print_show_ends(file);
      break;
    case MODE_NUMBER:
      print_number(file);
      break;
    case MODE_SQUEEZE_BLANK:
      print_squeeze_blank(file);
      break;
    case MODE_SHOW_TABS:
      print_show_tabs(file);
      break;
    case MODE_SHOW_NONPRINTING:
      print_show_nonprinting(file);
      break;
    case MODE_SHOW_NONPRINTING_ENDS:
      print_show_nonprinting_ends(file);
      break;
    case MODE_SHOW_TABS_NONPRINTING:
      print_show_tabs_nonprinting(file);
      break;
    default:
      break;
  }

  fclose(file);
}

// cat
void print_normal(FILE* file) {
  char line[MAX_LINE_LENGTH];
  while (fgets(line, sizeof(line), file) != NULL) {
    printf("%s", line);
  }
}

//-b

void print_number_nonblank(FILE* file) {
  char line[MAX_LINE_LENGTH];
  int line_number = 1;
  while (fgets(line, sizeof(line), file) != NULL) {
    if (line[0] != '\n') {
      printf("%6d\t%s", line_number++, line);
    } else {
      printf("%s", line);
    }
  }
}

//-E
void print_show_ends(FILE* file) {
  char line[MAX_LINE_LENGTH];
  while (fgets(line, sizeof(line), file) != NULL) {
    size_t len = strlen(line);
    if (len > 0 && line[len - 1] == '\n') {
      line[len - 1] = '$';
      printf("%s\n", line);
    } else {
      printf("%s", line);
    }
  }
}

// -n
void print_number(FILE* file) {
  char line[MAX_LINE_LENGTH];
  int line_number = 1;
  while (fgets(line, sizeof(line), file) != NULL) {
    printf("%6d\t%s", line_number++, line);
  }
}

// -s
void print_squeeze_blank(FILE* file) {
  char line[MAX_LINE_LENGTH];
  int prev_blank = 0;
  while (fgets(line, sizeof(line), file) != NULL) {
    if (line[0] == '\n') {
      if (!prev_blank) {
        printf("%s", line);
        prev_blank = 1;
      }
    } else {
      printf("%s", line);
      prev_blank = 0;
    }
  }
}

//-T
void print_show_tabs(FILE* file) {
  char line[MAX_LINE_LENGTH];
  while (fgets(line, sizeof(line), file) != NULL) {
    for (size_t i = 0; line[i] != '\0'; i++) {
      if (line[i] == '\t') {
        printf("^I");
      } else {
        printf("%c", line[i]);
      }
    }
  }
}

// -v
void print_show_nonprinting(FILE* file) {
  char line[MAX_LINE_LENGTH];
  while (fgets(line, sizeof(line), file) != NULL) {
    for (size_t i = 0; line[i] != '\0'; i++) {
      if ((line[i] >= 0 && line[i] < 32 && line[i] != '\n' &&
           line[i] != '\t') ||
          line[i] == 127) {
        printf("^%c", line[i] == 127 ? '?' : line[i] + 64);
      } else {
        printf("%c", line[i]);
      }
    }
  }
}

// -e
void print_show_nonprinting_ends(FILE* file) {
  char line[MAX_LINE_LENGTH];
  while (fgets(line, sizeof(line), file) != NULL) {
    for (size_t i = 0; line[i] != '\0'; i++) {
      if (line[i] == '\n') {
        printf("$\n");
      } else if ((line[i] >= 0 && line[i] < 32 && line[i] != '\t') ||
                 line[i] == 127) {
        printf("^%c", line[i] == 127 ? '?' : line[i] + 64);
      } else {
        printf("%c", line[i]);
      }
    }
  }
}

// -t
void print_show_tabs_nonprinting(FILE* file) {
  char line[MAX_LINE_LENGTH];
  while (fgets(line, sizeof(line), file) != NULL) {
    for (size_t i = 0; line[i] != '\0'; i++) {
      if (line[i] == '\t') {
        printf("^I");
      } else if ((line[i] >= 0 && line[i] < 32 && line[i] != '\n' &&
                  line[i] != '\t') ||
                 line[i] == 127) {
        printf("^%c", line[i] == 127 ? '?' : line[i] + 64);
      } else {
        printf("%c", line[i]);
      }
    }
  }
}

CatMode get_mode(const char* flag) {
  if (strcmp(flag, "-b") == 0 || strcmp(flag, "--number-nonblank") == 0) {
    return MODE_NUMBER_NONBLANK;
  } else if (strcmp(flag, "-e") == 0) {
    return MODE_SHOW_NONPRINTING_ENDS;
  } else if (strcmp(flag, "-E") == 0) {
    return MODE_SHOW_ENDS;
  } else if (strcmp(flag, "-n") == 0 || strcmp(flag, "--number") == 0) {
    return MODE_NUMBER;
  } else if (strcmp(flag, "-s") == 0 || strcmp(flag, "--squeeze-blank") == 0) {
    return MODE_SQUEEZE_BLANK;
  } else if (strcmp(flag, "-t") == 0) {
    return MODE_SHOW_TABS_NONPRINTING;
  } else if (strcmp(flag, "-T") == 0) {
    return MODE_SHOW_TABS;
  } else if (strcmp(flag, "-v") == 0) {
    return MODE_SHOW_NONPRINTING;
  } else {
    return MODE_UNKNOWN;
  }
}
