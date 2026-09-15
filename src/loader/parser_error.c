/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abazzoun <abazzoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/10 00:15:57 by abazzoun          #+#    #+#             */
/*   Updated: 2026/09/11 09:48:32 by abazzoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	parser_error(int linenumber, char *message)
{
	ft_putendl_fd("Error", 2);
	ft_putstr_fd("Line ", 2);
	ft_putnbr_fd(linenumber, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(message, 2);
}

void	parser_error_token(int linenumber, char c)
{
	ft_putendl_fd("Error", 2);
	ft_putstr_fd("Line ", 2);
	ft_putnbr_fd(linenumber, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd("unexpected token '", 2);
	ft_putchar_fd(c, 2);
	ft_putendl_fd("'", 2);
}

void	loader_error(const char *message)
{
	ft_putendl_fd("Error", 2);
	ft_putendl_fd(message, 2);
}
