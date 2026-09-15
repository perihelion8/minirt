/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_color.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abazzoun <abazzoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/09 00:04:25 by abazzoun          #+#    #+#             */
/*   Updated: 2026/09/11 09:51:58 by abazzoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	parser_color(t_color *color, char **s, int linenumber)
{
	if (!parser_int(&color->r, s, linenumber))
		return (0);
	if (!expect(s, ',', linenumber))
		return (0);
	if (!parser_int(&color->g, s, linenumber))
		return (0);
	if (!expect(s, ',', linenumber))
		return (0);
	if (!parser_int(&color->b, s, linenumber))
		return (0);
	if (!color_isvalid(*color))
	{
		parser_error(linenumber, "color components must be between 0 and 255.");
		return (0);
	}
	return (1);
}
