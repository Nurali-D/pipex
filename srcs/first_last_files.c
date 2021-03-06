#include "pipex.h"

int	first_command_file(t_pipex *p)
{
	int	fd;

	if (access(p->file1, F_OK) == -1)
	{
		write(STDOUT_FILENO, "bash: ", 6);
		write(STDOUT_FILENO, p->file1, ft_strlen(p->file1));
		write(STDOUT_FILENO, ": No such file or directory\n", 28);
		return (-1);
	}
	if (access(p->file1, R_OK) == -1)
	{
		write(STDOUT_FILENO, "bash: ", 6);
		write(STDOUT_FILENO, p->file1, ft_strlen(p->file1));
		write(STDOUT_FILENO, ": Permission denied\n", 20);
		return (-1);
	}
	fd = open(p->file1, O_RDONLY);
	return (fd);
}

int	last_command_file(t_pipex *p)
{
	int	fd;

	if (open(p->file2, O_DIRECTORY) != -1)
	{
		write(STDOUT_FILENO, "bash: ", 6);
		write(STDOUT_FILENO, p->file2, ft_strlen(p->file2));
		write(STDOUT_FILENO, ": Is a directory\n", 17);
		return (-1);
	}
	if (access(p->file2, F_OK) == -1)
	{
		fd = open(p->file2, O_RDWR | O_CREAT, 0644);
		return (fd);
	}
	if (access(p->file2, W_OK) == -1)
	{
		write(STDOUT_FILENO, "bash: ", 6);
		write(STDOUT_FILENO, p->file2, ft_strlen(p->file2));
		write(STDOUT_FILENO, ": Permission denied\n", 20);
		return (-1);
	}
	unlink(p->file2);
	fd = open(p->file2, O_RDWR | O_CREAT, 0644);
	return (fd);
}
