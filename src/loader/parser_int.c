/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 parser_int.c										:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: abazzoun <abazzoun@student.42.fr>			+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2026/09/09 16:54:33 by abazzoun		   #+#	  #+#			  */
/*	 Updated: 2026/09/10 18:09:28 by abazzoun		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#include <limits.h>
#include "libft.h"
#include "parser.h"

int	is_int(char **str)
{
	char	*p;

	if (!str || !*str)
		return (0);
	p = *str;
	while (ft_isspace(*p))
		p++;
	if (*p == '+' || *p == '-')
		p++;
	if (!ft_isdigit(*p))
		return (0);
	while (ft_isdigit(*p))
		p++;
	if (*p && *p != ',' && !ft_isspace(*p))
		return (0);
	*str = p;
	return (1);
}

static int	convert_int(int *dst, char *s)
{
	int	value;
	int	sign;
	int	limit;

	while (ft_isspace(*s))
		s++;
	sign = 1;
	if (*s == '-')
		sign = -1;
	if (*s == '+' || *s == '-')
		s++;
	limit = -INT_MAX;
	if (sign == -1)
		limit = INT_MIN;
	value = 0;
	while (ft_isdigit(*s))
	{
		if (value < (limit + (*s - '0')) / 10)
			return (0);
		value = value * 10 - (*s++ - '0');
	}
	*dst = value;
	if (sign == 1)
		*dst = -value;
	return (1);
}

int	parser_int(int *dst, char **s, int linenumber)
{
	char	*start;
	char	*end;

	if (!dst || !s || !*s)
		return (0);
	start = *s;
	end = start;
	if (!is_int(&end) || !convert_int(dst, start))
	{
		parser_error(linenumber, "invalid int.");
		return (0);
	}
	*s = end;
	return (1);
}
