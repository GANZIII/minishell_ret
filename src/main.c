/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jijoo <jijoo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 17:33:24 by seonghyk          #+#    #+#             */
/*   Updated: 2022/12/05 20:05:12 by jijoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "eval/eval.h"

//struct s_shell_state	g_shell_state;

int	skip(char *line)
{
	int	idx;

	idx = 0;
	if (!line)
		exit(0);
	add_history(line);
	while (line[idx])
	{
		if ((line[idx] >= 9) && (line[idx] <= 13))
		{
			idx++;
			continue ;
		}
		else if (line[idx] == ' ')
		{
			idx++;
			continue ;
		}
		else
			return (0);
	}
	return (1);
}

void	nop(void)
{
	return ;
}

void	init_msh(int argc, char *argv[], char *envp[])
{
	int	envp_len;

	(void)argc;
	(void)argv;
	envp_len = -1;
	while (envp[++envp_len] != NULL)
		;
	g_shell_state.envp = (char **)malloc(sizeof(char *) * (envp_len + 1));
	envp_len = -1;
	while (envp[++envp_len] != NULL)
		g_shell_state.envp[envp_len] = ft_strdup(envp[envp_len]);
	g_shell_state.envp[envp_len] = NULL;
	g_shell_state.orig_stdin = dup(STDIN_FILENO);
	g_shell_state.exit_status = 0;
	signaling();
}

void	node_null(t_ast_node *node)
{
	eval(node);
	ast_free(node);
}

int	main(int argc, char *argv[], char *envp[])
{
	char			*line;
	t_token			*token_lst;
	t_ast_node		*node;

	init_msh(argc, argv, envp);
	while ((argv[0]) && (argc))
	{
		line = readline("minishell$ ");
		if (!skip(line))
		{
			if (quote_open(line))
			{
				quote_err(line);
				continue ;
			}
			tokenize(line, &token_lst, g_shell_state.envp);
			node = parse_program(token_lst);
			if (node != NULL)
				node_null(node);
			ft_lstfree(&token_lst);
		}
		free(line);
	}
	return (0);
}
