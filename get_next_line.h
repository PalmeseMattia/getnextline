#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <unistd.h>
# include <fcntl.h>
# define BUFFER_SIZE 1024
typedef struct	s_buffer
{
    char	content[BUFFER_SIZE];
	int		index;
}		t_buffer;
char	*ft_strrealloc(char *ptr, size_t size);
char	*get_next_line(int fd);
#endif
