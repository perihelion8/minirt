/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_metrics.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abazzoun <abazzoun@student.42beirut.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/18 21:55:23 by abazzoun          #+#    #+#             */
/*   Updated: 2026/08/18 21:55:25 by abazzoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "vector.h"

double	vec3_length_squared(t_vec3 v)
{
	return (vec3_dot(v, v));
}

double	vec3_length(t_vec3 v)
{
	return (sqrt(vec3_length_squared(v)));
}

t_vec3	vec3_normalize(t_vec3 v)
{
	double	len;

	len = vec3_length(v);
	if (len == 0)
		return ((t_vec3){0, 0, 0});
	return ((t_vec3){v.x / len, v.y / len, v.z / len});
}
