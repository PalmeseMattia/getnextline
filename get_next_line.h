/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rizz <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 05:35:33 by rizz              #+#    #+#             */
/*   Updated: 2024/03/04 00:33:23 by rizz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>

typedef struct s_buffer
{
	char	content[BUFFER_SIZE];
	int		index;
}		t_buffer;
char	*ft_strrealloc(char *ptr, size_t size);
char	*get_next_line(int fd);
void	*ft_memset(void *ptr, int value, size_t n);
size_t	ft_strlen(const char *s);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memchr(const void *s, int c, size_t n);
int		populate_buffer(t_buffer buff, int fd);
void	*ft_calloc(size_t nmemb, size_t size);
void	ft_bzero(void *ptr, size_t n);

#endif
