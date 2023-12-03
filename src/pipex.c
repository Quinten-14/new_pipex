#include "../include/pipex.h"
#include "../include/libft.h"
#include <stdlib.h>
#include <unistd.h>

int file_opener(char *file, int perms)
{
    int fd_id;

    if (perms == PERMS_R)
        fd_id = open(file, O_RDONLY, 0777);
    else if (perms == PERMS_WCT)
        fd_id = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
    else if (perms == PERMS_WCA)
        fd_id = open(file, O_WRONLY | O_CREAT | O_APPEND, 0777);
    if (fd_id == FAIL)
        error_handler(OPEN_ERROR);
    return (fd_id);
}

void    exec(char *cmd, char **envp)
{
    char    **cmd_parsed;
    char    *path;

    cmd_parsed = ft_split(cmd, ' ');
    path = get_path(cmd_parsed[0], envp);
    if (execve(path, cmd_parsed, envp) == -1)
    {
        error_handler(CMD_ERROR);
        ft_putendl_fd(cmd_parsed[0], 2);
        ft_free_tab(cmd_parsed);
        exit(1);
    }
}

int ac_doc_checker(int ac, char **av)
{
    size_t  i;
    char    *str_av;
    char    *str_doc;

    if (ac < 5)
        error_handler(INPUT_ERROR);
    str_av = av[1];
    str_doc = "here_doc";
    i = 0;
    while (str_av[i] || str_doc[i])
    {
        if (str_av[i] != str_doc[i])
            return (0);
        i++;
    }
    if (ac < 6)
        error_handler(INPUT_ERROR);
    return (1);
}

void    command_fork(char *cmd, char **envp, int *p_fd)
{
    pid_t   pid;
    int status;

    pid = fork();
    if (pid == FAIL)
        error_handler(FORK_ERROR);
    if (pid == 0)
    {
        close(p_fd[IN]);
        redir_fork(p_fd, STDOUT_FILENO, 1);
        exec(cmd, envp);
        error_handler(EXECVE_ERROR);
    }
    else {
        close(p_fd[OUT]);
        waitpid(pid, &status, 0);
        redir_fork(p_fd, STDIN_FILENO, 0);
    }
}

int main(int ac, char **av, char **envp)
{
    int fd;
    int pipe_fd[2];
    size_t  i;

    if (pipe(pipe_fd) == FAIL)
        error_handler(PIPE_ERROR);
    if (INPUT_CHECK)
    {
        i = 3;
        fd = file_opener(av[ac - 1], PERMS_WCA);
        here_doc(av);
    }
    else
    {
        i = 2;
        fd = file_opener(av[1], PERMS_R);
        redir_main(fd, STDIN_FILENO);
    }
    fd = file_opener(av[ac - 1], PERMS_WCT);
    redir_main(fd, STDOUT_FILENO);
    while (i < ac - 2)
        command_fork(av[i++], envp, pipe_fd);
    exec(av[ac - 2], envp);
}
