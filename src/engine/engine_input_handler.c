/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine_input_handler.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abazzoun <abazzoun@student.42beirut.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/18 21:56:46 by abazzoun          #+#    #+#             */
/*   Updated: 2026/09/17 15:14:30 by abazzoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "engine_input.h"
#include <X11/keysym.h>

static void	set_key(t_engine *engine, int keycode, int pressed)
{
	int	i;

	if (keycode >= XK_A && keycode <= XK_Z)
		keycode += XK_a - XK_A;
	i = 0;
	while (i < INPUT_COUNT)
	{
		if (engine->keycodes[i] == keycode)
			engine->keypressed[i] = pressed;
		i++;
	}
}

int	handle_close(void *param)
{
	engine_stop(param);
	return (0);
}

int	handle_key_press(int keycode, void *param)
{
	if (keycode == XK_Escape)
		engine_stop(param);
	else
		set_key(param, keycode, 1);
	return (0);
}

int	handle_key_release(int keycode, void *param)
{
	set_key(param, keycode, 0);
	return (0);
}

int	handle_focus_out(void *param)
{
	t_engine	*engine;
	int			i;

	engine = param;
	i = 0;
	while (i < INPUT_COUNT)
		engine->keypressed[i++] = 0;
	engine->last_tick = 0;
	return (0);
}
