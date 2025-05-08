/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesar-m <acesar-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 11:12:33 by acesar-m          #+#    #+#             */
/*   Updated: 2025/05/06 11:12:34 by acesar-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isoperator(int c)
{
	if (c == '|' || c == '&' || c == '<' || c == '>' || c == '(' || c == ')')
		return (1);
	return (0);
}

int	ft_isredirector(t_token token)
{
	if (token.type == TK_REDIR_IN || token.type == TK_REDIR_OUT || token.type == TK_REDIR_OUT_APP || token.type == TK_REDIR_HDOC)
		return (1);
	return (0);
}