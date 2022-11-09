/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpalmer <dpalmer@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 13:55:21 by dpalmer           #+#    #+#             */
/*   Updated: 2022/11/09 14:27:04 by dpalmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

/* Misc utilites needed for evaluation. These will eventually be subsumed	**
** into the general LIBFT file (if possible) once this project is complete. **/

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strchr(const char *s, int c)
{
	char	*chr;

	if (!s)
		return (NULL);
	chr = (char *)s;
	c %= 128;
	while (*chr != c)
	{
		if (!*chr)
			return (NULL);
		chr++;
	}
	return (chr);
}

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;
	size_t	s_len;
	size_t	d_len;

	j = 0;
	if ((!dst ||!src) && dstsize == 0)
		return (0);
	d_len = ft_strlen(dst);
	s_len = ft_strlen(src);
	i = d_len;
	if (dstsize == 0 || dstsize <= d_len)
		return (s_len + dstsize);
	while (src[j] && (d_len + j) < dstsize)
		dst[i++] = src[j++];
	if ((d_len + j) == dstsize && d_len < dstsize)
		dst[i - 1] = '\0';
	else
		dst[i] = '\0';
	return (s_len + d_len);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	s_len;

	i = 0;
	if (!src && dstsize == 0)
		return (0);
	s_len = ft_strlen(src);
	while (src[i] != '\0' && i < dstsize)
	{
		dst[i] = src[i];
		i++;
	}
	if (dstsize <= s_len)
		dst[dstsize - 1] = '\0';
	else
		dst[i] = '\0';
	return (s_len);
}
