/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loader_rt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abazzoun <abazzoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/09 00:03:38 by abazzoun          #+#    #+#             */
/*   Updated: 2026/09/15 09:42:46 by abazzoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include "libft.h"
#include "scene.h"
#include "parser.h"

static int	open_file(const char *filename)
{
	size_t	len;
	int		fd;

	len = ft_strlen(filename);
	if (len < 3
		|| filename[len - 1] != 't'
		|| filename[len - 2] != 'r'
		|| filename[len - 3] != '.')
	{
		loader_error("File should have extenion rt.");
		return (-1);
	}
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (perror("Error\nrt file"), -1);
	return (fd);
}

static int	validate_scene(t_scene *scene)
{
	if (!scene->camera.seen || !scene->light.seen || !scene->ambient.seen)
	{
		loader_error("Ambient, light and camera are necessary.");
		return (0);
	}
	if (!scene->shapell)
	{
		loader_error("There is no shapes in the scene.");
		return (0);
	}
	return (1);
}

int	loader_rt(t_scene *scene, const char *filename)
{
	char	*line;
	int		linenumber;
	int		fd;

	scene_init(scene);
	get_next_line(-1);
	fd = open_file(filename);
	if (fd == -1)
		return (0);
	errno = 0;
	line = get_next_line(fd);
	linenumber = 0;
	while (line)
	{
		if (!parser_line(scene, line, ++linenumber))
			return (close(fd), free(line), 0);
		free(line);
		errno = 0;
		line = get_next_line(fd);
	}
	if (errno != 0)
		return (perror("Error\nget_next_line"), close(fd), 0);
	if (close(fd) == -1)
		return (perror("Error\nrt file"), 0);
	if (!validate_scene(scene))
		return (0);
	return (1);
}
