/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abazzoun <abazzoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/09 14:05:06 by abazzoun          #+#    #+#             */
/*   Updated: 2026/09/09 17:03:55 by abazzoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPHERE_H
# define SPHERE_H

# include "color.h"
# include "vector.h"

typedef struct	s_sphere
{
	t_vec3			pos;
	t_color			color;
	double			diameter;
	struct s_sphere	*next;
}				t_sphere;

#endif
