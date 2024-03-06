#include <stdio.h>
#include "get_next_line.h"

char	*get_next_line(int fd);
void	read_line(int fd, t_buffer *buff);
int		find_line_size(t_buffer buff);

int main() {
	char *line;

	int fd = open("bible.txt", O_RDONLY);
	if (fd < 0) {
		perror("Error while opening file");
		return (-1);
	}
	while((line = get_next_line(fd)) != NULL)
	{
		printf("riga: ");
		printf("%s", line);
	}
	close(fd);
	return (0);
}

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
			return (NULL);
		line_size = find_line_size(buff);
		res = ft_strrealloc(res, ft_strlen(res) + line_size + 1);
		ft_memcpy(res + ft_strlen(res), buff.content + buff.index, line_size);
		buff.index+=line_size;
		if (ft_memchr(res,'\n', ft_strlen(res)))
			return (res);
	}
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

	size = 0;
	while (buff.index < BUFFER_SIZE && buff.content[buff.index] != '\n' && buff.content[buff.index] != EOF)
	{
		buff.index++;
		size++;
	}
	if (buff.content[buff.index] == '\n')
		return (size + 1);
	return (size);
}
