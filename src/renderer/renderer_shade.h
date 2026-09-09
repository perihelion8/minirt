/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer_shade.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abazzoun <abazzoun@student.42beirut.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/18 21:53:57 by abazzoun          #+#    #+#             */
/*   Updated: 2026/09/08 16:01:43 by abazzoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDERER_SHADE_H
# define RENDERER_SHADE_H

# include "scene.h"
# include "renderer_intersection.h"

# define RENDER_SHADOW_BIAS 1e-4

t_color	shade_hit(t_scene *scene, const t_hit *hit);

#endif
