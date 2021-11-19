#include "ft_malloc.h"

#define SZE 12

int	main() {

	void	*tny[SZE] = {NULL};
	void	*sml[SZE] = {NULL};
	void	*lre[SZE] = {NULL};

	for (int i = 0; i != SZE; i++) {
		tny[i] = malloc(TNY);
		sml[i] = malloc(SML);
		lre[i] = malloc(SML + 12);
	}
	show_alloc_mem();
	release_allocator();
	return 0;
}
