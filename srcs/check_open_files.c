#include "pipex.h"

int	gnl(char **line)
{
	int		i;
	int		ret;
	char	*buf;

	buf = (char *)malloc(sizeof(char) * 10000);
	*line = buf;
	i = 0;
	write(STDOUT_FILENO, "> ", 2);
	ret = read(STDIN_FILENO, &buf[i], 1);
	while (ret > 0 && buf[i] != '\n')
	{
		i++;
		ret = read(STDIN_FILENO, &buf[i], 1);
	}
	buf[i] = '\0';
	return (ret);
}

int	heredoc_fd(t_pipex *p)
{
	char	*line;
	int		fd;

	fd = open("temp-file", O_RDWR | O_CREAT, 0644);
	while (gnl(&line) > 0)
	{
		if (!strcmp(line, p->limiter))
		{
			free(line);
			close(fd);
			break ;
		}
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	close(fd);
	fd = open("flag", O_RDWR | O_CREAT, 0644);
	close(fd);
	return (open("temp-file", O_RDONLY));
}

int	file_append(t_pipex *p)
{
	int	fd;

	if (open(p->file2, __O_DIRECTORY) != -1)
	{
		fd = open("temp-file2", O_RDWR | O_CREAT, 0644);
		write(fd, "bash: ", 6);
		write(fd, p->file2, ft_strlen(p->file2));
		write(fd, ": Is a directory\n", 17);
		close(fd);
		return (-1);
	}
	if (access(p->file2, F_OK) == -1)
	{
		fd = open(p->file2, O_RDWR | O_CREAT, 0644);
		return (fd);
	}
	if (access(p->file2, W_OK) == -1)
	{
		fd = open("temp-file2", O_RDWR | O_CREAT, 0644);
		write(fd, "bash: ", 6);
		write(fd, p->file2, ft_strlen(p->file2));
		write(fd, ": Permission denied\n", 20);
		close(fd);
		return (-1);
	}
	fd = open(p->file2, O_APPEND | O_RDWR);
	return (fd);
}

int	check_open_file(t_pipex *p, int flag)
{
	if (p->limiter)
	{
		if (flag == 1)
			return (heredoc_fd(p));
		else
			return (file_append(p));
	}
	if (flag == 1)
		return (first_command_file(p));
	return (last_command_file(p));
}
