#include "ft_malloc.h"

node	*area = NULL;

void	*create_private_mapping(void *addr, size_t len, off_t offset) {
	void	*map = mmap(addr, len, PROT_READ
						| PROT_WRITE, MAP_PRIVATE
							| MAP_ANONYMOUS, 0, offset);
	if (map == MAP_FAILED)
		return NULL;
	return map;
}

int		area_init() {
	area = create_private_mapping(NULL, getpagesize(), 0);
	if (!area)
		return -1;
	
	return 0;
}

void	*ft_malloc(size_t size) {
	int p_size = getpagesize();
	return create_private_mapping(NULL, p_size, 0);
}
