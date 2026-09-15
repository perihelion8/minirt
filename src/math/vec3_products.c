/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_products.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abazzoun <abazzoun@student.42beirut.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/18 21:55:31 by abazzoun          #+#    #+#             */
/*   Updated: 2026/09/10 17:54:05 by abazzoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "vector.h"
#include "math/floating_point.h"

t_vec3	vec3_cross(t_vec3 a, t_vec3 b)
{
	return ((t_vec3){
		a.y * b.z - a.z * b.y,
		a.z * b.x - a.x * b.z,
		a.x * b.y - a.y * b.x});
}

double	vec3_dot(t_vec3 a, t_vec3 b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

int	vec3_are_parallel(t_vec3 a, t_vec3 b)
{
	if (approximately_zero(vec3_length(a))
		|| approximately_zero(vec3_length(b)))
		return (0);
	a = vec3_normal(a);
	b = vec3_normal(b);
	return (approximately_equal(fabs(vec3_dot(a, b)), 1.0));
}
