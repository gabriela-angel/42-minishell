/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_argv_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gangel-a <gangel-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 17:26:34 by acesar-m          #+#    #+#             */
/*   Updated: 2025/06/23 19:47:18 by gangel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

static int	count_words(t_token *token)
{
	int	count;

	count = 0;
	while (token)
	{
		if (token->type == TK_WORD && token->value
			&& token->value[0] != '\0')
			count++;
		if (token->type >= TK_REDIR_OUT_APP && token->type <= TK_REDIR_OUT)
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
		if (token->type == TK_WORD && token->value
			&& token->value[0] != '\0')
		{
			argv[i++] = ft_strdup(token->value);
			ft_gc_add(argv[i - 1]);
		}
		if (token->type >= TK_REDIR_OUT_APP && token->type <= TK_REDIR_OUT)
			token = token->next;
		token = token->next;
	}
	argv[i] = NULL;
	return (argv);
}
