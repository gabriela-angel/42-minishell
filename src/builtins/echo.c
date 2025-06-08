/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gangel-a <gangel-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 14:31:26 by acesar-m          #+#    #+#             */
/*   Updated: 2025/06/08 19:53:01 by gangel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Função para verificar se uma string é uma flag -n válida.
 * Pode aceitar múltiplos 'n' após o primeiro.
 */
static t_bool	is_n_flag(char *str)
{
	int	i;

	if (!str || str[0] != '-' || str[1] != 'n')
		return (FALSE);
	i = 2;
	while (str[i])
	{
		if (str[i] != 'n')
			return (FALSE);
		i++;
	}
	return (TRUE);
}

/**
 * Implementação do built-in echo com suporte à flag -n.
 * Imprime os argumentos separados por espaço e, por padrão, com quebra de linha.
 * Se a flag -n for passada, suprime a quebra de linha.
 */
int	exec_echo(char **args)
{
	int		i;
	t_bool	newline;

	i = 1;
	newline = TRUE;
	while (args[i] && is_n_flag(args[i]))
	{
		newline = FALSE;
		i++;
	}
	while (args[i])
	{
		ft_printf_fd(1, "%s", args[i]);
		if (args[i + 1])
			ft_printf_fd(1, " ");
		i++;
	}
	if (newline)
		ft_printf_fd(1, "\n");
	return (0);
}
