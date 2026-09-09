/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abazzoun <abazzoun@student.42beirut.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/18 21:48:39 by abazzoun          #+#    #+#             */
/*   Updated: 2026/09/09 20:04:20 by abazzoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "loader.h"

int	main(int argc, char **argv)
{
	t_scene		scene;
	t_engine	*engine;

	scene.ambient.color.r = -1;
	scene.light.color.r = -1;
	scene.camera.fov = -100.0;
	scene.spherell = NULL;
	scene.planell = NULL;
	scene.cylinderll = NULL;
	if (argc != 2 || !loader_rt(&scene, argv[1]))
		return (1);
	engine = engine_create(&scene);
	if (engine == NULL)
		return (scene_destroy(&scene), 1);
	engine_run(engine);
	engine_destroy(engine);
	scene_destroy(&scene);
	return (0);
}
