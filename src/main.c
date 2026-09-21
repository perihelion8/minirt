/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abazzoun <abazzoun@student.42beirut.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/18 21:48:39 by abazzoun          #+#    #+#             */
/*   Updated: 2026/09/19 17:20:32 by abazzoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "loader.h"
#include "libft.h"

int	main(int argc, char **argv)
{
	t_engine	engine;
	t_scene		scene;

	if (argc != 2)
	{
		ft_putendl_fd("Error\nNo rt file", 2);
		return (1);
	}
	if (!loader_rt(&scene, argv[1]))
		return (scene_destroy(&scene), 1);
	if (!engine_init(&engine, &scene))
		return (scene_destroy(&scene), 1);
	engine_run(&engine);
	scene_destroy(&scene);
	engine_destroy(&engine);
	return (0);
}
