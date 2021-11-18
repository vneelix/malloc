/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vneelix <vneelix@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 22:19:47 by vneelix           #+#    #+#             */
/*   Updated: 2021/11/19 02:31:34 by vneelix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

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
}
