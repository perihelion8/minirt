/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abazzoun <abazzoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/10 12:58:31 by abazzoun          #+#    #+#             */
/*   Updated: 2026/09/14 14:06:51 by abazzoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CYLINDER_H
# define CYLINDER_H

# include "color.h"
# include "vector.h"

typedef struct s_cylinder
{
	t_vec3				pos;
	t_vec3				axis;
	t_vec3				right;
	t_vec3				up;
	t_color				color;
	double				diameter;
	double				height;
}	t_cylinder;


#endif
