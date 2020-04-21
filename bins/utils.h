#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"

#define LINE_INIT_CHOP 24
#define LINE_CHOP_SIZE 8

status_t copy_file_txt(FILE * ,FILE *);
status_t read_line(char **, bool_t *,FILE*,char);
char ** split_string(char *, char *, size_t *);
void destroy_strings(char **, size_t);
char * strdup(const char *);
#endif
