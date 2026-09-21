/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floating_point.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abazzoun <abazzoun@student.42beirut.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/18 21:54:52 by abazzoun          #+#    #+#             */
/*   Updated: 2026/09/10 12:39:06 by abazzoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "floating_point_internal.h"

int	is_positive(double n)
{
	return (n > FLOATING_POINT_EPSILON);
}

int	approximately_zero(double n)
{
	return (fabs(n) < FLOATING_POINT_EPSILON);
}

int	approximately_equal(double a, double b)
{
	return (fabs(a - b) < FLOATING_POINT_EPSILON);
}
