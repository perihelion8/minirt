/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hyperboloid.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abazzoun <abazzoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/18 02:55:48 by abazzoun          #+#    #+#             */
/*   Updated: 2026/09/19 17:53:38 by abazzoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HYPERBOLOID_H
# define HYPERBOLOID_H

# include "vector.h"
# include "color.h"

typedef struct s_hyperboloid
{
	t_vec3				pos;
	t_vec3				axis;
	t_vec3				right;
	t_vec3				up;
	t_color				color;
	double				diameter;
	double				height;
}	t_hyperboloid;

#endif
