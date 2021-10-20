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

void	*ft_memset(void *s, int c, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memcpy_reverse(void *dest, const void *src, size_t n);

void	*ft_malloc(size_t size);

typedef	struct	node
{
	struct node	*prev;
	struct node	*next;
	void		*data;
	size_t		size;
	size_t		used;
}				node;

typedef struct	content_table
{
	size_t	size;
	void	*content;
}				content_table;

typedef struct	content
{
	void	*content;
}				content;


typedef	enum	enum_area {
	TINY,
	SMALL,
	LARGE
}				enum_area;

#endif
