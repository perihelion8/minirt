/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_key.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abazzoun <abazzoun@student.42beirut.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/18 21:56:46 by abazzoun          #+#    #+#             */
/*   Updated: 2026/08/18 21:56:47 by abazzoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "handle_key.h"
#include "../action/action.h"

int	handle_key(int keycode, void *param)
{
	if (keycode == KEY_ESC)
		action_apply(param, ACTION_QUIT);
	else if (keycode == KEY_W)
		action_apply(param, ACTION_MOVE_FORWARD);
	else if (keycode == KEY_S)
		action_apply(param, ACTION_MOVE_BACKWARD);
	else if (keycode == KEY_A)
		action_apply(param, ACTION_ROTATE_RIGHT);
	else if (keycode == KEY_D)
		action_apply(param, ACTION_ROTATE_LEFT);
	return (0);
}
