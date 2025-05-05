/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gangel-a <gangel-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 18:04:33 by gangel-a          #+#    #+#             */
/*   Updated: 2025/04/15 18:04:33 by gangel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "minishell.h"

// ERROR MACROS -----------
# define QUOTE_ERROR "minishell: unclosed quote: `%c'\n"

// STRUCTS ----------------

typedef enum e_value_type
{
	TK_INVALID,
	TK_OR = 8,
	TK_AND,
	TK_REDIR_HDOC,
	TK_REDIR_OUT_APP,
	TK_WORD,
	TK_PIPE,
	TK_REDIR_IN,
	TK_REDIR_OUT,
	TK_OPEN_PARENTHESIS,
	TK_CLOSE_PARENTHESIS
}						t_value_type;

typedef struct s_value_part
{
	char				*str;
	char				quote;
}						t_value_part;

typedef struct s_data
{
	t_value_part		*parts;
	size_t				item_no;
	t_bool				error;
}						t_data;

typedef struct s_token
{
	t_value_type		type;
	struct s_token		*file;
	char				*value;
	t_data				data;
}						t_token;

typedef struct s_tk_list
{
	t_token				token;
	struct s_tk_list	*prev;
	struct s_tk_list	*next;
}						t_tk_list;

// FUNCTIONS -----------------
t_tk_list	*get_token_list(char *input);
char		*handle_word(char *input, t_token *token);

// UTILS ------------------
int			ft_isoperator(int c);
int			ft_isredirector(t_token token);

#endif