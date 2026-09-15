/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_transforms.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abazzoun <abazzoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/11 17:35:33 by abazzoun          #+#    #+#             */
/*   Updated: 2026/09/11 17:57:33 by abazzoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CYLINDER_TRANSFORMS_H
# define CYLINDER_TRANSFORMS_H

# include "scene/cylinder.h"
# include "renderer_ray.h"

t_ray	cy_raytorel(t_ray ray, const t_cylinder *cylinder);
t_vec3	cy_pointtoabs(const t_cylinder *cylinder, t_vec3 rel);

#endif
