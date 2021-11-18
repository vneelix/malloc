/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_restricted_area.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vneelix <vneelix@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 23:31:00 by vneelix           #+#    #+#             */
/*   Updated: 2021/11/18 23:32:40 by vneelix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

static void	bubble_iteration(t_area *area, __uint32_t iter)
{
	__uint32_t	i;
	t_page		*page;

	i = 0;
	while (i != area->page_size - iter - 1)
	{
		if ((__uint64_t)area->page[i]->content
			> (__uint64_t)area->page[i + 1]->content)
		{
			page = area->page[i];
			area->page[i] = area->page[i + 1];
			area->page[i + 1] = page;
		}
		i++;
	}
}

void	sort_restricted_area(t_area *area)
{
	__uint32_t	i;

	i = 0;
	while (i != area->page_size - 1)
	{
		bubble_iteration(area, i);
		i++;
	}
}
