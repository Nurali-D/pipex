#include "pipex.h"

int	**malloc_fd_pid(int **fd, int **pid, t_pipex *p)
{
	int	i;

	fd = (int **)malloc(sizeof(int *) * (p->nc + 1));
	if (!fd)
	{
		free_fd_pid_p(fd, *pid, p);
		put_error_exit("malloc error");
	}
	i = -1;
	while (++i < p->nc + 1)
	{
		fd[i] = (int *)malloc(sizeof(int) * 2);
		if (!fd[i])
		{
			free_fd_pid_p(fd, *pid, p);
			put_error_exit("malloc error");
		}
	}
	*pid = (int *)malloc(sizeof(int) * p->nc);
	if (!(*pid))
	{
		free_fd_pid_p(fd, *pid, p);
		put_error_exit("malloc error");
	}
	return (fd);
}

void	make_pipes(t_pipex *p, int **fd, int *pid)
{
	int	i;

	i = -1;
	while (++i < p->nc + 1)
	{
		if (pipe(fd[i]) == -1)
		{
			free_fd_pid_p(fd, pid, p);
			put_error_exit("pipe error");
		}
	}
}

int	execute_commands(t_pipex *p, int **fd, int *pid)
{
	int		i;
	t_token	*tmp;

	tmp = p->tokens;
	i = 0;
	while (tmp)
	{
		pid[i] = fork();
		if (pid[i] < 0)
			return (1);
		else if (pid[i] == 0)
		{
			p->i = i;
			if (exec_command(fd, tmp, p) == -1)
				return (-1);
		}
		tmp = tmp->next;
		i++;
	}
	close_fd(fd, p->nc + 1);
	i = -1;
	while (++i < p->nc)
		waitpid(pid[i], 0, 0);
	return (0);
}

int	execute_pipes(t_pipex *p)
{
	int		**fd;
	int		*pid;
	int		temp_fd;
	char	buf[1];

	fd = NULL;
	pid = NULL;
	fd = malloc_fd_pid(fd, &pid, p);
	make_pipes(p, fd, pid);
	if (execute_commands(p, fd, pid) == 0 && 
			(open(p->file2, __O_DIRECTORY) != -1 || access(p->file2, W_OK) == -1))
	{
		temp_fd = open("temp-file2", O_RDONLY);
		while (read(temp_fd, buf, 1) > 0)
			write(STDERR_FILENO, buf, 1);
		close(temp_fd);
		unlink("temp-file2");
	}

	if (!access("flag", F_OK) && !access("temp-file3", F_OK))
	{
		temp_fd = open("temp-file3", O_RDONLY);
		while (read(temp_fd, buf, 1) > 0)
			write(STDERR_FILENO, buf, 1);
		close(temp_fd);
		unlink("temp-file3");
		unlink("flag");
	}
	free_fd_pid_p(fd, pid, p);
	unlink("temp-file");
	return (0);
}
