/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rizz <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 09:59:01 by rizz              #+#    #+#             */
/*   Updated: 2024/03/04 18:52:08 by rizz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static t_buffer buff = {.index = 0, .bytes_read = 1};
	int				line_size;
	char			*res;

	res = NULL;
	line_size = 0;
	while(1)
	{
		read_line(fd, &buff);
		if (buff.bytes_read <= 0 || buff.content[buff.index] == '\0')
		{
            break ;
			//return (NULL);
			//free(res);
		}
		line_size = find_line_size(buff);
		res = ft_strrealloc(res, ft_strlen(res) + line_size + 1);
		ft_memcpy(res + ft_strlen(res), buff.content + buff.index, line_size);
		buff.index+=line_size;
		if (ft_memchr(res,'\n', ft_strlen(res)))
			return (res);
	}
    if (res && *res)
        return res;
    free(res);
    return NULL;
}

void read_line(int fd, t_buffer *buff)
{
	if ((buff->index == 0 || buff->index >= BUFFER_SIZE))
	{
		buff->bytes_read = (read(fd, buff->content, BUFFER_SIZE));
		buff->index = 0;
	}
}

int find_line_size(t_buffer buff)
{
    int size;

	size = 1;
	while (buff.index < BUFFER_SIZE && buff.content[buff.index] != '\n' && buff.content[buff.index] != EOF && buff.content[buff.index] != '\0')
	{
		buff.index++;
		size++;
	}
	if (buff.content[buff.index] == '\n')
		return (size);
	return (size);
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

