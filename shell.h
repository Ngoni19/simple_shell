#ifndef SHELL_H
#define SHELL_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <wait.h>


/**
 * struct list - linked list for env variables
 * @var: holds environmental variable string
 * @next: points to next node
 */
typedef struct list
{
	char *var;
	struct list *next;

} list_t;
/** prompt user & execute */
int prompt(char **env);

/** string compare */
int _strcmp(char *s1, char *s2);

/**string length function*/
int t_strlen(char *str, int pos, char delm);

/** change directory function */
int _cd(char **str, list_t *env, int num);

/** Handle shell builtins (cd, env, exit) */
int built_in(char **token, list_t *env, int num, char **command);

/** exit shell function*/
int __exit(char **s, list_t *env, int num, char **command);

/** excute child and process PID*/
int _execve(char *argv[], list_t *env, int num);

/** handle unset & set environ variables */
int _unsetenv(list_t **env, char **str);
int _setenv(list_t **env, char **str);

/** find environment variables*/
int _env(char **str, list_t *env);
int find_env(list_t *env, char *str);

/** get commands from user input*/
size_t get_line(char **str);

/**print to linked lists to stdout*/
size_t print_list(list_t *h);

/** function to handle spaces in user cmd */
char *ignore_space(char *str);

/**String hanling function (tokens,copy, concant)*/
char **_str_tok(char *str, char *delm);
char **c_str_tok(char *str, char *delm);
char *_strcat(char *dest, char *src);
char *_strdup(char *str);
char *_strcpy(char *dest, char *src);

/** Match PATH directory function*/
char *_which(char *str, list_t *env);

/** Find and copy requested env variable*/
char *get_env(char *str, list_t *env);

/** Convert int to string function*/
char *int_to_string(int num);

/**Linked list functions from env*/
list_t *env_linked_list(char **env);
list_t *add_end_node(list_t **head, char *str);
int delete_nodeint_at_index(list_t **head, int index);

/** Helping and error handling functions*/
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
void non_interactive(list_t *env);
void free_double_ptr(char **str);
void free_linked_list(list_t *list);
void not_found(char *str, int num, list_t *env);
void cant_cd_to(char *str, int c_n, list_t *env);
void illegal_number(char *str, int c_n, list_t *env);

#endif
