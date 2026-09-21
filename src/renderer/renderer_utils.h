/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer_utils.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abazzoun <abazzoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/11 17:35:33 by abazzoun          #+#    #+#             */
/*   Updated: 2026/09/18 03:07:06 by abazzoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDERER_UTILS_H
# define RENDERER_UTILS_H

# include "scene/cylinder.h"
# include "scene/hyperboloid.h"
# include "renderer_ray.h"

t_vec3	cy_point_to_abs(const t_cylinder *cy, t_vec3 rel_point);
t_ray	cy_ray_to_rel(t_ray *ray, const t_cylinder *cy);
t_ray	hb_ray_to_rel(t_ray *ray, const t_hyperboloid *hb);
t_vec3	hb_point_to_abs(const t_hyperboloid *hb, t_vec3 rel_point);

#endif
