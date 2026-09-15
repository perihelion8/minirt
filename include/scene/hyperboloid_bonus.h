/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hyperboloid_bonus.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abazzoun <abazzoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/10 12:58:36 by abazzoun          #+#    #+#             */
/*   Updated: 2026/09/10 21:28:22 by abazzoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HYPERBOLOID_BONUS_H
# define HYPERBOLOID_BONUS_H

# include "color.h"
# include "vector.h"

typedef struct s_hyperboloid
{
	t_vec3	pos;
	t_vec3	axis;
	t_color	color;
	double	diameter;
	double	height;
}	t_hyperboloid;

#endif
