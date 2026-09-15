/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abazzoun <abazzoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/09 00:04:50 by abazzoun          #+#    #+#             */
/*   Updated: 2026/09/11 10:06:42 by abazzoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include "libft.h"
#include "parser.h"

void	unexpected(char c, int linenumber)
{
	if (c)
		parser_error_token(linenumber, c);
	else
		parser_error(linenumber, "unexpected end of input");
}

int	accept(char **s, char c)
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

int	expect(char **s, char c, int linenumber)
{
	if (accept(s, c))
		return (1);
	unexpected(**s, linenumber);
	return (0);
}

int	accept_identifier(char **s, const char *identifier)
{
	int	i;

	i = 0;
	while (identifier[i])
	{
		if (!(*s)[i] || (*s)[i] != identifier[i])
			return (0);
		i++;
	}
	*s = *s + i;
	return (1);
}
