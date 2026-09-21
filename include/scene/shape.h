/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abazzoun <abazzoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/18 09:03:32 by abazzoun          #+#    #+#             */
/*   Updated: 2026/09/20 13:08:37 by abazzoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHAPE_H
# define SHAPE_H

# include "plane.h"
# include "sphere.h"
# include "cylinder.h"
# include "hyperboloid.h"

typedef enum e_shape_type
{
	PLANE,
	SPHERE,
	CYLINDER,
	HYPERB
}	t_shape_type;

typedef struct s_shape
{
	t_shape_type	type;
	union
	{
		t_plane			plane;
		t_sphere		sphere;
		t_cylinder		cylinder;
		t_hyperboloid	hyperboloid;
	};
}	t_shape;

#endif
