/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spotlight.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abazzoun <abazzoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/19 18:52:45 by abazzoun          #+#    #+#             */
/*   Updated: 2026/09/20 00:17:42 by abazzoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPOTLIGHT_H
# define SPOTLIGHT_H

# include "vector.h"
# include "color.h"

typedef struct s_spotlight
{
	t_vec3	pos;
	t_vec3	direction;
	double	brightness;
	t_color	color;
	int		angle;
	double	cutoff_cos;
}	t_spotlight;

#endif
