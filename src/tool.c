/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vneelix <vneelix@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 22:27:39 by vneelix           #+#    #+#             */
/*   Updated: 2021/11/18 23:18:28 by vneelix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

static int	find_into_unrestr(void *addr, t_unrestr_area *area,
								t_page **page, __uint32_t *block_index)
{
	__uint32_t	block_idx;

	block_idx = 0;
	while (block_idx != area->size)
	{
		if (addr == area->table[block_idx].ptr)
		{
			*block_index = block_idx;
			*page = (t_page *)(area->table + block_idx);
			return (0);
		}
		block_idx++;
	}
	return (-1);
}

static int	find_into_restr(void *addr, t_area *area,
								t_page **page, __uint32_t *block_index)
{
	__uint32_t	page_idx;
	__uint32_t	block_idx;

	page_idx = 0;
	while (page_idx != area->page_size)
	{
		if (addr >= area->page[page_idx]->content
			&& addr <= area->page[page_idx]->content_end)
		{
			block_idx = 0;
			while (block_idx != area->page[page_idx]->table_size)
			{
				if (addr == area->page[page_idx]->table[block_idx].beg)
				{
					*block_index = block_idx;
					*page = area->page[page_idx];
					return (0);
				}
				block_idx++;
			}
		}
		page_idx++;
	}
	return (-1);
}

int	find_address(void *addr,
		t_enum_area *type, t_page **page, __uint32_t *block_index)
{
	__uint32_t	area_idx;

	area_idx = 0;
	while (area_idx != 2)
	{
		if (find_into_restr(addr, &g_area[area_idx], page, block_index) == 0)
		{
			*type = (t_enum_area)area_idx;
			return (0);
		}
		area_idx++;
	}
	if (find_into_unrestr(addr,
			(t_unrestr_area *)(g_area + 2), page, block_index) == 0)
	{
		*type = LARGE;
		return (0);
	}
	return (-1);
}

void	*create_private_mapping(void *addr, size_t len, off_t offset)
{
	void	*ptr;

	ptr = mmap(addr, len, PROT_READ
			| PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, 0, offset);
	if (ptr == MAP_FAILED)
		return (NULL);
	return (ptr);
}
