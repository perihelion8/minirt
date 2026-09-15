/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abazzoun <abazzoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/10 12:58:36 by abazzoun          #+#    #+#             */
/*   Updated: 2026/09/10 21:28:22 by abazzoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIGHT_H
# define LIGHT_H

# include "color.h"
# include "vector.h"

typedef struct s_light
{
	t_vec3	pos;
	t_color	color;
	double	ratio;
	int		seen;
}	t_light;

#endif
