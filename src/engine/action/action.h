/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abazzoun <abazzoun@student.42beirut.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/18 21:57:09 by abazzoun          #+#    #+#             */
/*   Updated: 2026/08/18 22:03:25 by abazzoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ACTION_H
# define ACTION_H

typedef enum e_action
{
	ACTION_QUIT,
	ACTION_MOVE_FORWARD,
	ACTION_MOVE_BACKWARD,
	ACTION_ROTATE_RIGHT,
	ACTION_ROTATE_LEFT,
	ACTION_NONE
}	t_action;

void	action_apply(void *param, t_action action);

#endif
