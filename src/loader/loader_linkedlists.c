/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loader_linkedlists.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abazzoun <abazzoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/20 13:39:06 by abazzoun          #+#    #+#             */
/*   Updated: 2026/09/20 13:47:27 by abazzoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "loader_rt.h"
#include "libft.h"

t_shape	*shapell_to_shapea(t_shapell *shapell)
{
	t_shape		*shapea;
	t_nodell	*node;
	int			i;

	shapea = ft_calloc(sizeof(*shapea), lenll((t_nodell *)shapell));
	if (!shapea)
		return (NULL);
	i = 0;
	node = (t_nodell *)shapell;
	while (node)
	{
		shapea[i] = ((t_shapell *)node)->shape;
		++i;
		node = node->next;
	}
	return (shapea);
}

t_spotlight	*spotlightll_to_spotlighta(t_spotlightll *spotlightll)
{
	t_spotlight		*spotlighta;
	t_nodell		*node;
	int				i;

	spotlighta = ft_calloc(sizeof(*spotlighta),
			lenll((t_nodell *)spotlightll));
	if (!spotlighta)
		return (NULL);
	i = 0;
	node = (t_nodell *)spotlightll;
	while (node)
	{
		spotlighta[i] = ((t_spotlightll *)node)->spotlight;
		++i;
		node = node->next;
	}
	return (spotlighta);
}
