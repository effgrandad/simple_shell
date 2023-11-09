#ifndef __SHELL_H__
#define __SHELL_H__

extern char** environ;

#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string.h>
#include <unistd.h>

#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3



/**
 * struct liststr - singly linked list
 * @num: the field value
 * @str: a string
 * @next: points to the next node
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 * struct passinfo - includes pseudo-arguments that can be passed into a
 * function, enabling a uniform prototype for function pointer
 * @arg: a string with arguments that was produced by getline
 * @argv:an array of strings produced from arg
 * @argc: the argument count
 * @fname: the program filename
 * @env: linked list local copy of environ
 * @environ: personalized altered version of environ from LL env
 * @history: the history node
 * @alias: the alias node
 * @cmd_buf: address of pointer to cmd_buf
 * @cmd_buf_type: CMD_type ||, &&, ;
 * @readfd: the fd from which to read line input
 * @history_count: the history line number count
 * @linecount_flag: count number of line of input
 */
typedef struct passinfo
{
	char **argv;
	int argc;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int linecount_flag;

	char **cmd_buf;
	int cmd_buf_type; 
	int readfd;
	int history_count;
} info_t;

#define INFO_INIT

int _putchar(char m);
int _puts(const char *z);
char **str_tow2(char *str, char u);
char **str_tow(char *str, char *u);
int my_unsetenv(info_t *info);
char *get_env(info_t *info, const char *name);
int assemble_env_list(info_t *info);
int my_setenv(info_t *info);
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

int is_chain(info_t *, char *, size_t *);
void check_chain(info_t *, char *, size_t *, size_t, size_t);
char *_memset(char *, char, unsigned int);
void ffree(char **);
void *_realloc(void *, unsigned int, unsigned int);
int bfree(void **);

#endif
