/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gangel-a <gangel-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 19:48:33 by gangel-a          #+#    #+#             */
/*   Updated: 2025/04/24 19:48:33 by gangel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

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
