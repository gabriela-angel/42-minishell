/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesar-m <acesar-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 17:30:39 by gangel-a          #+#    #+#             */
/*   Updated: 2025/05/15 16:26:29 by acesar-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/include/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>

// MACROS ---------------
# define SUCCESS 0
# define ERROR 1

// ERROR MACROS -----------
extern int	g_exit_status;

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
}						t_value_type;

typedef struct s_token
{
	t_value_type		type;
	char				*value;
	struct s_token	*prev;
	struct s_token	*next;
}						t_token;

typedef struct s_tree
{
	t_token		*token;
	struct s_tree	*left;
	struct s_tree	*right;
}						t_tree;


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

// FT_MALLOC -----------------
void		*ft_malloc(size_t size);
void		ft_gc_free(void *ptr);
void		ft_gc_exit(void);
t_bool		ft_gc_add(void *ptr);

// UTILS
int		ft_setenv(char *arg, char ***env);
void	ft_sort_strs(char **arr);
void	ft_free_split(char **split);
void	tk_lst_add_back(t_token **head, t_token *new_node);
t_token	*get_last_token(t_token *lst);
t_token	*ft_cutlist(t_token *start, t_token *end);
t_token	*search_token_rev(t_token *token_list, t_value_type start_type, t_value_type end_type);
t_token	*search_token(t_token *token_list, t_value_type start_type, t_value_type end_type);
int		handle_error(const char *msg);

// EXECUTOR
int		minishell_exec(t_tree *ast, char ***env);
void	execute_tree(t_tree *node, char ***env);
void	exec_simple_command(t_token *token, char ***env);
int		exec_external(char **argv, char **envp);
int		apply_redirections(t_token *token);
int		handle_heredocs(t_token *token);
char	**convert_token_to_argv(t_token *token);

// BUILTINS
t_bool	is_builtin(const char *cmd);
int		exec_builtin(char **args, char ***env, int last_status);
int		exec_echo(char **args);
int		exec_cd(char **args);
int		exec_pwd(char **args);
int		exec_env(char **args, char **env);
int		exec_export(char **args, char ***env);
int		exec_unset(char **args, char ***env);
int		exec_exit(char **args, int last_status);

// LEXER
t_token	*get_token_list(char *input);
int		validate_input(char *input);

// PARSER
int		validate_tokens(t_token *current);
t_tree	*get_tree(t_token *token_list);

// SIGNALS
void	handle_sigint(int signum);
void	setup_signals_prompt(void);
void	setup_signals_child(void);
void	handle_heredoc_sigint(int sig);

#endif