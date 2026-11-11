/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshikhov <mshikhov@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/12 04:32:18 by mshikhov          #+#    #+#             */
/*   Updated: 2026/11/11 03:48:17 by mshikhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "get_next_line.h"

static size_t	ft_findln(char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0' && s[i] != '\n')
		i++;
	return (i);
}

static void	update_remainder(char **remainder, char *str)
{
	char	*temp;

	if (!*remainder)
	{
		*remainder = ft_substr(str, 0, ft_strlen(str));
		return ;
	}
	temp = *remainder;
	*remainder = ft_strjoin(*remainder, str);
	free(temp);
}

static char	*get_return(char **remainder)
{
	char	*temp;
	char	*ret;
	size_t	len;

	temp = *remainder;
	len = ft_findln(temp);
	if (temp[len] == '\n')
		len++;
	ret = ft_substr(temp, 0, len);
	if (!ret)
	{
		free(temp);
		*remainder = NULL;
		return (NULL);
	}
	*remainder = ft_substr(temp, len, ft_strlen(temp) - len);
	free(temp);
	return (ret);
}

ssize_t	read_file(char **remainder, int fd)
{
	ssize_t	bytes_read;
	char	*buffer;

	if (*remainder && ft_strchr(*remainder, '\n'))
		return (1);
	buffer = malloc((size_t)BUFFER_SIZE + 1);
	if (!buffer)
		return (-1);
	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read > 0)
		{
			buffer[bytes_read] = '\0';
			update_remainder(remainder, buffer);
			if (!*remainder)
				bytes_read = -1;
			else if (ft_strchr(buffer, '\n'))
				break ;
		}
	}
	free(buffer);
	return (bytes_read);
}

char	*get_next_line(int fd)
{
	static char	*remainder;
	ssize_t		bytes_read;

	if (BUFFER_SIZE <= 0 || fd < 0)
		return (NULL);
	bytes_read = read_file(&remainder, fd);
	if (bytes_read == -1 || !remainder || *remainder == '\0')
	{
		free(remainder);
		remainder = NULL;
		return (NULL);
	}
	return (get_return(&remainder));
}
