#include "pipex.h"

char	*get_pwd(char **env)
{
	char	*pwd;
	char	**tmp;
	int		i;

	i = -1;
	while (env[++i])
	{
		tmp = ft_split(env[i], '=');
		if (!ft_strcmp(tmp[0], "PWD"))
			break ;
		free_array(tmp);
	}
	pwd = ft_strdup(tmp[1]);
	free_array(tmp);
	return (pwd);
}

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
