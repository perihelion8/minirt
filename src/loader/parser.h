/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abazzoun <abazzoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/09 16:00:34 by abazzoun          #+#    #+#             */
/*   Updated: 2026/09/20 13:43:51 by abazzoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "scene.h"
# include "linkedlist.h"
# include "loader_rt.h"

int		parser_camera(t_camera *camera, char **s, int linenumber);
int		parser_ambient(t_ambient *ambient, char **s, int linenumber);
int		parser_light(t_light *light, char **s, int linenumber);
int		parser_spotlight(t_spotlight *spotlight, char **line, int linenumber);
int		parser_plane(t_plane *plane, char **s, int linenumber);
int		parser_sphere(t_sphere *sphere, char **s, int linenumber);
int		parser_cylinder(t_cylinder *cylinder, char **s, int linenumber);
int		parser_hyperboloid(t_hyperboloid *hyperboloid, char **s,
			int linenumber);
int		parser_vec3(t_vec3 *vec, char **s, int linenumber);
int		parser_vec3_normal(t_vec3 *vec, char **s, int linenumber);
int		parser_color(t_color *color, char **s, int linenumber);
int		parser_double(double *dst, char **s, int linenumber);
int		parser_ratio(double *dst, char **s, int linenumber);
int		parser_dimension(double *dst, char **s, int linenumber);
int		parser_int(int *dst, char **s, int linenumber);
void	parser_error(int linenumber, const char *str);
void	parser_error_token(int linenumber, char c);
int		parser_line(t_scene *scene, t_loader_rt *loader, char *s);
void	loader_error(const char *message);
int		all_space(char **s);
int		accept(char **s, char c);
int		expect(char **s, char c, int linenumber);
void	unexpected(char c, int linenumber);
char	*get_next_line(int fd);
int		accept_identifier(char **s, const char *identifier, int linenumber);

#endif
