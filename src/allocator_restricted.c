/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocator_restricted.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vneelix <vneelix@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 00:33:38 by vneelix           #+#    #+#             */
/*   Updated: 2021/11/18 01:38:01 by vneelix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static t_page	*find_vacant_page(t_area *area)
{
	__uint32_t	i;

	i = 0;
	while (i != area->page_capacity)
	{
		if (area->page[i] != NULL
			&& area->page[i]->table_size != area->page[i]->table_capacity)
			return (area->page[i]);
		i++;
	}
	return (NULL);
}

void	*allocate_in_restriced_area(t_enum_area type,
									size_t content_size, size_t size)
{
	void	*ptr;
	t_page	*page;

	page = find_vacant_page(&g_area[type]);
	if (page == NULL)
	{
		if (area_append_page(type, TBE_SIZE, content_size) != 0)
			return (NULL);
		return (allocate_in_restriced_area(type, content_size, size));
	}
	page->table_size++;
	ptr = page->table[page->vacant_block_index].beg;
	page->table[page->vacant_block_index].size = size;
	while (page->vacant_block_index != page->table_capacity
		&& page->table[page->vacant_block_index].size != 0)
		page->vacant_block_index++;
	return (ptr);
}
