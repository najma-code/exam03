// Assignment name: filter
// Expected files: filter.c
// Allowed functions: read, write, strlen, memmem, memmove, malloc, calloc,
// realloc, free, printf, fprintf, stdout, stderr, perror
// --------------------------------------------------------------------------------

// Write a program that will take one and only one argument.

// Your program will then read from stdin and write all the content read in stdout
// except that every occurrence of s must be replaced by '*' (as many as the length
// of s). Your program will be tested with random buffer sizes, using a custom read
// function. Therefore the buffer being set in your program will be filled with a
// different number of chars each new call.


// For example:

// ./filter bonjour
// will behave in the same way as:
// sed 's/bonjour/*******/g'

// ./filter abc
// will behave in the same way as:
// sed's/abc/***/g'

// More generally your program must be the equivalent of the shell script filter.sh
// present in this directory (you can compare your program with it).

// In case of error during a read or a malloc, you must write "Error: " followed by
// the error message in stderr and return 1.

// If the program is called without arguments or with an empty argument or with multiple
// arguments, it must return 1.

// For example this should work:

// $> echo 'abcdefaaaabcdeabcabcdabc' | ./filter abc | cat -e
// ***defaaa***de******d***$
// $> echo 'ababcabababc' | ./filter ababc | cat -e
// *****ab*****$

#include <unistd.h>
#include <stdio.h>
#include <string.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 10
#endif

void	ft_filter(char *line, char *word)	// 'line' is the full text, 'word' is the word to be censored
{
	int	len = strlen(word);
	int	i = 0;

	while (line[i])
	{
		int	j = 0;
		while (word[j] && line[i + j] == word[j])
			j++;
		if (j == len)
		{
			int	k = 0;	// Count the number of asterisks
			while (k < len)
			{
				write(1, "*", 1);
				k++;
			}
			i += j;
		}
		else
		{
			write(1, &line[i], 1);
			i++;
		}
	}
}

int	main(int argc, char **argv)
{
	if (argc != 2 || !argv[1][0])
		return (1);
	char	line[999999];
	int		bytes_read = 1;
	int		i = 0;

	while (bytes_read > 0)
	{
		bytes_read = read(0, &line[i], BUFFER_SIZE);
		if (bytes_read < 0)
		{
			perror("Error");
			return (1);
		}
		i += bytes_read;
	}
	line[i] = '\0';
	ft_filter(line, argv[1]);
	return (0);
}
