/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine_input.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abazzoun <abazzoun@student.42beirut.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/18 21:56:50 by abazzoun          #+#    #+#             */
/*   Updated: 2026/09/20 12:05:40 by abazzoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENGINE_INPUT_H
# define ENGINE_INPUT_H

typedef enum e_input
{
	INPUT_FORWARD,
	INPUT_BACKWARD,
	INPUT_LEFT,
	INPUT_RIGHT,
	INPUT_UP,
	INPUT_DOWN,
	INPUT_YAW_LEFT,
	INPUT_YAW_RIGHT,
	INPUT_PITCH_UP,
	INPUT_PITCH_DOWN,
	INPUT_FAST,
	INPUT_FULLSCREEN,
	INPUT_COUNT
}	t_input;

void	keycodes_init(int *keycodes);
int		handle_close(void *param);
int		handle_key_press(int keycode, void *param);
int		handle_key_release(int keycode, void *param);
int		handle_focus_out(void *param);

#endif
