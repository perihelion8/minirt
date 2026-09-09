/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_int.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abazzoun <abazzoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/09 16:54:33 by abazzoun          #+#    #+#             */
/*   Updated: 2026/09/09 19:57:04 by abazzoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <errno.h>

int parser_int(int *dst, char **s, int linenumber)
{
    char    *end;
    long    value;

    (void)linenumber;

    if (!dst || !s || !*s)
        return (0);

    errno = 0;
    value = strtol(*s, &end, 10);

    if (*s == end)
        return (0);

    if (errno == ERANGE || value < INT_MIN || value > INT_MAX)
        return (0);

    *dst = (int)value;
    *s = end;

    return (1);
}
