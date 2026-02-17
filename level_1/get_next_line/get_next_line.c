/*
Assignment name : broken_GNL
Expected files  : get_next_line.c get_next_line.h
Allowed functions : read, free, malloc
--------------------------------------------------------------------------------
Repair the function ‘get_next_line’ in the file get_next_line.c, whose prototype should be:
char *get_next_line(int fd);

You may need to repair other functions as well.

Description of the ‘get_next_line’ function:

Your function must return a line that has been read from the file descriptor
passed as a parameter.

A ‘line that has been read’ is defined as a succession of 0 to n characters
ending with ‘
’ (ASCII code 0x0a) or with End of File (EOF).

The line should be returned including the ‘
’ if there is one at the end
of the line that has been read.

When you reach the EOF, you must store the current buffer in a char * and
return it. If the buffer is empty, you must return NULL.

In case of an error, return NULL.

If not returning NULL, the pointer should be freeable.

Your program will be compiled with the flag -D BUFFER_SIZE=xx, which must be
used as the buffer size for the read calls in your functions.

Your function must be free of memory leaks.

When you reach the EOF, your function should not keep any memory allocated with
malloc except for the line that has been returned.

Calling your function get_next_line in a loop will allow you to read
the text available on a file descriptor one line at a time until the end of the
text, regardless of the size of the text or any of its lines.

Make sure that your function behaves correctly when reading from a file, from the
standard output, from a redirection etc.

No call to another function will be done on the file descriptor between two calls
of get_next_line.

Finally, we consider that get_next_line has undefined behavior when reading
from a binary file.
*/

#include "get_next_line.h"

size_t	ft_strlen(const char *str)
{
	if (!str)
		return (0);
	size_t	i = 0;

	while (str[i])
		i++;
	return (i);
}

char	*ft_strdup(const char *str)
{
	if (!str)
		return (NULL);
	
	size_t	i = 0;
	char	*copy = malloc(sizeof(char) * (ft_strlen(str) + 1));
	
	if (!copy)
		return (NULL);
	while (str[i])
	{
		copy[i] = str[i];
		i++;
	}
	copy[i] = '\0';
	return (copy);
}

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE];
	char		line[999999];
	static int	b_read;
	static int	b_pos;
	int			i = 0;

	while (1)
	{
		if (b_pos >= b_read)
		{
			b_read = read(fd, buffer, BUFFER_SIZE);
			b_pos = 0;
			if (b_read <= 0)
				break ;
		}
		line[i++] = buffer[b_pos++];
		if (buffer[b_pos - 1] == '\n')
			break ;
	}
	line[i] = '\0';
	if (i <= 0)	// Checks for EOF or empty input. Avoids returning a spurious empty line and ensures the main while loop terminates correctly -> (i == 0)
		return (NULL);
	return (ft_strdup(line));
}

// #include <fcntl.h>
// #include <stdio.h>

// int	main(void)
// {
// 	char	*line;
// 	int		fd = open("test.txt", O_RDONLY);

// 	if (fd < 0)
// 		return (1);
// 	while ((line = get_next_line(fd)) != NULL)
// 	{
// 		printf("%s", line);
// 		free(line);
// 	}
// 	close (fd);
// 	return (0);
// }
