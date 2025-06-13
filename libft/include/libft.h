/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gangel-a <gangel-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 12:05:54 by gangel-a          #+#    #+#             */
/*   Updated: 2025/06/13 17:39:15 by gangel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>

# include "../get_next_line/include/get_next_line.h"

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}		t_list;

long			ft_atoi(const char *nptr);
void			ft_bzero(void *s, size_t n);
void			*ft_calloc(size_t nmemb, size_t size);
void			ft_free_matrix(char **matrix);
unsigned int	ft_htoi(char *hex);
char			*ft_itoa(int n);
int				ft_isalnum(int c);
int				ft_isalpha(int c);
int				ft_isascii(int c);
int				ft_isdigit(int c);
int				ft_isprint(int c);
int				ft_isspace(int c);
void			*ft_memchr(const void *s, int c, size_t n);
int				ft_memcmp(const void *s1, const void *s2, size_t n);
void			*ft_memcpy(void *dest, const void *src, size_t n);
void			*ft_memmove(void *dest, const void *src, size_t n);
void			*ft_memset(void *s, int c, size_t n);
int				ft_num_abs(int nb);
int				ft_printf_fd(const int fd, const char *str, ...);
int				ft_putbase_fd(long nb, char *base, int fd);
int				ft_putchar_fd(char c, int fd);
void			ft_putendl_fd(char *s, int fd);
int				ft_putnbr_fd(int n, int fd);
int				ft_putptr_fd(unsigned long nbr, int fd);
int				ft_putstr_fd(char *s, int fd);
void			*ft_recalloc(void *ptr, size_t new_size, size_t old_size);
char			**ft_split(char const *s, char c);
char			*ft_strchr(const char *s, int c);
int				ft_strcmp(const char *s1, const char *s2);
char			*ft_strdup(const char *s);
void			ft_striteri(char *s, void (*f)(unsigned int, char*));
char			*ft_strjoin(char *s1, char *s2);
char			*ft_strjoin_free(char *s1, char *s2);
size_t			ft_strlcat(char *dst, const char *src, size_t size);
size_t			ft_strlcpy(char *dst, const char *src, size_t size);
size_t			ft_strlen(const char *s);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
char			**ft_strdup_split(char **envp);
char			*ft_strnstr(const char *big, const char *little, size_t len);
char			*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char			*ft_strrchr(const char *s, int c);
int				ft_strtoll_check(const char *nptr, long long *out);
char			*ft_strtrim(char const *s1, char const *set);
char			*ft_substr(char const *s, unsigned int start, size_t len);
int				ft_tolower(int c);
int				ft_toupper(int c);
t_list			*ft_lstnew(void *content);
void			ft_lstadd_front(t_list **lst, t_list *new);
int				ft_lstsize(t_list *lst);
t_list			*ft_lstlast(t_list *lst);
void			ft_lstadd_back(t_list **lst, t_list *new);
void			ft_lstdelone(t_list *lst, void (*del)(void *));
void			ft_lstclear(t_list **lst, void (*del)(void *));
void			ft_lstiter(t_list *lst, void (*f)(void *));
t_list			*ft_lstmap(t_list *lst, void *(*f)(void *),
					void (*del)(void *));

// PRINTF
int				ft_printf(const char *format, ...);
int				ft_printchar(int c);
int				ft_printhex(unsigned long n, char c);
int				ft_printnbr(int n);
int				ft_printunbr(unsigned int n);
int				ft_printptr(unsigned long ptr);
int				ft_printstr(char *s);

#endif
