/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quadratic.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abazzoun <abazzoun@student.42beirut.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/18 21:54:56 by abazzoun          #+#    #+#             */
/*   Updated: 2026/09/20 12:43:52 by abazzoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

static void	sort_roots(double *root)
{
	double	tmp;

	if (root[0] > root[1])
	{
		tmp = root[0];
		root[0] = root[1];
		root[1] = tmp;
	}
}

int	solve_quadratic(double a, double b, double c, double *root)
{
	double	discriminant;
	double	q;

	root[0] = 0.0;
	root[1] = 0.0;
	if (a == 0.0)
		return (0);
	discriminant = b * b - 4.0 * a * c;
	if (discriminant < 0.0)
		return (0);
	if (discriminant == 0.0)
	{
		root[0] = -b / (2.0 * a);
		root[1] = root[0];
	}
	else
	{
		discriminant = sqrt(discriminant);
		q = -0.5 * (b + copysign(discriminant, b));
		root[0] = q / a;
		root[1] = c / q;
		sort_roots(root);
	}
	return (1);
}
