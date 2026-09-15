/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_key.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abazzoun <abazzoun@student.42beirut.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/18 21:56:50 by abazzoun          #+#    #+#             */
/*   Updated: 2026/09/15 10:06:23 by abazzoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HANDLE_KEY_H
# define HANDLE_KEY_H

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
	INPUT_COUNT
}	t_input;

int	handle_close(void *param);
int	handle_key(int keycode, void *param);
int	handle_key_release(int keycode, void *param);
int	handle_focus_out(void *param);

#endif
