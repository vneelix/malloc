#include "ft_malloc.h"

#define SZE 8

int	main() {

	void	*tny[SZE] = {NULL};
	void	*sml[SZE] = {NULL};
	void	*lre[SZE] = {NULL};

	srand(time(NULL));

	tny[0] = malloc(0);
	show_alloc_mem();

	tny[0] = realloc(tny[0], TNY + random() % TNY);
	show_alloc_mem();

	tny[0] = realloc(tny[0], SML + random() % SML);
	show_alloc_mem();

	release_allocator();

	return 0;
}
