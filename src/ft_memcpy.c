/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vneelix <vneelix@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 22:40:59 by vneelix           #+#    #+#             */
/*   Updated: 2021/11/17 23:19:36 by vneelix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;
	void	*ret;

	i = 0;
	ret = dest;
	while (i != n / sizeof(__uint64_t))
	{
		*(__uint64_t *)dest = *(__uint64_t *)src;
		dest += sizeof(__uint64_t);
		src += sizeof(__uint64_t);
		i++;
	}
	i = 0;
	while (i != n % sizeof(__uint64_t))
	{
		*(__uint8_t *)dest = *(__uint8_t *)src;
		dest += sizeof(__uint8_t);
		src += sizeof(__uint8_t);
		i++;
	}
	return (ret);
}
