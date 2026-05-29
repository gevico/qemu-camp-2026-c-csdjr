#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LINE_LENGTH 1024

int parse_replace_command(const char* cmd, char** old_str, char** new_str) {
    if (cmd[0] != 's' || cmd[1] != '/') {
        return -1;
    }

    // format: s/old/new/
    const char *p = cmd + 2; // skip s/
    const char *slash = strchr(p, '/');
    if (!slash) return -1;
    size_t old_len = slash - p;
    const char *p2 = slash + 1;
    const char *slash2 = strchr(p2, '/');
    if (!slash2) return -1;
    size_t new_len = slash2 - p2;

    *old_str = malloc(old_len + 1);
    *new_str = malloc(new_len + 1);
    if (!*old_str || !*new_str) {
        free(*old_str);
        free(*new_str);
        return -1;
    }
    memcpy(*old_str, p, old_len);
    (*old_str)[old_len] = '\0';
    memcpy(*new_str, p2, new_len);
    (*new_str)[new_len] = '\0';

    return 0;
}

void replace_first_occurrence(char* str, const char* old, const char* new) {
    char *pos = strstr(str, old);
    if (!pos) return;

    char buffer[MAX_LINE_LENGTH];
    size_t prefix_len = pos - str;
    size_t old_len = strlen(old);
    size_t new_len = strlen(new);

    // build new string in buffer
    memcpy(buffer, str, prefix_len);
    memcpy(buffer + prefix_len, new, new_len);
    strcpy(buffer + prefix_len + new_len, pos + old_len);

    // copy back
    strcpy(str, buffer);
}

int main(int argc, char* argv[]) {
    const char* replcae_rules = "s/unix/linux/";

    char line[MAX_LINE_LENGTH] = {"unix is opensource. unix is free os."};

    char* old_str = NULL;
    char* new_str = NULL;
    
    if (parse_replace_command(replcae_rules, &old_str, &new_str) != 0) {
        fprintf(stderr, "Invalid replace command format. Use 's/old/new/'\n");
        return 1;
    }

    
    replace_first_occurrence(line, old_str, new_str);
    fputs(line, stdout);

    free(old_str);
    free(new_str);
    return 0;
}
