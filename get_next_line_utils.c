/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshikhov <mshikhov@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/12 23:56:19 by mshikhov          #+#    #+#             */
/*   Updated: 2026/11/11 03:15:11 by mshikhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

static size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	len_d;
	size_t	len_s;
	size_t	i;
	size_t	j;

	len_s = ft_strlen(src);
	if (size == 0)
		return (len_s);
	len_d = ft_strlen(dst);
	if (size <= len_d)
		return (len_s + size);
	i = len_d;
	j = 0;
	while (src[j] && i < size - 1)
	{
		dst[i] = src[j];
		i++;
		j++;
	}
	dst[i] = '\0';
	return (len_d + len_s);
}

char	*ft_strjoin(char *s1, char *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	size_t	len;
	char	*str;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	len = s1_len + s2_len + 1;
	str = (char *)malloc(sizeof(char) * len);
	if (str == NULL)
		return (NULL);
	str[0] = '\0';
	ft_strlcat(str, s1, len);
	ft_strlcat(str, s2, len);
	return (str);
}

char	*ft_substr(char *s, unsigned int start, size_t len)
{
	size_t	s_len;
	char	*str;

	s_len = ft_strlen(s);
	if (start >= s_len)
		len = 0;
	else if (len > s_len - start)
		len = s_len - start;
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (str == NULL)
		return (NULL);
	str[0] = '\0';
	if (start < s_len)
		ft_strlcat(str, &s[start], len + 1);
	return (str);
}

char	*ft_strchr(char *s, int c)
{
	char	*str;
	char	chr;

	str = (char *)s;
	chr = (char)c;
	while (*str)
	{
		if (*str == chr)
			return (str);
		str++;
	}
	if (*str == chr)
		return (str);
	return (NULL);
}
