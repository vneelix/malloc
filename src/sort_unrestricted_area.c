/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_unrestricted_area.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vneelix <vneelix@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 23:33:08 by vneelix           #+#    #+#             */
/*   Updated: 2021/11/18 23:49:20 by vneelix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

static void	bubble_iteration(t_unrestr_area *area, __uint32_t iter)
{
	__uint32_t		i;
	t_unrestr_block	block;

	i = 0;
	while (i != area->size - iter - 1)
	{
		if ((__uint64_t)area->table[i].ptr
			> (__uint64_t)area->table[i + 1].ptr)
		{
			block = area->table[i];
			area->table[i] = area->table[i + 1];
			area->table[i + 1] = block;
		}
		i++;
	}
}

void	sort_unrestricted_area(t_unrestr_area *area)
{
	__uint32_t	i;

	i = 0;
	while (i != area->size)
	{
		bubble_iteration(area, i);
		i++;
	}
}
