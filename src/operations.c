#include "../include/pipex.h"
#include <unistd.h>

void    redir_main(int fd, int target_fd)
{
    if (dup2(fd, target_fd) == FAIL)
        error_handler(DUP2_ERROR);
    if (close(fd) == FAIL)
        error_handler(CLOSE_ERROR);
}

void    redir_fork(int fd[2], int target_fd, int pipe_end)
{
    if (pipe_end == IN)
    {
        if (close(fd[OUT] == FAIL))
                error_handler(CLOSE_ERROR);
    }
    else if (pipe_end == OUT)
    {
        if (close(fd[IN] == FAIL))
                error_handler(CLOSE_ERROR);
    }
    if (dup2(fd[pipe_end], target_fd) == FAIL)
        error_handler(DUP2_ERROR);
}

int	ft_strcmp(char *s1, char *s2)
{
	size_t	i;

	i = 0;
	if (!s1)
		return (1);
	while (s1[i] || s2[i])
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (0);
}
