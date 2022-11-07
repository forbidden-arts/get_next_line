/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpalmer <dpalmer@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 11:01:28 by dpalmer           #+#    #+#             */
/*   Updated: 2022/11/07 09:04:25 by dpalmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_gnl_read_join(char *remain, char *buff)
{
	size_t	i;
	size_t	j;
	char	*str;

	if (!remain)
	{
		remain = (char *)malloc(1 * sizeof(char));
		remain[0] = '\0';
	}
	if (!remain || !buff)
		return (NULL);
	str = malloc(sizeof(char) * ((ft_strlen(remain) + ft_strlen(buff)) + 1));
	if (str == NULL)
		return (NULL);
	i = -1;
	j = 0;
	if (remain)
		while (remain[++i] != '\0')
			str[i] = remain[i];
	while (buff[j] != '\0')
		str[i++] = buff[j++];
	str[ft_strlen(remain) + ft_strlen(buff)] = '\0';
	free(remain);
	return (str);
}

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
		str = ft_gnl_read_join(str, buff);
	}
	free(buff);
	return (str);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*parse_buff;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	parse_buff = ft_load_parse_buff(fd, parse_buff);
	if (!parse_buff)
		return (NULL);
	line = ft_parse_line(parse_buff);
	parse_buff = ft_prep_parse(parse_buff);
	return (line);
}
