/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vneelix <vneelix@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 22:19:47 by vneelix           #+#    #+#             */
/*   Updated: 2021/11/19 03:14:11 by vneelix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

static size_t	total_unrestricted(t_unrestr_area *area)
{
	size_t	i;
	size_t	size;

	size = 0;
	i = 0;
	while (i != area->size)
	{
		size += area->table[i].size;
		i++;
	}
	return (size);
}

static size_t	total_restricted(t_area *area)
{
	size_t	i;
	size_t	j;
	size_t	size;

	size = 0;
	i = 0;
	while (i != area->page_size)
	{
		j = 0;
		while (j != area->page[i]->table_size)
		{
			size += area->page[i]->table[j].size;
			j++;
		}
		i++;
	}
	return (size);
}

static void	print_total(void)
{
	char	buff[35];
	char	number[64];

	ft_memset(number, 0, 20);
	ft_memset(buff, ' ', sizeof(buff));
	ft_memcpy(buff, "Total : ", 8);
	uint64_to_dec(total_restricted(&g_area[TINY])
		+ total_restricted(&g_area[SMALL])
		+ total_unrestricted((t_unrestr_area *)(g_area + 2)), number);
	ft_memcpy(buff + 8, number, ft_strlen(number));
	buff[sizeof(buff) - 2] = '\n';
	buff[sizeof(buff) - 1] = 0;
	write(1, buff, sizeof(buff));
}

void	show_alloc_mem(void)
{
	if (g_area == NULL)
		return ;
	sort_restricted_area(&g_area[TINY]);
	sort_restricted_area(&g_area[SMALL]);
	sort_unrestricted_area((t_unrestr_area *)(g_area + 2));
	show_alloc_mem_restricted(&g_area[TINY], "TINY");
	show_alloc_mem_restricted(&g_area[SMALL], "SMALL");
	show_alloc_mem_unrestricted((t_unrestr_area *)(g_area + 2), "LARGE");
	print_total();
}
