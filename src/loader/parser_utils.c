/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abazzoun <abazzoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/09 00:04:50 by abazzoun          #+#    #+#             */
/*   Updated: 2026/09/09 17:19:55 by abazzoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include "libft.h"
#include "parser.h"

void    unexpected(char c, int linenumber)
{
	printf("Error\n");
	printf("rt_file: line %d: ", linenumber);
    if (c)
		printf("Unexpected token '%c'\n", c);
    else
		printf("Unexpected end of input\n");
}

int accept(char **s, char c)
{
	while (ft_isspace(**s))
		(*s)++;
    if (**s == c)
    {
		(*s)++;
		return (1);
    }
    return (0);
}

int expect(char **s, char c, int linenumber)
{
	if (accept(s, c))
		return (1);
	unexpected(**s, linenumber);
	return (0);
}
