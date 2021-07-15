#include "pipex.h"

void	free_array(char **array)
{
	int		i;
	char	**tmp;

	i = -1;
	tmp = array;
	while (tmp[++i])
		free(tmp[i]);
	free(array);
}

char	**get_path_value(char **env)
{
	char	**path_value;
	char	**tmp;
	int		i;

	i = -1;
	while (env[++i])
	{
		tmp = ft_split(env[i], '=');
		if (!ft_strcmp(tmp[0], "PATH"))
			break ;
		free_array(tmp);
	}
	path_value = ft_split(tmp[1], ':');
	free_array(tmp);
	return (path_value);
}

char	*check_local_path(char *path, char *command)
{
	path = ft_strjoin("./", command);
	if (access(path, F_OK))
	{
		free(path);
		path = ft_strdup(command);
	}
	return (path);
}

char	*get_path(char **pv, char *command)
{
	int		i;
	char	*tmp;
	char	*path;

	path = NULL;
	i = -1;
	while (pv[++i])
	{
		tmp = ft_strjoin(pv[i], "/");
		path = ft_strjoin(tmp, command);
		free(tmp);
		if (!access(path, F_OK))
			break ;
		free(path);
		path = NULL;
	}
	if (path == NULL)
		path = check_local_path(path, command);
	return (path);
}

char	*find_path(char *command, char **env)
{
	char	*path;
	char	**path_value;

	path_value = get_path_value(env);
	path = get_path(path_value, command);
	free_array(path_value);
	return (path);
}
