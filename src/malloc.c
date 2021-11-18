/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vneelix <vneelix@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 23:12:00 by vneelix           #+#    #+#             */
/*   Updated: 2021/11/19 02:45:02 by vneelix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

t_area	*g_area = NULL;

static void	free_restricted(t_enum_area type,
				t_page *page, __uint32_t block_index)
{
	__uint32_t	i;

	if (page->table_size != 0)
		page->table_size--;
	if (g_area[type].page_size != 1 && page->table_size == 0)
	{
		i = 0;
		while (g_area[type].page[i] != page)
			i++;
		g_area[type].page[i] = NULL;
		int64_stack_shift_up(g_area[type].page + i, g_area[type].page_size - i);
		g_area[type].page_size--;
		munmap(page, page->sizeof_page);
		return ;
	}
	page->table[block_index].size = 0;
	if (block_index < page->vacant_block_index)
		page->vacant_block_index = block_index;
}

void	free(void *ptr)
{
	t_enum_area		type;
	t_page			*page;
	__uint32_t		block_index;
	t_unrestr_area	*unrestricted_area;
	t_unrestr_block	*unrestricted_block;

	if (g_area == NULL)
		return ;
	if (find_address(ptr, &type, &page, &block_index) == -1)
		return ;
	if (type != LARGE)
		free_restricted(type, page, block_index);
	else
	{
		unrestricted_area = (t_unrestr_area *)(g_area + 2);
		unrestricted_block = (t_unrestr_block *)page;
		munmap(ptr, unrestricted_block->capacity);
		ft_memset(unrestricted_block, 0, sizeof(t_unrestr_block));
		if (block_index < unrestricted_area->vacant_block_index)
			unrestricted_area->vacant_block_index = block_index;
		unrestricted_area->size--;
	}
}

void	*malloc(size_t size)
{
	if (g_area == NULL)
		if (init_allocator() != 0)
			return (NULL);
	if (size == 0)
		return (NULL);
	if (size <= TNY)
		return (allocate_in_restriced_area(TINY, TNY, size));
	else if (size <= SML)
		return (allocate_in_restriced_area(SMALL, SML, size));
	else
		return (allocate_in_unrestricted_area(size));
}
