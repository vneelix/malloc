/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vneelix <vneelix@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 22:07:43 by vneelix           #+#    #+#             */
/*   Updated: 2021/11/18 01:38:22 by vneelix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static void	*realloc_unrestricted(void *addr,
				size_t size, t_unrestr_block *block)
{
	void	*ptr;
	size_t	aligned_size;

	if (size <= block->capacity)
	{
		block->size = size;
		return (addr);
	}
	aligned_size = size + (getpagesize() - size % getpagesize());
	ptr = create_private_mapping(addr, aligned_size, 0);
	if (ptr == NULL)
		return (NULL);
	if (ptr == addr)
		return (addr);
	ft_memcpy(ptr, addr, block->size);
	munmap(block->ptr, block->capacity);
	block->capacity = aligned_size;
	block->size = size;
	block->ptr = ptr;
	return (ptr);
}

static void	*realloc_restricted(void *addr, size_t size,
							t_page *page, __uint32_t block_index)
{
	void	*ptr;

	if (size <= page->block_capacity)
	{
		page->table[block_index].size = size;
		return (addr);
	}
	if (size <= SML)
		ptr = allocate_in_restriced_area(SMALL, SML, size);
	else
		ptr = allocate_in_unrestricted_area(size);
	if (ptr == NULL)
		return (NULL);
	ft_memcpy(ptr, addr, page->table[block_index].size);
	free(addr);
	return (ptr);
}

void	*realloc(void *ptr, size_t size)
{
	t_enum_area	type;
	t_page		*page;
	__uint32_t	block_index;

	if (ptr == NULL || g_area == NULL)
		return (malloc(size));
	if (find_address(ptr, &type, &page, &block_index) == -1)
		return (NULL);
	if (type != LARGE)
		return (realloc_restricted(ptr, size, page, block_index));
	return (realloc_unrestricted(ptr, size, (t_unrestr_block *)page));
}
