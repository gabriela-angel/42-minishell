/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesar-m <acesar-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 17:05:43 by acesar-m          #+#    #+#             */
/*   Updated: 2025/05/08 11:16:05 by acesar-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	is_builtin(t_tk_list *tokens)
{
	if (!tokens || !tokens->token.value)
		return (FALSE);
	if (!ft_strcmp(tokens->token.value, "cd") || !ft_strcmp(tokens->token.value, "echo")
		|| !ft_strcmp(tokens->token.value, "env") || !ft_strcmp(tokens->token.value, "exit")
		|| !ft_strcmp(tokens->token.value, "export") || !ft_strcmp(tokens->token.value,
			"pwd") || !ft_strcmp(tokens->token.value, "unset"))
		return (TRUE);
	return (FALSE);
}

int execute_builtin(t_tree *command_tree)
{
    if (!command_tree || !command_tree->command || !command_tree->command->token.value)
        return (handle_error("invalid command tree"));
    if (!ft_strcmp(command_tree->command->token.value, "cd"))
        return (execute_cd(command_tree));
    if (!ft_strcmp(command_tree->command->token.value, "echo"))
        return (execute_echo(command_tree));
    if (!ft_strcmp(command_tree->command->token.value, "env"))
        return (execute_env(command_tree));
    if (!ft_strcmp(command_tree->command->token.value, "exit"))
        return (execute_exit(command_tree));
    if (!ft_strcmp(command_tree->command->token.value, "export"))
        return (execute_export(command_tree));
    if (!ft_strcmp(command_tree->command->token.value, "unset"))
        return (execute_unset(command_tree));
    return (handle_error("error executing builtin"));
}
