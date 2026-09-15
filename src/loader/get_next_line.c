/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 get_next_line.c									:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: abazzoun <abazzoun@student.42.fr>			+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2026/09/09 16:42:27 by abazzoun		   #+#	  #+#			  */
/*	 Updated: 2026/09/10 17:48:56 by abazzoun		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include "libft.h"
#include "get_next_line.h"

static int	str_append_mem(char **s1, char *s2, size_t size2)
{
	size_t	size1;
	char	*tmp;

	size1 = 0;
	if (*s1)
		size1 = ft_strlen(*s1);
	tmp = malloc(size1 + size2 + 1);
	if (!tmp)
		return (0);
	if (*s1)
		ft_memcpy(tmp, *s1, size1);
	ft_memcpy(tmp + size1, s2, size2);
	tmp[size1 + size2] = '\0';
	free(*s1);
	*s1 = tmp;
	return (1);
}

static int	read_until_newline(int fd, char *buffer, char **line)
{
	int	bytes;

	while (!ft_strchr(buffer, '\n'))
	{
		if (*buffer && !str_append_mem(line, buffer, ft_strlen(buffer)))
			return (0);
		buffer[0] = '\0';
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes < 0)
			return (0);
		if (ft_memchr(buffer, '\0', bytes))
			return (errno = EINVAL, 0);
		buffer[bytes] = '\0';
		if (bytes == 0)
			return (1);
	}
	return (1);
}

static int	extract_line(char *buffer, char **line)
{
	char	*newline;

	newline = ft_strchr(buffer, '\n');
	if (!newline)
		return (1);
	if (!str_append_mem(line, buffer, newline - buffer + 1))
		return (0);
	ft_memmove(buffer, newline + 1, ft_strlen(newline + 1) + 1);
	return (1);
}

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	char		*line;

	line = NULL;
	if (fd < 0 || read(fd, buffer, 0) < 0)
	{
		buffer[0] = '\0';
		return (NULL);
	}
	if (!read_until_newline(fd, buffer, &line)
		|| !extract_line(buffer, &line))
	{
		free(line);
		buffer[0] = '\0';
		return (NULL);
	}
	return (line);
}
