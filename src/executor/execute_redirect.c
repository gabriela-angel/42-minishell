/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_redirect.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesar-m <acesar-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 17:28:34 by acesar-m          #+#    #+#             */
/*   Updated: 2025/05/07 13:31:14 by acesar-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int save_and_restore_fds(int mode, int std_fd[2])
{
    if (mode == 0) // Salvar descritores
    {
        std_fd[0] = dup(STDIN_FILENO);
        std_fd[1] = dup(STDOUT_FILENO);
        if (std_fd[0] == -1 || std_fd[1] == -1)
            return (handle_error("dup"));
    }
    else if (mode == 1) // Restaurar descritores
    {
        if (dup2(std_fd[0], STDIN_FILENO) == -1 || dup2(std_fd[1], STDOUT_FILENO) == -1)
            return (handle_error("dup2"));
        close(std_fd[0]);
        close(std_fd[1]);
    }
    return (SUCCESS);
}

static void expand_variables(t_tk_list *tokens)
{
    t_tk_list *current;
    char *expanded_value;

    current = tokens;
    while (current)
    {
        if (ft_strchr(current->token.value, '$')) // Verifica se há variáveis para expandir
        {
            expanded_value = getenv(current->token.value + 1); // Obtém o valor da variável de ambiente
            if (expanded_value)
                current->token.value = ft_strdup(expanded_value); // Substitui pelo valor expandido
            else
                current->token.value = ft_strdup(""); // Substitui por string vazia se a variável não existir
        }
        current = current->next;
    }
}

static int handle_redirection(t_tree *right, int redir_type, int *fd)
{
    if (redir_type == TK_REDIR_OUT_APP)
        *fd = open(right->command->token.value, O_CREAT | O_APPEND | O_WRONLY, 0644);
    else if (redir_type == TK_REDIR_HDOC || redir_type == TK_REDIR_IN)
        *fd = open(right->command->token.value, O_RDONLY, 0644);
    else if (redir_type == TK_REDIR_OUT)
        *fd = open(right->command->token.value, O_CREAT | O_TRUNC | O_WRONLY, 0644);
    if (*fd == -1)
        return (handle_error(right->command->token.value));
    if ((redir_type == TK_REDIR_OUT_APP || redir_type == TK_REDIR_OUT) &&
        dup2(*fd, STDOUT_FILENO) == -1)
        return (handle_error("dup2"));
    if ((redir_type == TK_REDIR_HDOC || redir_type == TK_REDIR_IN) &&
        dup2(*fd, STDIN_FILENO) == -1)
        return (handle_error("dup2"));
    close(*fd);
    return (SUCCESS);
}

int execute_redirect(t_tree *left, t_tree *right, int redir_type)
{
    int fd;
    int std_fd[2];
    int exit_status;
    char *before_expansion;

    if (save_and_restore_fds(0, std_fd) != SUCCESS)
        return (FAILURE);
    before_expansion = right->command->token.value;
    expand_variables(right->command);
    if ((*before_expansion != '\0' && !right->command) || right->command->next)
    {
        ft_printf_fd(STDERR_FILENO, "%s: ambiguous redirect\n", before_expansion);
        return (FAILURE);
    }
    if (handle_redirection(right, redir_type, &fd) != SUCCESS)
        return (FAILURE);
    exit_status = left->command ? executor(left) : SUCCESS;
    if (save_and_restore_fds(1, std_fd) != SUCCESS)
        return (FAILURE);
    return (exit_status);
}

int dup2_redir_file(int redir_type, int *fd)
{
	int exit_status;

	exit_status = -1;
	if (redir_type == TK_REDIR_OUT_APP || redir_type == TK_REDIR_OUT)
		exit_status = dup2(*fd, STDOUT_FILENO);
	else if (redir_type == TK_REDIR_HDOC || redir_type == TK_REDIR_IN)
		exit_status = dup2(*fd, STDIN_FILENO);
	if (exit_status == -1)
		return (handle_error("dup2"));
	close(*fd);
	return (SUCCESS);
}
