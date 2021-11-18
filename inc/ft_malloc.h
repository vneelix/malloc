/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vneelix <vneelix@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 23:31:30 by vneelix           #+#    #+#             */
/*   Updated: 2021/11/19 02:25:23 by vneelix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MALLOC_H
# define FT_MALLOC_H

# include <unistd.h>
# include <sys/mman.h>

// block sizes
# define TNY 1024
# define SML 2048
# define TBE_SIZE 16

typedef struct s_block
{
	void	*beg;
	size_t	size;
}	t_block;

typedef struct s_page
{
	t_block		*table;
	__uint32_t	table_size;
	__uint32_t	table_capacity;

	size_t		block_capacity;

	__uint32_t	vacant_block_index;

	size_t		sizeof_page;

	void		*content;
	void		*content_end;
}	t_page;

typedef struct s_area
{
	t_page		**page;
	__uint32_t	page_size;
	__uint32_t	page_capacity;
}	t_area;

typedef struct s_unrestr_block
{
	size_t		size;
	size_t		capacity;

	void		*ptr;
}	t_unrestr_block;

typedef struct s_unrestr_area
{
	t_unrestr_block	*table;

	__uint32_t		size;
	__uint32_t		capactiy;

	__uint32_t		vacant_block_index;
}	t_unrestr_area;

typedef enum enum_area
{
	TINY,
	SMALL,
	LARGE
}	t_enum_area;

extern t_area	*g_area;

// allocator
void	free(void *ptr);
void	*malloc(size_t size);
void	*realloc(void *ptr, size_t size);

// allocator actions
void	release_allocator(void);
int		init_allocator(void);

// restricted area actions
int		area_append_page(t_enum_area type,
			__uint32_t table_size, __uint32_t content_size);
t_page	*init_page(__uint32_t table_size, size_t content_size);
void	*allocate_in_restriced_area(t_enum_area type,
			size_t content_size, size_t size);
void	sort_restricted_area(t_area *area);

// unrestricted area actions
int		unrestricted_area_append(void);
void	*allocate_in_unrestricted_area(size_t size);
void	sort_unrestricted_area(t_unrestr_area *area);

// extra
size_t	ft_strlen(const char *str);
void	*ft_memset(void *s, int c, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*create_private_mapping(void *addr, size_t len, off_t offset);
int		find_address(void *addr,
			t_enum_area *type, t_page **page, __uint32_t *block_index);
void	int64_stack_shift_up(__int64_t *stack, __uint32_t num);
void	int64_stack_shift_down(__int64_t *stack, __uint32_t num);
void	uint64_to_hex(__uint64_t num, char *buff);
void	uint64_to_dec(__uint64_t num, char *buff);

// show_mem
void	show_alloc_mem(void);
void	show_alloc_mem_restricted(t_area *area, char *title);
void	show_alloc_mem_unrestricted(t_unrestr_area *area, char *title);
#endif
