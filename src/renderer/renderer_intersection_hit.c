/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer_intersection_hit.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abazzoun <abazzoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/14 13:22:34 by abazzoun          #+#    #+#             */
/*   Updated: 2026/09/17 21:18:28 by abazzoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "renderer_intersection.h"

t_hit	no_hit(void)
{
	t_hit	hit;

	hit = (t_hit){0};
	return (hit);
}
