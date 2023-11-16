#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>
#include <errno.h>
#include <limits.h>

/* Macros */
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH '\0'
#define STDERR_FILENO 2
#define USE_GETLINE 0
#define HISTORY_MAX 4096
#define HISTORY_FILE ".simple_shell_history"
#define INFO_INIT {NULL, NULL, NULL, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, 0, 0, 0, NULL, 0, 0, NULL, 0, 0, 0, 0, 0, 0}

/* Structures */
typedef struct info
{
    char *arguments;
    char **argumentVector;
    char *path;
    int argumentCount;
    int argumentVectorCount;
    int lineCount;
    char *executableName;
    char **environmentStrings;
    char **environment;
    char *commandBuffer;
    char *originalCommandBuffer;
    char *historyBuffer;
    int historyCount;
    list_t *history;
    list_t *aliasList;
    list_t *env;
    char *envPath;
    char *functionName;
    int commandBufferType;
    int readFileDescriptor;
    int writeFileDescriptor;
    int printPrompt;
    int isatty;
    int envChanged;
    int childPid;
    int lastChildStatus;
    int currentLine;
    int lineCountFlag;
    ssize_t (*print)(const void *, size_t);
} info_t;

typedef struct list
{
    char *str;
    int num;
    struct list *next;
} list_t;

/* Function Prototypes */
int hsh(info_t *, char **);
int populate_env_list(info_t *);
int read_history(info_t *);
void print_prompt(info_t *);
void _eputs(const char *);
ssize_t _puts(const char *, size_t);
void _eputchar(char);
void _putchar(char);
int _strcmp(const char *, const char *);
char *_strdup(const char *);
char *_strcpy(char *, const char *);
char *_strcat(char *, const char *);
char *_strncat(char *, const char *, size_t);
char *_strncpy(char *, const char *, size_t);
char *_strchr(char *, char);
char *convert_number(int, int, int);
char *get_path(char *, char *);
list_t *startsWith(char *, const char *);
ssize_t puts_history(const list_t *);
void remove_comments(char *);
int _getline(info_t *, char **, size_t *);
ssize_t bufferChainedCommands(info_t *, char **, size_t *);
ssize_t get_input(info_t *);
int save_history_to_file(info_t *);
int load_history_from_file(info_t *);
int build_history_list(info_t *, char *, int);
int recompute_history_numbers(info_t *);
ssize_t read_buffer(info_t *, char *, size_t *);
void interrupt_signal_handler(__attribute__((unused))int);
void check_chain(info_t *, char *, size_t *, size_t, size_t);
int is_chain(info_t *, char *, size_t *);
int convert_string_to_integer(char *);
void print_error_info(info_t *, char *);
int write_char_to_fd(char, int);
void print_decimal(int, int);
char *convert_number_to_string(long int, int, int);
void remove_comments(char *);
char *copy_string_n(char *, char *, int);
char *concatenate_strings_n(char *, char *, int);
char *find_character(char *, char);
int convert_string_to_integer(char *);
void print_error_info(info_t *, char *);
void print_decimal(int, int);
char *convert_number_to_string(long int, int, int);
char *remove_comments(char *);
ssize_t buffer_chained_commands(info_t *, char **, size_t *);
ssize_t get_input(info_t *);
ssize_t read_buffer(info_t *, char *, size_t *);
int convert_string_to_integer(char *);
void print_error_info(info_t *, char *);
void print_decimal(int, int);
char *convert_number_to_string(long int, int, int);
void remove_comments(char *);
int copy_environ_to_string_array(info_t *);
int remove_environment_variable(info_t *, char *);
int set_environment_variable(info_t *, char *, char *);
void initialize_info(info_t *);
void fill_info(info_t *, char **);
void release_info(info_t *, int);
char *obtain_history_file_path(info_t *);
int save_history_to_file(info_t *);
int load_history_from_file(info_t *);
int build_history_list(info_t *, char *, int);
int recompute_history_numbers(info_t *);
list_t *add_node_at_start(list_t **, const char *, int);
list_t *add_node_at_end(list_t **, const char *, int);
size_t print_list_strings(const list_t *);
int delete_node_at_index(list_t **, unsigned int);
void free_list(list_t **);
size_t list_len(const list_t *);
char **list_to_strings(list_t *);
size_t print_list(const list_t *);
list_t *node_starts_with(list_t *, char *, char);
ssize_t get_node_index(list_t *, list_t *);
#endif /* SHELL_H */
