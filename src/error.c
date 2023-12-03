#include "../include/pipex.h"
#include <stdio.h>

void    error_handler(int n)
{
    if (n == INPUT_ERROR)
        printf("input: Incorrect number of arguments\n");
    else if (n == OPEN_ERROR)
        perror("open");
    else if (n == FORK_ERROR)
        perror("fork");
    else if (n == PIPE_ERROR)
        perror("pipe");
    else if (n == CMD_ERROR)
        perror("command");
    else if (n == EXECVE_ERROR)
        perror("execve");
    else if (n == DUP2_ERROR)
        perror("dup2");
    else if (n == CLOSE_ERROR)
        perror("close");
    else
     printf("Unkown error\n");
    exit(EXIT_FAILURE);
}
