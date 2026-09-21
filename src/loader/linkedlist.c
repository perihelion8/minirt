/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linkedlist.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abazzoun <abazzoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/14 13:34:59 by abazzoun          #+#    #+#             */
/*   Updated: 2026/09/18 23:15:41 by abazzoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "libft.h"
#include "linkedlist.h"

t_nodell	*appendll(t_nodell **head, size_t node_size)
{
	t_nodell	*node;
	t_nodell	*last;

	if (!head || node_size < sizeof(*node))
		return (NULL);
	node = ft_calloc(1, node_size);
	if (!node)
		return (perror("Error\nappendll"), NULL);
	if (!*head)
		*head = node;
	else
	{
		last = *head;
		while (last->next)
			last = last->next;
		last->next = node;
	}
	return (node);
}

void	destroyll(t_nodell *head)
{
	t_nodell	*next;

	while (head)
	{
		next = head->next;
		free(head);
		head = next;
	}
}

size_t	lenll(t_nodell *head)
{
	size_t	len;

	len = 0;
	while (head)
	{
		++len;
		head = head->next;
	}
	return (len);
}
