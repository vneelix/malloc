#include "ft_malloc.h"

char buff[128] = {0};

int	main() {
	void	*addr[38] = {NULL};

	for (int i = 0; i != 38; i++) {
		addr[i] = ft_malloc(432);
	}

	addr[11] = ft_realloc(addr[11], 11);
	addr[11] = ft_realloc(addr[11], TNY + 256);

	return 0;
}
