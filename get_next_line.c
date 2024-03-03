/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rizz <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 09:59:01 by rizz              #+#    #+#             */
/*   Updated: 2024/03/03 05:44:19 by rizz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static t_buffer		b = {.index = 0};
	int					bytes_read;
	char				*line;
	char				*newline;
	size_t				line_length;

	line = NULL;
	while (1)
	{
		bytes_read = populate_buffer(b, fd);
		if (bytes_read <= 0 && b.index >= BUFFER_SIZE)
			return (NULL);
		newline = ft_memchr(b.content + b.index, '\n', BUFFER_SIZE - b.index);
		if (newline)
		{
			line_length = newline - (b.content + b.index);
			line = ft_strrealloc(line, ft_strlen(line) + line_length + 1);
			ft_memcpy(line, (b.content + b.index), line_length);
			b.index += line_length + 1;
			return (line);
		}
		line = ft_strrealloc(line, ft_strlen(line) + (BUFFER_SIZE - b.index) + 1);
		ft_memcpy(line + ft_strlen(line), (b.content + b.index), (BUFFER_SIZE - b.index));
		b.index = 0;
	}
}

int	populate_buffer(t_buffer buff, int fd)
{
	int	bytes_read;

	bytes_read = 0;
	if (buff.index == 0 || buff.index > BUFFER_SIZE)
	{
		bytes_read = read(fd, buff.content, BUFFER_SIZE);
		buff.index = 0;
	}
	return (bytes_read);
}

char	*ft_strrealloc(char *ptr, size_t size)
{
	char	*new_ptr;

	if (size == 0)
	{
		free(ptr);
		return (NULL);
	}
	else if (ptr == NULL)
		return (ft_calloc(size, sizeof(char)));
	new_ptr = ft_calloc(size, sizeof(char));
	if (new_ptr)
	{
		ft_memcpy(new_ptr, ptr, ft_strlen(ptr));
		free(ptr);
		return (new_ptr);
	}
	return (NULL);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*p;
	size_t	bytes;

	if (nmemb == 0 || size == 0)
	{
		nmemb = 1;
		size = 1;
	}
	bytes = nmemb * size;
	if (bytes / size != nmemb)
		return (NULL);
	p = malloc(bytes);
	if (!p)
		return (NULL);
	ft_bzero(p, bytes);
	return (p);
}

void	ft_bzero(void *ptr, size_t n)
{
	ft_memset(ptr, 0, n);
}
