#ifndef GREP_S21_GREP_H_
#define GREP_S21_GREP_H_

#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER 1000
#define MAX_ERR_LENGTH 500

struct flags {
  int e;  // Шаблон |
  int i;  // Игнорирует различия регистра.  |
  int v;  // Инвертирует смысл поиска соответствий. |
  int c;  // Выводит только количество совпадающих строк. |
  int l;  // Выводит только совпадающие файлы.  |
  int n;  // Предваряет каждую строку вывода номером строки из файла ввода. |
  int h;  // Выводит совпадающие строки, не предваряя их именами файлов. |
  int s;  // Подавляет сообщения об ошибках о несуществующих |
  int f;  // Получает регулярные выражения из файла. |
  int o;  // Печатает только совпадающие (непустые) части совпавшей строки. |
};

void grep_flags(int argc, char* argv[], struct flags* flag, char* ef_arg);
void add_e_arg(char* optarg, int* e_count, char* ef_arg);
void add_f_arg(char* optarg, int* e_count, char* ef_arg, char* argv[]);
void open_files(int argc, char* argv[], char* ef_arg, struct flags flag);
void reg_compile(char* argv[], char* my_reg, FILE* fp, struct flags flag,
                 int files_count);

#endif  // GREP_S21_GREP_H_
