/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpalmer <dpalmer@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 11:01:28 by dpalmer           #+#    #+#             */
/*   Updated: 2022/11/08 18:59:44 by dpalmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_gnl_join(char *remain, char *buff);
static char	*ft_load_parse_buff(int fd, char *str);
static char	*ft_parse_line(char *str);
static char	*ft_prep_parse(char *str);

/* Loads the parse_buff with the contents of a file, BUFFER bytes at a time.
** Because it is highly unlikely that the newline or EOF will occur at an exact
** multiple of the BUFFER_SIZE, the func stores the remainder in parse_buff[fd]. 

*******************************************************************************
* Bonus Instructions say <MULTIPLE> not <INFINITE>, so 1024 was chosen as the *
* number of files that can be handled simultaneously. Will revisit later.     * 
******************************************************************************/

char	*get_next_line(int fd)
{
	char		*line;
	static char	*parse_buff[1024];

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	parse_buff[fd] = ft_load_parse_buff(fd, parse_buff[fd]);
	if (!parse_buff[fd])
		return (NULL);
	line = ft_parse_line(parse_buff[fd]);
	parse_buff[fd] = ft_prep_parse(parse_buff[fd]);
	return (line);
}

/* Combine any remaining string (chars past the "\n") that was previously read
** by the buffer to the new buffer. If remain does not exist, create a blank
** string. This is a bastardized version of ft_strjoin. */

static char	*ft_gnl_join(char *remain, char *buff)
{
	char	*str;

	if (!remain)
	{
		remain = (char *)malloc(sizeof(char) * 1);
		remain[0] = '\0';
	}
	str = ft_strjoin(remain, buff);
	return (str);
}

/* Allocates for the BUFFER_SIZE, reads that amount of bytes unless EOF is 
** encountered. Joins any previously ready bites that had occurred after a
** an earlier newline. Continues to loop, reading BUFFER_SIZE bytes, until
** newline or EOF is found. */

static char	*ft_load_parse_buff(int fd, char *str)
{
	char	*buff;
	int		read_bytes;

	buff = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buff)
		return (NULL);
	read_bytes = 1;
	while (!ft_strchr(str, '\n') && read_bytes != 0)
	{
		read_bytes = read(fd, buff, BUFFER_SIZE);
		if (read_bytes == -1)
		{
			free(buff);
			return (NULL);
		}
		buff[read_bytes] = '\0';
		str = ft_gnl_join(str, buff);
	}
	free(buff);
	return (str);
}
/* Due to libft being forbidden, malloc is used instead of calloc. The memory 
** allocation is given two(2) extra spots instead of the usual one(1) because
** we need also capture the "\n" on the existing line before null-terminating */

static char	*ft_parse_line(char *str)
{
	int		i;
	char	*result;

	if (!str)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	result = (char *)malloc(sizeof(char) * (i + 2));
	if (!result)
		return (NULL);
	ft_strlcpy(result, str, i + 1);
	return (result);
}

/* Iterates through a string until the newline (or EOF) is found. If there are
** chars beyond the newline, they are copied to *result and returned for later
** use. Considered pointers here, but iterators seemed easier for this func.*/

static char	*ft_prep_parse(char *str)
{
	size_t	i;
	size_t	j;
	char	*result;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (!str[i])
	{
		free(str);
		return (NULL);
	}
	result = (char *)malloc(sizeof(char) * (ft_strlen(str) - i + 1));
	if (!result)
		return (NULL);
	i++;
	j = 0;
	while (str[i])
		result[j++] = str[i++];
	result[j] = '\0';
	free(str);
	return (result);
}

int	main(void)
{
	char	*line;
	int		i;
	int		fd1;
	int		fd2;
	int		fd3;
	fd1 = open("tests/test1.txt", O_RDONLY);
	fd2 = open("tests/test2.txt", O_RDONLY);
	fd3 = open("tests/test3.txt", O_RDONLY);
	i = 1;
	while (i < 8)
	{
		line = get_next_line(fd1);
		printf("line [%02d]:\n%s\n", i, line);
		line = get_next_line(fd2);
		printf("line [%02d]:\n%s\n", i, line);
		line = get_next_line(fd3);
		printf("line [%02d]:\n%s\n", i, line);
		i++;
	}
	close(fd1);
	close(fd2);
	close(fd3);
	return (0);
}
