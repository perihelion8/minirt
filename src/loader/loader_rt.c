/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loader_rt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abazzoun <abazzoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/09 00:03:38 by abazzoun          #+#    #+#             */
/*   Updated: 2026/09/09 16:48:21 by abazzoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <fcntl.h>
#include "scene.h"
#include "parser.h"

static int	parser_line(t_scene *scene, char *s, int linenumber)
{
	if (accept(&s, 'A'))
		return (parser_ambient(&scene->ambient, &s, linenumber));
	if (accept(&s, 'C'))
		return (parser_camera(&scene->camera, &s, linenumber));
	if (accept(&s, 'L'))
		return (parser_light(&scene->light, &s, linenumber));
	if (accept(&s, 's') && accept(&s, 'p'))
		return (parser_sphere(&scene->spherell, &s, linenumber));
	if (accept(&s, 'p') && accept(&s, 'l'))
		return (parser_plane(&scene->planell, &s, linenumber));
	if (accept(&s, 'c') && accept(&s, 'y'))
		return (parser_cylinder(&scene->cylinderll, &s, linenumber));
	unexpected(*s, linenumber);
	return (0);
}

int	loader_rt(t_scene *scene, const char *filename)
{
	char	*line;
	int		linenumber;
	int		fd;

	fd = open(filename, O_RDONLY);
	line = get_next_line(fd);
	linenumber = 0;
	while (line)
	{
		linenumber++;
		if (!parser_line(scene, line, linenumber))
			return (free(line), 0);
		free(line);
		line = get_next_line(fd);
	}
	if (!scene->cylinderll && !scene->spherell && scene->planell)
		return (0);
	return (1);
}
