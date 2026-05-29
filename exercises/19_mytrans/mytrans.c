// mytrans.c
#include "myhash.h"
#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void trim(char *str) {
    // remove leading/trailing whitespace
    char *start = str;
    while (*start && isspace((unsigned char)*start)) start++;
    if (start != str) memmove(str, start, strlen(start) + 1);

    size_t len = strlen(str);
    while (len > 0 && isspace((unsigned char)str[len - 1])) {
        str[len - 1] = '\0';
        len--;
    }
}

int load_dictionary(const char *filename, HashTable *table,
                    uint64_t *dict_count) {
  FILE *file = fopen(filename, "r");
  if (!file) {
    perror("无法打开词典文件");
    return -1;
  }

  char line[1024];
  char current_word[100] = {0};
  char current_translation[1024] = {0};
  int in_entry = 0;

    *dict_count = 0;
    while (fgets(line, sizeof(line), file)) {
        trim(line);
        if (line[0] == '\0') continue;

        if (line[0] == '#') {
            // previous entry flush
            if (in_entry && current_word[0] && current_translation[0]) {
                hash_table_insert(table, current_word, current_translation);
                (*dict_count)++;
            }
            // start new word
            strncpy(current_word, line + 1, sizeof(current_word) - 1);
            current_word[sizeof(current_word) - 1] = '\0';
            current_translation[0] = '\0';
            in_entry = 1;
        } else if (strncmp(line, "Trans:", 6) == 0) {
            // translation line
            const char *p = line + 6;
            while (*p && isspace((unsigned char)*p)) p++;
            // append translation
            if (current_translation[0] != '\0') {
                strncat(current_translation, " ", sizeof(current_translation) - strlen(current_translation) - 1);
            }
            strncat(current_translation, p, sizeof(current_translation) - strlen(current_translation) - 1);
        }
    }

    // flush last entry
    if (in_entry && current_word[0] && current_translation[0]) {
        hash_table_insert(table, current_word, current_translation);
        (*dict_count)++;
    }

  fclose(file);
  return 0;
}
