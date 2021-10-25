#include "ft_malloc.h"

t_area	*area = NULL;

void	*create_private_mapping(void *addr, size_t len, off_t offset) {
	void	*map = mmap(addr, len, PROT_READ
						| PROT_WRITE, MAP_PRIVATE
							| MAP_ANONYMOUS, 0, offset);
	if (map == MAP_FAILED)
		return (NULL);
	return (map);
}

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
	page->sizeof_page = page_size;
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

int		area_append_page(enum_area type, __uint32_t table_size, __uint32_t content_size) {
	t_area *a = &area[type];

	/* realloc pages */
	if (a->page_size == a->page_capacity) {
		size_t	len = a->page_capacity * sizeof(void*) + getpagesize();
		void	*p = create_private_mapping(a->page, len, 0);

		if (p == NULL)
			return (-1);
		if (a->page != NULL && a->page != p)
			ft_memcpy(p, a->page, a->page_size * sizeof(t_page));
		
		a->page = p;
		a->page_capacity = len / sizeof(void*);
	}

	/* append new page to back*/
	a->page[a->page_size] = init_page(table_size, content_size);
	if (a->page[a->page_size] == NULL)
		return (-1);
	a->page_size++;

	return (0);
}

int		init_allocator(void) {
	if (getpagesize() < 256)
		return (-1);

	/* mmap array of areas */
	area = create_private_mapping(NULL, getpagesize(), 0);
	if (area == NULL)
		return (-1);
	ft_memset(area, 0, getpagesize());

	/* init tiny and small areas */
	if (area_append_page(TINY, 32, 512) != 0
			|| area_append_page(SMALL, 32, 1024) != 0)
		return (-1);

	return (0);
}

int		set_vacant_block(t_page *page) {
	for (__uint32_t i = page->vacant_block_index; i != page->table_capacity; i++) {
		t_block *block = page->table + i;
		if (block->size == 0) {
			page->vacant_block_index = i;
			return (0);
		}
	}
	page->vacant_block_index = page->table_capacity;
	return (-1);
}

void	*allocate_in_restriced_area(enum_area type, size_t content_size, size_t size) {
	t_area *a = &(area[type]);
	for (__uint32_t i = 0; i != a->page_size; i++) {
		t_page *page = a->page[i];
		if (page->table_size != page->table_capacity) {
			/* block -> [size, content_ptr] */
			t_block	*block = page->table + page->vacant_block_index;
			block->size = size;

			/* find next vacant block in current page */
			set_vacant_block(page);
			page->table_size++;

			/* return block content_ptr */
			return (block->beg);
		}
	}

	/* if all blocks in current page is full - append new page */
	if (area_append_page(type, 32, content_size) != 0)
		return (NULL);
	return (allocate_in_restriced_area(type, content_size, size));
}

int		find_address(void *addr, enum_area *type, t_page **page, __uint32_t *block_index) {
	/* check tiny and small */
	for (__uint32_t i = 0; i != 2; i++) {
		t_area *a = area + i;
		for (__uint32_t j = 0; j != a->page_size; j++) {
			t_page *p = a->page[j];
			if (addr >= p->content && addr <= p->content_end) {

				/* write area type, page and block_index */
				if (block_index != NULL) {
					for (__uint32_t k = 0; k != p->table_size; k++) {
						if (p->table[k].size == 0)
							break;
						if (p->table[k].beg == addr) {
							*type = i;
							*page = p;
							*block_index = k;
							return (0);
						}
					}
				}
			}
		}
	}
	return (-1);
}

void	*ft_realloc(void *addr, size_t size) {

	if (addr == NULL)
		return (ft_malloc(size));

	enum_area	type = 0;
	t_page		*page = NULL;
	__uint32_t	block_index = 0;

	if (find_address(addr, &type, &page, &block_index) != 0)
		return (NULL);

	if (size <= page->block_capacity) {
		page->table[block_index].size = size;
		return (page->table[block_index].beg);
	}

	if (type == TINY) {
		void *ptr = allocate_in_restriced_area(SMALL, SML, size);
		if (ptr == NULL)
			return (NULL);
		ft_memcpy(ptr, addr, page->table[block_index].size);
		ft_free(addr);
		return (ptr);
	}

	return (NULL);
}

void	ft_free(void *addr) {
	enum_area	type = 0;
	t_page		*page = NULL;
	__uint32_t	block_index = 0;

	if (find_address(addr, &type, &page, &block_index) != 0)
		return;

	/* make block vacant */
	page->table[block_index].size = 0;
	if (block_index < page->vacant_block_index)
		page->vacant_block_index = block_index;

	/* deleting page if necessary */
	if (page->table_size != 0)
		page->table_size--;
	if (area[type].page_size != 0 && page->table_size == 0) {
		area[type].page_size--;
		int ret = munmap(page, page->sizeof_page);
		ret -= 1;
	}

	return;
}

void	*ft_malloc(size_t size) {

	if (area == NULL)
		init_allocator();

	if (size <= TNY)
		return (allocate_in_restriced_area(TINY, TNY, size));
	else if (size <= SML)
		return (allocate_in_restriced_area(SMALL, SML, size));

	return (NULL);
}
