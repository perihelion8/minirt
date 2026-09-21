/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine_input_keycodes.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abazzoun <abazzoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/16 12:06:25 by abazzoun          #+#    #+#             */
/*   Updated: 2026/09/17 14:58:05 by abazzoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine_input.h"
#include <X11/keysym.h>

void	keycodes_init(int *keycodes)
{
	keycodes[INPUT_FORWARD] = XK_w;
	keycodes[INPUT_BACKWARD] = XK_s;
	keycodes[INPUT_LEFT] = XK_a;
	keycodes[INPUT_RIGHT] = XK_d;
	keycodes[INPUT_UP] = XK_q;
	keycodes[INPUT_DOWN] = XK_e;
	keycodes[INPUT_YAW_LEFT] = XK_Left;
	keycodes[INPUT_YAW_RIGHT] = XK_Right;
	keycodes[INPUT_PITCH_UP] = XK_Up;
	keycodes[INPUT_PITCH_DOWN] = XK_Down;
	keycodes[INPUT_FAST] = XK_Shift_L;
	keycodes[INPUT_FULLSCREEN] = XK_F11;
}
