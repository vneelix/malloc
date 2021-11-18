/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_op.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vneelix <vneelix@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 22:43:52 by vneelix           #+#    #+#             */
/*   Updated: 2021/11/18 22:44:13 by vneelix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

void	int64_stack_shift_up(__int64_t *stack, __uint32_t num)
{
	if (!stack || !num)
		return ;
	if (num == 1)
	{
		if (*stack)
			*stack = 0;
		return ;
	}
	while (num - 1)
	{
		*((__uint128_t *)stack) >>= 64;
		num -= 1;
		if (num - 1)
			stack += 1;
	}
}

void	int64_stack_shift_down(__int64_t *stack, __uint32_t num)
{
	if (!stack || !num)
		return ;
	if (num == 1)
	{
		if (*stack)
			*stack = 0;
		return ;
	}
	stack += num - 2;
	while (num - 1)
	{
		*((__uint128_t *)stack) <<= 64;
		num -= 1;
		if (num - 1)
			stack -= 1;
	}
}
