/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpalmese <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 10:51:04 by dpalmese          #+#    #+#             */
/*   Updated: 2024/02/27 11:14:55 by rizz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include "libft/libft.h"

#define BUFFER_SIZE 1024

char	*get_next_line(int fd);
char	*ft_strrealloc(char *ptr, size_t size);

typedef struct	s_buffer
{
    char	content[BUFFER_SIZE];
	int		index;
}	t_buffer;

int	main(int argc, char **argv)
{
	char *filename = "bible.txt";
	int fd = open(filename, O_RDONLY);
	if (fd < 0) {
		perror("Error while opening the file");
		return (-1);
	}
	char *line = get_next_line(fd);
	while(line != NULL) {
		printf("%s\n", line);
		line = get_next_line(fd);
	}
	free(line);
	return (0);
}

char	*get_next_line(int fd)
{
	static t_buffer	buff= {.index = 0};
	int				bytes_read;
	char			*line;
	char			*newline;
	size_t			line_length;

	line = NULL;
	while (1)
	{
		if (buff.index == 0 || buff.index > BUFFER_SIZE)
		{
			bytes_read = read(fd, buff.content, BUFFER_SIZE);
			buff.index = 0;
		}
		if (bytes_read <= 0)
			return (NULL);
		newline = ft_memchr(buff.content + buff.index, '\n', BUFFER_SIZE - buff.index);
		if (newline)
		{
			line_length = newline - (buff.content + buff.index);
			line = realloc(line, ft_strlen(line) + line_length + 1);
			ft_memcpy(line, (buff.content + buff.index), line_length);
			buff.index += line_length + 1;
			return (line);
		}
		else
		{
			line = realloc(line, ft_strlen(line) + (BUFFER_SIZE - buff.index) + 1);
			ft_memcpy(line + ft_strlen(line), (buff.content + buff.index), (BUFFER_SIZE - buff.index));
			buff.index = 0;
		}
	}
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
