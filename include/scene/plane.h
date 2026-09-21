/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abazzoun <abazzoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/09 14:05:00 by abazzoun          #+#    #+#             */
/*   Updated: 2026/09/14 14:06:41 by abazzoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLANE_H
# define PLANE_H

# include "vector.h"
# include "color.h"

typedef struct s_plane
{
	t_vec3			pos;
	t_vec3			normal;
	t_color			color;
}	t_plane;

#endif
