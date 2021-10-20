#include "ft_malloc.h"

node	*area = NULL;

void	*create_private_mapping(void *addr, size_t len, off_t offset) {
	void	*map = mmap(addr, len, PROT_READ
						| PROT_WRITE, MAP_PRIVATE
							| MAP_ANONYMOUS, 0, offset);
	if (map == MAP_FAILED)
		return (NULL);
	return (map);
}

int		area_init() {
	area = create_private_mapping(NULL, getpagesize(), 0);
	if (!area)
		return (-1);
	return (0);
}

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

	void		*content;
	void		*content_end;
}				t_page;

t_page	*init_page(__uint32_t table_size, size_t content_size) {
	/* align blocks */
	if (content_size % 8)
		content_size = 8 * (content_size / 8) + 8;

	/* calculating page size */
	size_t	page_size = sizeof(t_page)
							+ sizeof(t_block) * table_size
								+ table_size * content_size;
	page_size = page_size + (getpagesize() - page_size % getpagesize());

	/* allocate memory (mmap) */
	t_page	*page = create_private_mapping(NULL, page_size, 0);
	ft_memset(page, 0, page_size);

	/* markup page */
	page->table_size = 0;
	page->table_capacity = table_size;
	page->block_capacity = content_size;
	page->table = (void*)page + sizeof(t_page);
	page->content = (void*)page + sizeof(t_page)
						+ sizeof(t_block) * table_size;
	page->content_end = (void*)page + page_size;

	/* markup blocks */
	for (__uint32_t i = 0; i != table_size; i++)
		page->table[i].beg = page->content + i * content_size;

	return (page);
}

void	*ft_malloc(size_t size) {

	t_page	*p = (t_page*)init_page(32, 512);

	return (NULL);
}
