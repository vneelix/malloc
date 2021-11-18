/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vneelix <vneelix@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 23:36:37 by vneelix           #+#    #+#             */
/*   Updated: 2021/11/18 22:47:27 by vneelix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

static void	release_unrestricted_area(t_unrestr_area *area)
{
	size_t	size;

	while (area->size != 0)
	{
		munmap(area->table[area->size - 1].ptr,
			area->table[area->size - 1].capacity);
		area->size--;
	}
	size = sizeof(t_unrestr_block) * area->capactiy + (getpagesize()
			- (sizeof(t_unrestr_block) * area->capactiy) % getpagesize());
	munmap(area->table, size);
	ft_memset(area, 0, sizeof(t_unrestr_area));
}

static void	release_restricted_area(t_area *area)
{
	size_t	i;
	size_t	size;

	i = 0;
	while (i != area->page_capacity)
	{
		if (area->page[i] != NULL)
			munmap(area->page[i], area->page[i]->sizeof_page);
		i++;
	}
	size = sizeof(void *) * area->page_capacity + (getpagesize()
			- (sizeof(void *) * area->page_capacity) % getpagesize());
	munmap(area->page, size);
	ft_memset(area, 0, sizeof(t_area));
}

void	release_allocator(void)
{
	if (g_area == NULL)
		return ;
	release_restricted_area(&g_area[TINY]);
	release_restricted_area(&g_area[SMALL]);
	release_unrestricted_area((t_unrestr_area *)(g_area + 2));
	munmap(g_area, getpagesize());
	g_area = NULL;
}

int	init_allocator(void)
{
	if (getpagesize() < 256)
		return (-1);
	g_area = create_private_mapping(NULL, getpagesize(), 0);
	if (g_area == NULL)
		return (-1);
	ft_memset(g_area, 0, getpagesize());
	if (unrestricted_area_append()
		|| area_append_page(TINY, TBE_SIZE, TNY)
		|| area_append_page(SMALL, TBE_SIZE, SML))
	{
		release_allocator();
		return (-1);
	}
	return (0);
}
