#include "pipex.h"

int	check_pathfile(t_token *token, t_pipex *p, int f)
{
	if (f == 1 && !(p->limiter) && access(p->file1, R_OK))
		return (-1);
	if (f == 2 && !access(p->file2, F_OK) && access(p->file2, W_OK))
		return (-1);
	if (!((token->path[0] == '.' && token->path[1] == '/')
			|| token->path[0] == '/'))
	{
		write(STDOUT_FILENO, token->path, ft_strlen(token->path));
		write(STDOUT_FILENO, ": command not found\n", 20);
		return (-1);
	}
	return (0);
}

int	first_command(t_pipex *p, int **fd, t_token *token)
{
	if (check_pathfile(token, p, 1) == -1 || p->f1 == -1)
		return (-1);
	dup2(p->f1, STDIN_FILENO);
	dup2((fd[1][1]), STDOUT_FILENO);
	close(p->f1);
	return (0);
}

int	last_command(t_pipex *p, int **fd, t_token *token)
{
	if (p->f2 == -1 || check_pathfile(token, p, 2) == -1)
		return (-1);
	dup2(p->f2, STDOUT_FILENO);
	dup2(fd[p->i][0], STDIN_FILENO);
	close(p->f2);
	return (0);
}

int	close_fd(int **fd, int n)
{
	int	j;

	j = -1;
	while (++j < n)
	{
		close(fd[j][0]);
		close(fd[j][1]);
	}
	return (0);
}

int	exec_command(int **fd, t_token *token, t_pipex *p)
{
	int	k;

	k = 0;
	if (p->i == 0)
		k = first_command(p, fd, token);
	else if (token->next == NULL)
		k = last_command(p, fd, token);
	else
	{
		if (check_pathfile(token, p, 0) == -1)
		{
			close_fd(fd, p->nc + 1);
			return (-1);
		}
		dup2(fd[p->i][0], STDIN_FILENO);
		dup2(fd[p->i + 1][1], STDOUT_FILENO);
	}
	close_fd(fd, p->nc + 1);
	if (k != -1)
		execve(token->path, token->args, NULL);
	return (-1);
}
