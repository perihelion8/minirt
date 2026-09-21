/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loader_rt.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abazzoun <abazzoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/19 00:49:16 by abazzoun          #+#    #+#             */
/*   Updated: 2026/09/20 13:46:30 by abazzoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOADER_RT_H
# define LOADER_RT_H

# include "scene.h"
# include "linkedlist.h"

typedef struct s_shapell
{
	t_nodell	nodell;
	t_shape		shape;
}	t_shapell;

typedef struct s_spotlightll
{
	t_nodell	nodell;
	t_spotlight	spotlight;
}	t_spotlightll;

typedef struct s_loader_rt
{
	int				fd;
	int				linenumber;
	t_shapell		*shapell;
	t_spotlightll	*spotlightll;
}	t_loader_rt;

t_shape		*shapell_to_shapea(t_shapell *shapell);
t_spotlight	*spotlightll_to_spotlighta(t_spotlightll *spotlightll);

#endif
