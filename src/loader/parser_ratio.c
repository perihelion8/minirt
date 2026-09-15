/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_ratio.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abazzoun <abazzoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/10 10:41:44 by abazzoun          #+#    #+#             */
/*   Updated: 2026/09/11 09:52:11 by abazzoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	parser_ratio(double *dst, char **s, int linenumber)
{
	if (!parser_double(dst, s, linenumber))
		return (0);
	if (*dst < 0.0 || *dst > 1.0)
	{
		parser_error(linenumber, "ratio must be between 0 and 1.");
		return (0);
	}
	return (1);
}

int	parser_dimension(double *dst, char **s, int linenumber)
{
	if (!parser_double(dst, s, linenumber))
		return (0);
	if (*dst < 0.0)
	{
		parser_error(linenumber, "dimension must be positive.");
		return (0);
	}
	return (1);
}
