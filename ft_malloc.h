#ifndef FT_MALLOC_H
#define FT_MALLOC_H

#include <unistd.h>
#include <sys/mman.h>

#ifndef size_t
typedef unsigned long size_t;
#endif

#ifndef NULL
#define NULL (void*)0
#endif

#define	TNY 512
#define SML 1024

void	*ft_memset(void *s, int c, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memcpy_reverse(void *dest, const void *src, size_t n);

void	*ft_malloc(size_t size);
void	*ft_realloc(void *addr, size_t size);

typedef struct	s_block
{
	void	*beg;
	size_t	size;
}				t_block;

typedef	struct	s_page
{
	t_block		*table;
	__uint32_t	table_size;
	__uint32_t	table_capacity;

	size_t		block_capacity;

	__uint32_t	vacant_block_index;

	size_t		sizeof_page;

	void		*content;
	void		*content_end;
}				t_page;

typedef	struct	s_area
{
	t_page		**page;
	__uint32_t	page_size;
	__uint32_t	page_capacity;
}				t_area;

typedef	enum	enum_area {
	TINY,
	SMALL,
	LARGE
}				enum_area;

void	ft_free(void *addr);

#endif
