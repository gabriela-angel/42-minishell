/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gangel-a <gangel-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 15:40:30 by gangel-a          #+#    #+#             */
/*   Updated: 2025/03/15 21:44:32 by gangel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 20
# endif

# include <stdlib.h>
# include <unistd.h>

char	*get_next_line(int fd);

size_t	gnl_ft_strlen(const char *s);
int		gnl_ft_strchr(const char *s, int c);
char	*gnl_ft_strjoin(char *s1, char const *s2);
char	*gnl_ft_substr(char const *s, unsigned int start, size_t len);

#endif