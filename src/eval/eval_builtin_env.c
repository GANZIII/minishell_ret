/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eval_builtin_env.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonghyk <seonghyk@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 00:56:37 by seonghyk          #+#    #+#             */
/*   Updated: 2022/12/05 18:13:07 by seonghyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "../minishell.h"
#include "../msh_utils/msh_utils.h"
#include "eval.h"
#include "libft.h"

void	msh_unsetenv(char *name)
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
			break ;
		}
	}
	while (g_shell_state.envp[i + 1] != NULL)
	{
		g_shell_state.envp[i] = g_shell_state.envp[i + 1];
		++i;
	}
	g_shell_state.envp[i] = NULL;
	free(temp);
}

pid_t	msh_builtin_unset(t_ast_node *node, t_context *ctx)
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
		msh_unsetenv(argv[i]);
	}
	free(argv);
	return (0);
}

pid_t	msh_builtin_env(t_ast_node *node, t_context *ctx)
{
	int			i;

	(void)ctx;
	(void)node;
	i = 0;
	while (g_shell_state.envp[++i] != NULL)
	{
		printf("%s\n", g_shell_state.envp[i]);
	}
	return (0);
}
