/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vneelix <vneelix@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 22:30:59 by vneelix           #+#    #+#             */
/*   Updated: 2021/11/17 23:29:01 by vneelix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static __uint64_t	generate_qword(__uint8_t c)
{
	__uint64_t	qword;

	qword = 0;
	qword |= (unsigned long)c << 0;
	qword |= (unsigned long)c << 8;
	qword |= (unsigned long)c << 16;
	qword |= (unsigned long)c << 24;
	qword |= (unsigned long)c << 32;
	qword |= (unsigned long)c << 40;
	qword |= (unsigned long)c << 48;
	qword |= (unsigned long)c << 56;
	return (qword);
}

void	*ft_memset(void *s, int c, size_t n)
{
	size_t		i;
	void		*ret;
	__uint64_t	qword;

	i = 0;
	ret = s;
	qword = generate_qword((__uint8_t)c);
	while (i != n / sizeof(__uint64_t))
	{
		*(__uint64_t *)s = qword;
		s += sizeof(__uint64_t);
		i++;
	}
	i = 0;
	while (i != n % sizeof(__uint64_t))
	{
		*(__uint8_t *)s = (__uint8_t)c;
		s += sizeof(__uint8_t);
		i++;
	}
	return (ret);
}
