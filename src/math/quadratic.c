/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quadratic.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abazzoun <abazzoun@student.42beirut.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/18 21:54:56 by abazzoun          #+#    #+#             */
/*   Updated: 2026/08/18 22:22:10 by abazzoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "math/floating_point.h"

double	quadratic_minimum_positive_root(double a, double b, double c)
{
	double	discriminant;
	double	root;

	if (approximately_zero(a))
		return (-1.0);
	discriminant = b * b - 4.0 * a * c;
	if (discriminant < 0.0)
		return (-1.0);
	root = (-b - sqrt(discriminant)) / (2.0 * a);
	if (!is_positive(root))
		root = (-b + sqrt(discriminant)) / (2.0 * a);
	if (!is_positive(root))
		return (-1.0);
	return (root);
}

int	solve_quadratic(double a, double b, double c, double *root1,
		double *root2)
{
	double	discriminant;

	if (approximately_zero(a) || !is_positive(a))
	{
		*root1 = 0.0;
		*root2 = 0.0;
		return (0);
	}
	discriminant = b * b - 4.0 * a * c;
	if (approximately_zero(discriminant))
	{
		*root1 = -b / (2.0 * a);
		*root2 = 0.0;
		return (1);
	}
	if (!is_positive(discriminant))
	{
		*root1 = 0.0;
		*root2 = 0.0;
		return (0);
	}
	discriminant = sqrt(discriminant);
	*root1 = (-b - discriminant) / (2.0 * a);
	*root2 = (-b + discriminant) / (2.0 * a);
	return (1);
}
