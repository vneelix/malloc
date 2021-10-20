#include "ft_malloc.h"

void	*ft_memcpy(void *dest, const void *src, size_t n) {
	void	*ret = dest;
	size_t	i = 0, c = n / sizeof(unsigned long);
	while (i != c) {
		*(unsigned long*)dest = *(unsigned long*)src;
		dest += sizeof(unsigned long);
		src += sizeof(unsigned long);
		i++;
	}
	i = 0, c = n % sizeof(unsigned long);
	while (i != c) {
		*(unsigned char*)dest = *(unsigned char*)src;
		dest += sizeof(unsigned char);
		src += sizeof(unsigned char);
		i++;
	}
	return ret;
}

void	*ft_memcpy_reverse(void *dest, const void *src, size_t n) {
	void	*ret = dest;
	size_t	i = 0, c = n / sizeof(unsigned long);
	dest += n;
	src += n;
	while (i != c) {
		dest -= sizeof(unsigned long);
		src -= sizeof(unsigned long);
		i++;
		*(unsigned long*)dest = *(unsigned long*)src;
	}
	i = 0, c = n % sizeof(unsigned long);
	while (i != c) {
		dest -= sizeof(unsigned char);
		src -= sizeof(unsigned char);
		i++;
		*(unsigned char*)dest = *(unsigned char*)src;
	}
	return ret;
}
