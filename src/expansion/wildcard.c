/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gangel-a <gangel-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 18:30:02 by gangel-a          #+#    #+#             */
/*   Updated: 2025/05/17 18:30:02 by gangel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_bool	match_and_free(t_bool **match, int str_len, int pat_len)
{
	t_bool	match_found;
	int		i;

	i = 0;
	match_found = match[str_len][pat_len];
	while (i <= str_len)
	{
		free(match[i]);
		i++;
	}
	free(match);
	return (match_found);
}

static t_bool	**init_match_table(char *str, int *str_len, \
	char *pattern, int *pat_len)
{
	int		row_str;
	int		col_pat;
	t_bool	**match;

	*str_len = ft_strlen(str);
	*pat_len = ft_strlen(pattern);
	match = (t_bool **)ft_calloc((*str_len + 1), sizeof(t_bool *));
	row_str = 0;
	while (row_str <= *str_len)
	{
		match[row_str] = (t_bool *)ft_calloc((*pat_len + 1), sizeof(t_bool));
		row_str++;
	}
	match[0][0] = TRUE;
	col_pat = 1;
	while (col_pat <= *pat_len)
	{
		if (pattern[col_pat - 1] == '*')
			match[0][col_pat] = match[0][col_pat - 1];
		col_pat++;
	}
	return (match);
}

static t_bool	is_match(char *str, char *pattern)
{
	int		row_str;
	int		col_pat;
	int		str_len;
	int		pat_len;
	t_bool	**match;

	match = init_match_table(str, &str_len, pattern, &pat_len);
	row_str = 1;
	while (row_str <= str_len)
	{
		col_pat = 1;
		while (col_pat <= pat_len)
		{
			if (pattern[col_pat - 1] == '*')
				match[row_str][col_pat] = match[row_str][col_pat - 1];
			else if (str[row_str - 1] == pattern[col_pat - 1])
				match[row_str][col_pat] = match[row_str - 1][col_pat - 1];
			col_pat++;
		}
		row_str++;
	}
	return (match_and_free(match, str_len, pat_len));
}

static void	adjust_tk_list(t_token **token, t_tree **tree, t_token *match_lst)
{
	if ((*token)->prev == NULL)
	{
		if ((*tree)->token->type >= TK_REDIR_OUT_APP
			&& (*tree)->token->type <= TK_REDIR_OUT)
			(*tree)->token->next = match_lst;
		else
			(*tree)->token = match_lst;
	}
}

void	expand_wildcard(t_token **token, t_tree **tree)
{
	DIR				*dir;
	struct dirent	*entry;
	t_token			*match_lst;

	dir = opendir(".");
	if (!dir)
		return ;
	entry = readdir(dir);
	match_lst = NULL;
	while (entry)
	{
		if (*(entry->d_name) != '.' && is_match(entry->d_name, (*token)->value))
			create_match_lst(&match_lst, entry->d_name);
		entry = readdir(dir);
	}
	closedir(dir);
	if (!match_lst)
		return ;
	adjust_tk_list(token, tree, match_lst);
	alpha_sort_lst(&match_lst);
	update_tk_lst(token, match_lst);
}
