/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loader_rt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abazzoun <abazzoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/09 00:03:38 by abazzoun          #+#    #+#             */
/*   Updated: 2026/09/21 11:52:50 by abazzoun         ###   ########.fr       */
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
		loader_error("File extenion .rt");
		return (-1);
	}
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (perror("Error\nrt file"), -1);
	return (fd);
}

static int	loader_rt_init(t_loader_rt *loader, const char *filename,
				t_scene *scene)
{
	scene_init(scene);
	loader->fd = open_file(filename);
	if (loader->fd == -1)
		return (0);
	loader->linenumber = 0;
	loader->shapell = NULL;
	loader->spotlightll = NULL;
	get_next_line(-1);
	errno = 0;
	return (1);
}

static int	loader_rt_break(t_loader_rt *loader, char *line)
{
	free(line);
	close(loader->fd);
	destroyll((t_nodell *)loader->shapell);
	destroyll((t_nodell *)loader->spotlightll);
	return (0);
}

static int	loader_rt_clean_exit(t_loader_rt *loader, t_scene *scene)
{
	scene->shapea_len = lenll((t_nodell *)loader->shapell);
	scene->shapea = shapell_to_shapea(loader->shapell);
	scene->spotlighta_len = lenll((t_nodell *)loader->spotlightll);
	scene->spotlighta = spotlightll_to_spotlighta(loader->spotlightll);
	destroyll((t_nodell *)loader->spotlightll);
	destroyll((t_nodell *)loader->shapell);
	if (close(loader->fd) == -1)
	{
		perror("Error\nload rt");
		return (0);
	}
	if ((scene->shapea_len > 0 && !scene->shapea)
		|| (scene->spotlighta_len > 0 && !scene->spotlighta))
		return (0);
	if (!validate_scene(scene))
	{
		loader_error("not valid scene");
		return (0);
	}
	return (1);
}

int	loader_rt(t_scene *scene, const char *filename)
{
	t_loader_rt	loader;
	char		*line;

	if (!loader_rt_init(&loader, filename, scene))
		return (0);
	line = get_next_line(loader.fd);
	while (line)
	{
		++loader.linenumber;
		if (!parser_line(scene, &loader, line))
			return (loader_rt_break(&loader, line));
		free(line);
		errno = 0;
		line = get_next_line(loader.fd);
	}
	if (errno != 0)
		return (perror("Error\nload rt"), loader_rt_break(&loader, NULL));
	return (loader_rt_clean_exit(&loader, scene));
}
