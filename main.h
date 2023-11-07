#ifndef __MAIN_H__
#define __MAIN_H__

extern char** environ;

#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string.h>
#include <unistd.h>

int my_unset_env(info_t *info);
char *get_env(info_t *info, const char *name);
int assemble_env_list(info_t *info);
int my_set_env(info_t *info);
int my_env(info_t *info);

int unset_alias(info_t *info, char *str);
int my_alias(info_t *info);
int print_alias(list_t *node);
int set_alias(info_t *info, char *str);
int my_history(info_t *info);

int print_prompt(int terminal);
int tokenize_input(char *buffer, char *token_array[], char *delimiter, int read_count);
char *_strchr(const char *str, char c);

char *_strncpy(char *dest, char *src, int m);
char *_strncat(char *dest, char *src, int m);
char *_strchr(char *s, char d);
char *get_history_file(info_t *info);

int write_history(info_t *info);
int read_history(info_t *info);
int build_history_list(info_t *info, char *buf, int linecount);
int renumber_history(info_t *info);

ssize_t input_buf(info_t *info, char **buf, size_t *length);
ssize_t get_input(info_t *info);
ssize_t read_buf(info_t *info, char *buf, size_t *q);
int get_line(info_t *info, char **ptr, size_t *length);
void sig_hAndler(__attribute__((unused))int sig_num);

#endif
