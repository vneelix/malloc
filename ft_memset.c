#include "ft_malloc.h"

void	*ft_memset(void *s, int c, size_t n) {
	void	*ret = s;
	size_t	i = 0, j = n / sizeof(unsigned long);
	unsigned long qword = c;
	qword |= (unsigned long)c << 8;
	qword |= (unsigned long)c << 16;
	qword |= (unsigned long)c << 24;
	qword |= (unsigned long)c << 32;
	qword |= (unsigned long)c << 40;
	qword |= (unsigned long)c << 48;
	qword |= (unsigned long)c << 56;
	while (i != j) {
		*(unsigned long*)s = qword;
		s += sizeof(unsigned long);
		i++;
	}
	i = 0, j = n % sizeof(unsigned long);
	while (i != j) {
		*(unsigned char*)s = c;
		s += sizeof(unsigned char);
		i++;
	}
	return ret;
}
