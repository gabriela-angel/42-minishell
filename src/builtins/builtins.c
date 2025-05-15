/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesar-m <acesar-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 13:46:39 by acesar-m          #+#    #+#             */
/*   Updated: 2025/05/14 18:30:14 by acesar-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

t_bool	is_builtin(t_token *tokens)
{
	if (!ft_strcmp(tokens->value, "cd") || !ft_strcmp(tokens->value, "echo")
		|| !ft_strcmp(tokens->value, "env") || !ft_strcmp(tokens->value, "exit")
		|| !ft_strcmp(tokens->value, "export") || !ft_strcmp(tokens->value,
			"pwd") || !ft_strcmp(tokens->value, "unset"))
		return (TRUE);
	return (FALSE);
}

int	exec_builtin(t_token *tokens, char ***env, int last_status)
{
	char	**args;

	args = convert_token_to_argv(tokens);
	if (!args)
		return (1);
	if (!ft_strcmp(tokens->value, "cd"))
		return (exec_cd(args));
	if (!ft_strcmp(tokens->value, "echo"))
		return (exec_echo(args));
	if (!ft_strcmp(tokens->value, "env"))
		return (exec_env(args, *env));
	if (!ft_strcmp(tokens->value, "exit"))
		return (exec_exit(args, last_status));
	if (!ft_strcmp(tokens->value, "export"))
		return (exec_export(args, env));
	if (!ft_strcmp(tokens->value, "pwd"))
		return (exec_pwd(args));
	if (!ft_strcmp(tokens->value, "unset"))
		return (exec_unset(args, env));
	ft_free_split(args);
	return (handle_error("error executing builtin"));
}
