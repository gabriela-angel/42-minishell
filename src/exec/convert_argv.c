/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_argv.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gangel-a <gangel-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 17:26:34 by acesar-m          #+#    #+#             */
/*   Updated: 2025/05/20 22:41:11 by gangel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_words(t_token *token)
{
	int	count;

	count = 0;
	while (token)
	{
		if (token->type == TK_WORD)
			count++;
		if (token->type >= TK_REDIR_OUT && token->type <= TK_REDIR_HDOC)
			token = token->next;
		token = token->next;
	}
	return (count);
}

char	**convert_token_to_argv(t_token *token)
{
	int		i;
	int		size;
	char	**argv;

	size = count_words(token);
	argv = (char **)ft_malloc(sizeof(char *) * (size + 1));
	if (!argv)
		return (NULL);
	i = 0;
	while (token)
	{
		if (token->type == TK_WORD)
			argv[i++] = ft_strdup(token->value);
		if (token->type >= TK_REDIR_OUT && token->type <= TK_REDIR_HDOC)
			token = token->next;
		token = token->next;
	}
	argv[i] = NULL;
	return (argv);
}
