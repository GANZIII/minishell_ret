/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eval_builtin_export.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonghyk <seonghyk@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 18:12:58 by seonghyk          #+#    #+#             */
/*   Updated: 2022/12/05 18:13:00 by seonghyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "../minishell.h"
#include "../msh_utils/msh_utils.h"
#include "eval.h"
#include "libft.h"

void	get_args_from_cmd_suffix(t_ast_node *node, char ***argv, int idx)
{
	t_token		*token;
	t_ast_node	*next;

	if (node == NULL)
	{
		*argv = (char **)malloc(sizeof(char *) * (idx + 2));
		(*argv)[idx] = NULL;
		(*argv)[idx + 1] = NULL;
		return ;
	}
	next = node->data.cmd_suffix.child;
	token = node->data.cmd_suffix.token;
	if (token->type == TOKEN_WORD)
	{
		get_args_from_cmd_suffix(next, argv, idx + 1);
		(*argv)[idx] = token->str;
	}
	else
	{
		get_args_from_cmd_suffix(next, argv, idx);
	}
}

void	msh_env_append(char	*string)
{
	int		i;
	char	**new_envp;

	i = -1;
	while (g_shell_state.envp[++i] != NULL)
		;
	new_envp = malloc(sizeof(char *) * (i + 1));
	i = -1;
	while (g_shell_state.envp[++i] != NULL)
		new_envp[i] = g_shell_state.envp[i];
	new_envp[i] = string;
	new_envp[++i] = NULL;
	free(g_shell_state.envp);
	g_shell_state.envp = new_envp;
}

void	msh_setenv(const char *name, const char *value)
{
	int		i;
	char	*temp;

	i = -1;
	temp = ft_strjoin(name, "=");
	while (g_shell_state.envp[++i] != NULL)
	{
		if (str_start_with(g_shell_state.envp[i], temp))
		{
			free(g_shell_state.envp[i]);
			g_shell_state.envp[i] = ft_strjoin(temp, value);
			break ;
		}
	}
	if (g_shell_state.envp[i] == NULL)
	{
		msh_env_append(ft_strjoin(temp, value));
	}
	free(temp);
}

void	msh_putenv(const char *string)
{
	char	*p_first_occurrence_of_equal;

	p_first_occurrence_of_equal = ft_strchr(string, '=');
	if (p_first_occurrence_of_equal == NULL)
		return ;
	else
	{
		*p_first_occurrence_of_equal = '\0';
		msh_setenv(string, p_first_occurrence_of_equal + 1);
		*p_first_occurrence_of_equal = '=';
	}
}

pid_t	msh_builtin_export(t_ast_node *node, t_context *ctx)
{
	t_ast_node	*pair;
	char		**argv;
	int			i;

	(void)ctx;
	pair = node->data.simple_command.child;
	get_args_from_cmd_suffix(pair->data.pair.right, &argv, 1);
	i = 0;
	while (argv[++i] != NULL)
	{
		msh_putenv(argv[i]);
	}
	free(argv);
	return (0);
}
