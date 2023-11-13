#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include <stdio.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <unistd.h>



/* Represents read/write buffers */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* Command chaining */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

/* Used for conv_numb() */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

/* Used if using system get_n_line() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;

/**
 * struct liststr - Represents singly linked list
 * @num: Represents the number field
 * @str: This is a string
 * @next: Points to the next node
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 * struct passinfo - Contains pseudo-arguments to pass into a function,
 * allows a uniform prototype for a function pointer struct
 * @arg: This is a string generated from getline and contains arguments
 * @argv: An array of strings generated from arg
 * @path: A string path for the current command
 * @argc: The argument count
 * @line_count: Shows the error count
 * @err_num: Used for the error code for exit()s
 * @linecount_flag: If this is on, count this line of input
 * @fname: Represents the program filename
 * @env: Shows linked list local copy of environ
 * @environ: Shows custom modified copy of environ from LL env
 * @history: Represents the history node
 * @alias: This is the alias node
 * @env_changed: It's on if environ was changed
 * @status: Shows the return status of the last exec'd command
 * @cmd_buf: This is on if chaining, and shows the
 * address of the pointer to cmd_buf
 * @cmd_buf_type: CMD_type ||, &&, ;
 * @readfd: The fd from which to read line input
 * @histcount: Shows the history line number count
 */
typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buf; /* Pointer to cmd ; chain buffer, for memory management */
	int cmd_buf_type; /* CMD_type ||, &&, ; */
	int readfd;
	int histcount;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
		0, 0, 0}

/**
 * struct builtin - Contains a built-in string and related function
 * @type: Represents the built-in command flag
 * @func: Stands for the function
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;

/* she_loop.c */
int hsh(info_t *, char **);
int find_built_cmd(info_t *);
void find_exec(info_t *);
void fork_thread(info_t *);

/* parser_shell.c */
int cmd_file(info_t *, char *);
char *dupl_char(char *, int, int);
char *find_cmd_pth(info_t *, char *, char *);

/* loophsh.c */
int loophsh(char **);

/* errors_shell.c */
void _eputs(char *);
int _eputchar(char);
int puts_2_fd(char c, int fd);
int _puts_str_fd(char *str, int fd);

/* string_manipulation.c */
int strg_length(char *);
int comp_strgs(char *, char *);
char *begins_with(const char *, const char *);
char *concat_str(char *, char *);

/* string1_manipulation.c */
char *_strcpy(char *, char *);
char *dupl_str(const char *);
void _puts(char *);
int _putchar(char);

/* string2_manipulation.c */
char *copy_str(char *, char *, int);
char *join_2strgs(char *, char *, int);
char *find_ch_str(char *, char);

/* tokenizer.c */
char **str_split(char *, char *);
char **str_split2(char *, char);

/* realloc_memory.c */
char *fill_mem(char *, char, unsigned int);
void free_str_2(char **);
void *realloc_mem(void *, unsigned int, unsigned int);

/* memory.shell.c */
int free_pnt(void **);

/* a_interact.c */
int interact_mode(info_t *);
int is_del(char, char *);
int is_abcd(int);
int str_2_int(char *);

/* errors1_shell.c */
int conv_str_int(char *);
void prnt_my_err(info_t *, char *);
int print_d(int, int);
char *conv_numb(long int, int, int);
void rem_comnt(char *);

/* built_in.c */
int exit_sh(info_t *);
int cd_dir(info_t *);
int help_info(info_t *);

/* built_in1.c */
int sh_history(info_t *);
int my_alias(info_t *);

/*getLine_sh.c */
ssize_t gets_input(info_t *);
int get_n_line(info_t *, char **, size_t *);
void sigintHandler(int);

/* get_sh_info.c */
void init_struct(info_t *);
void set_struct(info_t *, char **);
void free_struct_fld(info_t *, int);

/* environ_sh.c */
char *get_env(info_t *, const char *);
int sh_env(info_t *);
int setup_env(info_t *);
int rm_env(info_t *);
int populate_env_list(info_t *);

/* get_env.c */
char **get_env_array(info_t *);
int rem_env(info_t *, char *);
int init_n_env(info_t *, char *, char *);

/* history_shell.c */
char *get_hist_file(info_t *info);
int write_hist(info_t *info);
int read_history(info_t *info);
int build_history_list(info_t *info, char *buf, int linecount);
int renum_hist(info_t *info);

/* lists_nodes.c */
list_t *first_node(list_t **, const char *, int);
list_t *last_node(list_t **, const char *, int);
size_t print_str_list(const list_t *);
int del_node_at_index(list_t **, unsigned int);
void free_all_nodes(list_t **);

/* lists1_node.c */
size_t list_length(const list_t *);
char **str_frm_list(list_t *);
size_t prnt_list(const list_t *);
list_t *node_by_prefix(list_t *, char *, char);
ssize_t get_node_index(list_t *, list_t *);

/* var_arrays.c */
int is_chained(info_t *, char *, size_t *);
void chain_status(info_t *, char *, size_t *, size_t, size_t);
int replace_alias(info_t *);
int replace_varry(info_t *);
int replace_string(char **, char *);

#endif
