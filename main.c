/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpalmese <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 10:51:04 by dpalmese          #+#    #+#             */
/*   Updated: 2024/02/25 17:57:51 by dpalmese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include "libft/libft.h"

#define BUFFER_SIZE 1

char			*get_next_line(int fd);

typedef struct	s_buffer
{
    char	content[BUFFER_SIZE];
	int		index;
}	t_buffer;

int	main(int argc, char **argv)
{
	if (argc < 2) {
		fprintf(stderr, "You must pass a filename!\n");
		return (-1);
	}
	char *filename = argv[1];
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
	return (0);
}

char	*get_next_line(int fd)
{
	static t_buffer	buff = {.index = 0};
	char			*result;
	char			*newline;
	int				n;
	char			*start;
	
	result = NULL;
	start = buff.content + buff.index;
	if (start == 0)
	{
		n = read(fd, buff.content, BUFFER_SIZE);
		if (n <= 0)
			return (NULL);	
	}
	newline = ft_memchr(start, '\n', BUFFER_SIZE - buff.index);
	while(newline == NULL) {
		n = read(fd, buff.content, BUFFER_SIZE);
		if (n <= 0)
			return (NULL);
		start = buff.content + buff.index;
		result = ft_strrealloc(result, (ft_strlen(result) + BUFFER_SIZE - buff.index) + 1);
		ft_memcpy(result + ft_strlen(result), start, BUFFER_SIZE - buff.index);
		newline = ft_memchr(buff.content, '\n', n);
		buff.index = 0;
	}
	result = ft_strrealloc(result, (ft_strlen(result) + (newline - start)) + 1);
	ft_memcpy(result + ft_strlen(result), start, newline - start);
	buff.index = newline - buff.content;
	return (result);
}
