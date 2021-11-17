/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   restricted_area_op.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vneelix <vneelix@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 21:34:52 by vneelix           #+#    #+#             */
/*   Updated: 2021/11/18 02:05:35 by vneelix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static void	map_page(t_page *page)
{
	__uint32_t	i;

	i = 0;
	while (i != page->table_capacity)
	{
		page->table[i].beg = page->content + i * page->block_capacity;
		i++;
	}
}

t_page	*init_page(__uint32_t table_size, size_t content_size)
{
	t_page		*page;
	size_t		page_size;

	if (content_size % 8)
		content_size = 8 * (content_size / 8) + 8;
	page_size = sizeof(t_page)
		+ sizeof(t_block) * table_size + table_size * content_size;
	page_size = page_size + (getpagesize() - page_size % getpagesize());
	page = create_private_mapping(NULL, page_size, 0);
	if (page == NULL)
		return (NULL);
	ft_memset(page, 0, page_size);
	page->sizeof_page = page_size;
	page->table_capacity = table_size;
	page->block_capacity = content_size;
	page->table = (void *)page + sizeof(t_page);
	page->content = (void *)page
		+ sizeof(t_page) + sizeof(t_block) * table_size;
	page->content_end = (void *)page + page_size;
	map_page(page);
	return (page);
}

static int	realloc_area_storage(t_area *area, size_t storage_capacity)
{
	void	*ptr;
	size_t	size;
	size_t	new_capacity;

	new_capacity = area->page_capacity + storage_capacity;
	size = sizeof(t_page *) * new_capacity + (getpagesize()
			- (sizeof(t_page *) * new_capacity) % getpagesize());
	ptr = create_private_mapping(area->page, size, 0);
	if (ptr == NULL)
		return (-1);
	if (area->page != NULL && ptr != area->page)
	{
		ft_memcpy(ptr, area->page, area->page_size * sizeof(t_page *));
		size = sizeof(t_page *) * area->page_capacity + (getpagesize()
				- (sizeof(t_page *) * area->page_capacity) % getpagesize());
		munmap(area->page, size);
	}
	area->page_capacity = new_capacity;
	area->page = ptr;
	return (0);
}

int	area_append_page(t_enum_area type,
						__uint32_t table_size, __uint32_t content_size)
{
	t_area	*area;
	size_t	vacant_page_index;

	area = &g_area[type];
	if (area->page_size == area->page_capacity)
		if (realloc_area_storage(area, 32) == -1)
			return (-1);
	vacant_page_index = 0;
	while (area->page[vacant_page_index] != NULL)
		vacant_page_index++;
	area->page[vacant_page_index] = init_page(table_size, content_size);
	if (area->page[vacant_page_index] == NULL)
		return (-1);
	area->page_size++;
	return (0);
}
