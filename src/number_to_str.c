/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   number_to_str.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vneelix <vneelix@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 01:02:30 by vneelix           #+#    #+#             */
/*   Updated: 2021/11/19 01:03:43 by vneelix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

static int	count_digit(__uint64_t n)
{
	int	count;

	count = 0;
	while (n != 0)
	{
		n = n / 10;
		++count;
	}
	return (count);
}

void	uint64_to_dec(__uint64_t num, char *buff)
{
	int	i;
	int	count;

	i = 0;
	count = count_digit(num);
	ft_memset(buff, 0, 20);
	buff[0] = '0';
	while (i != count)
	{
		buff[count - i - 1] = num % 10 + '0';
		num /= 10;
		i++;
	}
}

void	uint64_to_hex(__uint64_t num, char *buff)
{
	size_t	i;
	size_t	count;

	ft_memset(buff, 0, 18);
	ft_memcpy(buff, "0x0", 3);
	count = 16;
	while (count != 1
		&& ((num >> (4 * (count - 1)) & (__uint64_t)0xf) == 0))
		count--;
	i = 0;
	while (i != count)
	{
		buff[2 + count - i - 1] = '0'
			+ ((num >> (4 * i)) & (__uint64_t)0xf) % 10
			+ ('A' - '0') * (((num >> (4 * i)) & (__uint64_t)0xf) / 10);
		i++;
	}
}
