/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vneelix <vneelix@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 01:06:21 by vneelix           #+#    #+#             */
/*   Updated: 2021/11/19 01:28:25 by vneelix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

size_t	ft_strlen(const char *str)
{
	const char	*p;

	p = str;
	while (*str)
		str++;
	return ((size_t)(str - p));
}
