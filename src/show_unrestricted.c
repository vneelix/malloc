/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_unrestricted.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vneelix <vneelix@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 02:18:14 by vneelix           #+#    #+#             */
/*   Updated: 2021/11/19 02:57:24 by vneelix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

static void	fill_header(t_unrestr_area *area, char *title, char **report)
{
	size_t	temp;
	char	buff[64];

	temp = ft_strlen(title);
	if (temp > 12)
		temp = 12;
	ft_memcpy(*report, title, temp);
	*report += temp + 12 - temp;
	ft_memcpy(*report, " : ", 3);
	*report += 3;
	ft_memset(buff, 0, 64);
	uint64_to_hex((__uint64_t)area->table[0].ptr, buff);
	temp = ft_strlen(buff);
	ft_memcpy(*report, buff, temp);
	*report += temp + 18 - temp;
	**report = '\n';
	*report += 1;
}

static void	fill_block(char **report, t_unrestr_block *b)
{
	size_t	temp;
	char	buff[64];

	uint64_to_hex((__uint64_t)b->ptr, buff);
	temp = ft_strlen(buff);
	ft_memcpy(*report, buff, temp);
	*report += temp + 18 - temp;
	ft_memcpy(*report, " - ", 3);
	*report += 3;
	uint64_to_hex((__uint64_t)b->ptr + b->size, buff);
	temp = ft_strlen(buff);
	ft_memcpy(*report, buff, temp);
	*report += temp + 18 - temp;
	ft_memcpy(*report, " : ", 3);
	*report += 3;
	uint64_to_dec(b->size, buff);
	temp = ft_strlen(buff);
	ft_memcpy(*report, buff, temp);
	*report += temp + 20 - temp;
	**report = '\n';
	*report += 1;
}

static void	fill_report(t_unrestr_area *area, char *title, char *report)
{
	size_t	i;

	fill_header(area, title, &report);
	i = 0;
	while (i != area->size)
	{
		fill_block(&report, &area->table[i]);
		i++;
	}
	*report = 0;
}

static size_t	calc_size(t_unrestr_area *area)
{
	size_t	size;

	size = (12 + 3 + 18 + 1)
		+ (18 + 3 + 18 + 3 + 20 + 1 + 5 + 1) * area->size;
	size = size + (getpagesize() - size % getpagesize());
	return (size);
}

void	show_alloc_mem_unrestricted(t_unrestr_area *area, char *title)
{
	size_t	size;
	char	*report;

	size = calc_size(area);
	report = create_private_mapping(NULL, size, 0);
	if (report == NULL)
		return ;
	ft_memset(report, ' ', size);
	fill_report(area, title, report);
	write(1, report, ft_strlen(report));
	munmap(report, size);
}
