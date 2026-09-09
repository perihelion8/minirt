/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abazzoun <abazzoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/09 10:28:02 by abazzoun          #+#    #+#             */
/*   Updated: 2026/09/09 17:57:48 by abazzoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"
#include "scene.h"


static void free_spherell(t_sphere *head)
{
    t_sphere *next;

    while (head)
    {
        next = head->next;
        free(head);
        head = next;
    }
}

static void free_cylinderll(t_cylinder *head)
{
    t_cylinder *next;

    while (head)
    {
        next = head->next;
        free(head);
        head = next;
    }
}

static void free_planell(t_plane *head)
{
    t_plane *next;

    while (head)
    {
        next = head->next;
        free(head);
        head = next;
    }
}

void	scene_destroy(t_scene *scene)
{
	if (!scene)
		return ;
	free_cylinderll(scene->cylinderll);
	free_spherell(scene->spherell);
	free_planell(scene->planell);
}
