#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <signal.h>
# include <dirent.h>
# include <sys/errno.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <sys/ioctl.h>
# include <stdio.h>
# include "../lib/libft/libft.h"

typedef struct s_token
{
	char			*path;
	char			**args;
	struct s_token	*next;
}				t_token;

typedef struct s_pipex
{
	t_token	*tokens;
	char	*file1;
	char	*file2;
	char	*limiter;
	int		i;
	int		nc;
	int		f1;
	int		f2;
}				t_pipex;

int		execute_pipes(t_pipex *p);
void	put_error_exit(char *str);
int		close_fd(int **fd, int n);
void	free_fd_pid_p(int **fd, int *pid, t_pipex *p);
int		exec_command(int **fd, t_token *token, t_pipex *p);
int		check_open_file(t_pipex *p, int flag);
int		last_command_file(t_pipex *p);
int		first_command_file(t_pipex *p);
char	*find_path(char *command, char **env);
int		close_fd(int **fd, int n);

#endif
