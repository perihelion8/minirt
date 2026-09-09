/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abazzoun <abazzoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/09 16:00:34 by abazzoun          #+#    #+#             */
/*   Updated: 2026/09/09 17:05:50 by abazzoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "scene.h"

int 	parser_camera(t_camera *camera, char **s, int linenumber);
int		parser_ambient(t_ambient *ambient, char **s, int linenumber);
int		parser_light(t_light *light, char **s, int linenumber);
int		parser_plane(t_plane **planell, char **s, int linenumber);
int		parser_sphere(t_sphere **spherell, char **s, int linenumber);
int		parser_cylinder(t_cylinder **cylinderll, char **s, int linenumber);
int		parser_vec3(t_vec3 *vec, char **line, int linenumber);
int		parser_color(t_color *color, char **s, int linenumber);
int		parser_double(double *dst, char **s, int linenumber);
int		parser_int(int *dst, char **s, int linenumber);
int 	accept(char **s, char c);
int 	expect(char **s, char c, int linenumber);
void	unexpected(char c, int linenumber);
char	*get_next_line(int fd);

#endif


