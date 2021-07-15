#include "pipex.h"

t_token	*put_to_tokens_list(t_token *tokens, t_token *new)
{
	t_token	*tmp;

	tmp = tokens;
	while (tmp)
	{
		if (tmp->next == NULL)
			break ;
		tmp = tmp->next;
	}
	if (tmp)
		tmp->next = new;
	else
		tokens = new;
	return (tokens);
}

t_token	*get_commands(int argc, char **argv, char **env, int flag)
{
	t_token	*tokens;
	t_token	*tmp;
	int		i;

	tokens = NULL;
	i = 1;
	if (flag == 1)
		i = 2;
	while (++i < argc - 1)
	{
		tmp = (t_token *)malloc(sizeof(t_token));
		tmp->args = ft_split(argv[i], ' ');
		tmp->path = find_path(tmp->args[0], env);
		tmp->next = NULL;
		tokens = put_to_tokens_list(tokens, tmp);
	}
	return (tokens);
}

void	put_error_exit(char *str)
{
	perror(str);
	exit (1);
}

int	main(int argc, char **argv, char **env)
{
	t_pipex	*p;

	if (argc < 5 || (ft_strcmp("here_doc", argv[1]) == 0 && argc < 6))
		put_error_exit("Invalid arguments");
	p = (t_pipex *)malloc(sizeof(t_pipex));
	if (!p)
		put_error_exit("malloc error");
	if (ft_strcmp("here_doc", argv[1]) == 0)
	{
		p->file1 = argv[1];
		p->file2 = argv[argc - 1];
		p->limiter = argv[2];
		p->tokens = get_commands(argc, argv, env, 1);
		p->nc = argc - 4;
		return (execute_pipes(p));
	}
	p->file1 = argv[1];
	p->file2 = argv[argc - 1];
	p->limiter = NULL;
	p->tokens = get_commands(argc, argv, env, 2);
	p->nc = argc - 3;
	return (execute_pipes(p));
}
