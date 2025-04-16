/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isoperator.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gangel-a <gangel-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 21:53:37 by gangel-a          #+#    #+#             */
/*   Updated: 2025/04/15 21:53:37 by gangel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isoperator(int c)
{
	if (c == '|' || c == '&' || c == '<' || c == '>' || c == '(' || c == ')')
		return (1);
	return (0);
}

typedef enum e_state
{
	S_ERROR = -1,
	S_START,
	S_PIPE,
	S_AND,
	S_REDIR_IN,
	S_REDIR_OUT,
	S_WORD,
	S_SINGLE_QOUTE,
	S_QUOTE,
	E_OR,
	E_AND,
	E_REDIR_HDOC,
	E_REDIR_OUT_APP,
	E_WORD,
	E_PIPE,
	E_REDIR_IN,
	E_REDIR_OUT,
	E_OPEN_PARENTHESIS,
	E_CLOSE_PARENTHESIS,
}