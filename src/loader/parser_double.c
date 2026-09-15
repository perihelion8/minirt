/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_double.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abazzoun <abazzoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/09 02:57:18 by abazzoun          #+#    #+#             */
/*   Updated: 2026/09/12 16:10:46 by abazzoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser.h"
#include <math.h>

static void	calculate_digit(char c, double *result, int *length)
{
	if (*length)
	{
		*result = *result + ((c - '0') / pow(10, *length));
		*length += 1;
	}
	else
		*result = (*result * 10) + (c - '0');
}

static double	ft_atod(char *str)
{
	double	result;
	int		sign;
	int		length;

	sign = 1;
	result = 0.0;
	length = 0;
	while (ft_isspace(*str))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (ft_isdigit(*str) || (*str == '.' && !length))
	{
		if (*str == '.')
			length = 1;
		else
			calculate_digit(*str, &result, &length);
		str++;
	}
	return (result * sign);
}

static int	validate_decimal_part(char **str)
{
	while (**str && **str != ',' && !ft_isspace(**str))
	{
		if (!ft_isdigit(**str))
			return (0);
		(*str)++;
	}
	return (1);
}

static int	is_double(char **str)
{
	char	*start;

	while (ft_isspace(**str))
		(*str)++;
	if (**str == '-' || **str == '+')
		(*str)++;
	start = *str;
	while (ft_isdigit(**str))
		(*str)++;
	if (start == *str)
		return (0);
	if (**str == '.')
	{
		(*str)++;
		return (validate_decimal_part(str));
	}
	return (!**str || **str == ',' || ft_isspace(**str));
}

int	parser_double(double *dst, char **s, int linenumber)
{
	char	*start;

	if (!dst || !s || !*s)
		return (0);
	start = *s;
	if (!is_double(s))
	{
		unexpected(**s, linenumber);
		return (0);
	}
	*dst = ft_atod(start);
	if (!isfinite(*dst))
		return (parser_error(linenumber, "number must be finite."), 0);
	return (1);
}
