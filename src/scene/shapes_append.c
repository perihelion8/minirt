/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapes_append.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abazzoun <abazzoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/09 16:26:29 by abazzoun          #+#    #+#             */
/*   Updated: 2026/09/09 20:43:30 by abazzoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "scene.h"
#include "libft.h"

t_cylinder	*cylinderll_append(t_cylinder **cylinderll)
{
	t_cylinder *cylinder;

	if (!*cylinderll)
	{
		*cylinderll = ft_calloc(1, sizeof(*cylinder));
		if (!*cylinderll)
		{
			perror("malloc");
			return (NULL);
		}
		return (*cylinderll);
	}
	cylinder = *cylinderll;
	while (cylinder->next)
		cylinder = cylinder->next;
	cylinder->next = ft_calloc(1, sizeof(*cylinder));
	if (!cylinder->next)
	{
		perror("malloc");
		return (NULL);
	}
	return (cylinder->next);
}	

t_plane	*planell_append(t_plane **planell)
{
	t_plane *plane;

	
	if (!*planell)
	{
		*planell = ft_calloc(1, sizeof(*plane));
		if (!planell)
		{
			perror("malloc");
			return (NULL);
		}
		return (*planell);
	}
	plane = *planell;
	while (plane->next)
		plane = plane->next;
	plane->next = ft_calloc(1, sizeof(*plane));
	if (!plane->next)
	{
		perror("malloc");
		return (NULL);
	}
	return (plane->next);
}	

t_sphere	*spherell_append(t_sphere **spherell)
{
	t_sphere *sphere;

	if (!*spherell)
	{
		*spherell = ft_calloc(1, sizeof(*sphere));
		if (!spherell)
		{
			perror("malloc");
			return (NULL);
		}
		return (*spherell);
	}
	sphere = *spherell;
	while (sphere->next)
		sphere = sphere->next;
	sphere->next = ft_calloc(1, sizeof(*sphere));
	if (!sphere->next)
	{
		perror("malloc");
		return (NULL);
	}
	return (sphere->next);
}	
