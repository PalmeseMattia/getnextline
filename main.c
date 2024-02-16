#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

#define BUFFER_SIZE 16

char *get_next_line(int fd);
int static_test(int x);

int main(int argc, char **argv)
{
	int fd = open(argv[1], O_RDONLY);
	if (!fd)
		return 1;
	printf("%s\n", get_next_line(fd));
}


int static_test(int x)
{
	static int a = 0;
	return a += 5;
} 

char *get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE * 4];
	read(fd, buffer, BUFFER_SIZE);
	if ()
	return (buffer);
}

