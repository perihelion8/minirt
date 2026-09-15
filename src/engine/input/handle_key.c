/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_key.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abazzoun <abazzoun@student.42beirut.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/18 21:56:46 by abazzoun          #+#    #+#             */
/*   Updated: 2026/09/15 10:14:17 by abazzoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "handle_key.h"
#include "engine.h"
#include <X11/keysym.h>

static void	set_key(t_engine *engine, int keycode, int pressed)
{
	static const int	codes[INPUT_COUNT] = {XK_w, XK_s, XK_a, XK_d,
		XK_space, XK_c, XK_Left, XK_Right, XK_Up, XK_Down, XK_Shift_L};
	int					i;

	if (keycode >= XK_A && keycode <= XK_Z)
		keycode += XK_a - XK_A;
	i = 0;
	while (i < INPUT_COUNT)
	{
		if (codes[i] == keycode)
			engine->keys[i] = pressed;
		i++;
	}
}

int	handle_close(void *param)
{
	engine_stop(param);
	return (0);
}

int	handle_key(int keycode, void *param)
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
		engine->keys[i++] = 0;
	engine->last_tick = 0;
	return (0);
}
