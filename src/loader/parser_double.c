/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_double.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abazzoun <abazzoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/09 16:54:00 by abazzoun          #+#    #+#             */
/*   Updated: 2026/09/09 17:05:30 by abazzoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int	parser_double(double *dst, char **s, int linenumber)
{
	char *end;

	(void)linenumber;
    *dst = strtod(*s, &end);
    if (end == *s)
        return 0;
    *s = end;
    return 1;
}
