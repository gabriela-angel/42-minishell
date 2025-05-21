/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gangel-a <gangel-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 17:30:39 by gangel-a          #+#    #+#             */
/*   Updated: 2025/05/20 23:13:27 by gangel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/include/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <errno.h>
# include <limits.h>
# include <dirent.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>

// MACROS ---------------
# define SUCCESS 0
# define FAILURE 1
# define SYNTAX_ERROR 2

// STRUCTS ----------------

typedef enum e_value_type
{
	TK_AND = 1,
	TK_OR,
	TK_PIPE,
	TK_OPEN_PARENTHESIS,
	TK_CLOSE_PARENTHESIS,
	TK_REDIR_OUT_APP,
	TK_REDIR_HDOC,
	TK_REDIR_IN,
	TK_REDIR_OUT,
	TK_WORD
}	t_value_type;

typedef struct s_token
{
	t_value_type	type;
	char			*value;
	struct s_token	*prev;
	struct s_token	*next;
}	t_token;

typedef struct s_tree
{
	t_token			*token;
	struct s_tree	*left;
	struct s_tree	*right;
}	t_tree;

typedef enum e_bool
{
	FALSE,
	TRUE
}	t_bool;

typedef struct s_malloc
{
	void			*ptr;
	struct s_malloc	*next;
}	t_malloc;

// BUILTINS -------------
t_bool	is_builtin(const char *cmd);
int		exec_builtin(char **args, char ***env, int last_status);
int		exec_echo(char **args);
int		exec_cd(char **args);
int		exec_pwd(char **args);
int		exec_env(char **args, char **env);
int		exec_export(char **args, char ***env);
int		exec_unset(char **args, char ***env);
int		exec_exit(char **args, int last_status);

// EXECUTOR -------------
int		minishell_exec(t_tree *ast, char ***env);
void	execute_tree(t_tree *node, char ***env);
void	exec_pipe_node(t_tree *node, char ***env);
void	exec_simple_command(t_token *token, char ***env);
int		exec_external(char **argv, char **envp);
int		apply_redirections(t_token *token);
int		handle_heredocs(t_token *token);
char	**convert_token_to_argv(t_token *token);

// EXPANSION -------------
char	*expand_var(char *str);
void	expand_tokens(t_tree *tree);
char	*remove_quotes(char *str);
void	handle_empty_value(t_token **current, t_tree **tree);
char	*ft_strchr_quote_aware(const char *s, int c);
void	retokenize(t_token **token);

// WILDCARD -------------
void	expand_wildcard(t_token **token, t_tree **tree);
void	alpha_sort_lst(t_token **head);
void	update_tk_lst(t_token **token, t_token *match_lst);
void	create_match_lst(t_token **head, char *data);

// HEREDOC -------------
int		handle_heredoc(t_token *token);
int		delete_heredoc(void);
int		*get_heredoc_counter(void);

// LEXER -------------
t_token	*get_token_list(char *input);
int		validate_input(char *input);

// PARSER -------------
t_tree	*get_tree(t_token *token_list);
int		validate_tokens(t_token *current);

// SIGNALS -------------
void	handle_sigint(int signum);
void	setup_signals_prompt(void);
void	setup_signals_child(void);
void	handle_heredoc_sigint(int sig);

// FT_MALLOC -----------------
void	*ft_malloc(size_t size);
void	ft_gc_free(void *ptr);
void	ft_gc_exit(void);
t_bool	ft_gc_add(void *ptr);

// UTILS -----------------
void	ft_free_split(char **split);
void	ft_sort_strs(char **arr);
int		ft_setenv(char *arg, char ***env);
int		handle_error(const char *msg);
int		exit_status(int set);

// TOKEN UTILS -------------
void	tk_lst_add_back(t_token **head, t_token *new_node);
t_token	*get_last_token(t_token *lst);
t_token	*ft_cutlist(t_token *start, t_token *end);
t_token	*search_token_rev(t_token *tk_lst, t_value_type start_type, \
	t_value_type end_type);
t_token	*search_token(t_token *tk_lst, t_value_type start_type, \
	t_value_type end_type);

#endif
