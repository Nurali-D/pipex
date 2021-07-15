#include "pipex.h"

void	free_p(t_pipex *p)
{
	t_token	*tmp;
	t_token	*tmp2;
	int		i;

	tmp = p->tokens;
	while (tmp)
	{
		if (tmp->args)
		{
			i = 0;
			while (tmp->args[i])
			{
				free(tmp->args[i]);
				i++;
			}
			free(tmp->args);
		}
		if (tmp->path)
			free(tmp->path);
		tmp2 = tmp;
		tmp = tmp->next;
		free(tmp2);
	}
	free(p);
}

void	free_fd_pid_p(int **fd, int *pid, t_pipex *p)
{
	int	i;

	i = -1;
	while (p && ++i < p->nc + 1)
	{
		if (fd && fd[i])
			free(fd[i]);
	}
	if (fd)
		free(fd);
	if (pid)
		free(pid);
	free_p(p);
}
