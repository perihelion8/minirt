/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_basis.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abazzoun <abazzoun@student.42beirut.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/18 21:55:12 by abazzoun          #+#    #+#             */
/*   Updated: 2026/09/09 21:21:30 by abazzoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "math/floating_point.h"
#include "vector.h"

int	vec3_basis(t_vec3 *forward, t_vec3 *right, t_vec3 *up)
{
	t_vec3	reference_up;

	if (approximately_zero(vec3_length(*forward)))
		return (0);
	*forward = vec3_normalize(*forward);
	reference_up = (t_vec3){0.0, 1.0, 0.0};
	if (vec3_are_parallel(reference_up, *forward))
		reference_up = (t_vec3){0.0, 0.0, 1.0};
	*right = vec3_normalize(vec3_cross(reference_up, *forward));
	*up = vec3_cross(*forward, *right);
	return (1);
}
