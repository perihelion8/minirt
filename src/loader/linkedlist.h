/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linkedlist.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abazzoun <abazzoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/14 13:51:18 by abazzoun          #+#    #+#             */
/*   Updated: 2026/09/20 12:47:10 by abazzoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LINKEDLIST_H
# define LINKEDLIST_H

# include <stddef.h>

typedef struct s_nodell
{
	struct s_nodell	*next;
}	t_nodell;

t_nodell	*appendll(t_nodell **head, size_t node_size);
void		destroyll(t_nodell *head);
size_t		lenll(t_nodell *head);

#endif
