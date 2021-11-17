/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unrestricted_area_op.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vneelix <vneelix@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 22:20:16 by vneelix           #+#    #+#             */
/*   Updated: 2021/11/18 02:04:59 by vneelix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static int	realloc_area_storage(t_unrestr_area *area, size_t storage_capacity)
{
	void	*ptr;
	size_t	size;
	size_t	new_capacity;

	new_capacity = area->capactiy + storage_capacity;
	size = sizeof(t_unrestr_block) * new_capacity + (getpagesize()
			- (sizeof(t_unrestr_block) * new_capacity) % getpagesize());
	ptr = create_private_mapping(area->table, size, 0);
	if (ptr == NULL)
		return (-1);
	if (area->table != NULL && ptr != area->table)
	{
		ft_memcpy(ptr, area->table, area->size * sizeof(t_unrestr_block));
		size = sizeof(t_unrestr_block) * area->capactiy + (getpagesize()
				- (sizeof(t_unrestr_block) * area->capactiy) % getpagesize());
		munmap(area->table, size);
	}
	area->capactiy = new_capacity;
	area->table = ptr;
	return (0);
}

int	unrestricted_area_append(void)
{
	t_unrestr_area	*area;

	area = (t_unrestr_area *)(g_area + 2);
	if (area->size == area->capactiy)
		if (realloc_area_storage(area, TBE_SIZE) == -1)
			return (-1);
	return (0);
}

void	*allocate_in_unrestricted_area(size_t size)
{
	void			*ptr;
	t_unrestr_area	*area;
	size_t			aligned_size;

	if (unrestricted_area_append() == -1)
		return (NULL);
	area = (t_unrestr_area *)(g_area + 2);
	aligned_size = size + (getpagesize() - size % getpagesize());
	ptr = create_private_mapping(NULL, aligned_size, 0);
	if (ptr == NULL)
		return (NULL);
	area->size++;
	area->table[area->vacant_block_index].ptr = ptr;
	area->table[area->vacant_block_index].size = size;
	area->table[area->vacant_block_index].capacity = aligned_size;
	while (area->vacant_block_index != area->capactiy
		&& area->table[area->vacant_block_index].size != 0)
		area->vacant_block_index++;
	return (ptr);
}
