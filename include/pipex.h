#ifndef PIPEX_H
# define PIPEX_H

// basic includes
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

// system includes
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>

// Error handling defines
#define INPUT_ERROR 1
#define OPEN_ERROR 2
#define PIPE_ERROR 3
#define FORK_ERROR 4
#define PATH_ERROR 5
#define DUP2_ERROR 6
#define CLOSE_ERROR 7
#define EXECVE_ERROR 8
#define CMD_ERROR 9

/*     macros         */
#define INPUT_CHECK (ac_doc_checker(ac, av) == 1)
#define FAIL -1

// pipe ends
#define IN 0
#define OUT 1

// File permissions
#define PERMS_R 0
#define PERMS_WCT 1
#define PERMS_WCA 2

/*     functions      */

// error error_handler
void    error_handler(int n);

// redirections
void    redir_main(int fd, int target_fd);
void    redir_fork(int fd[2], int target_fd, int pipe_end);

// here_doc
void    here_doc_put_in(char **av, int *p_fd);
void    here_doc(char **av);

// paths
char    *get_path(char *cmd, char **env);
char    *my_getenv(char *name, char **env);

// freeing
void    ft_free_tab(char **tab);

// operations
int     ft_strcmp(char *s1, char *s2);

#endif
