#include "malloc.h"

#define SZE 49

int	main() {

	void	*tny[SZE] = {NULL};
	void	*sml[SZE] = {NULL};
	void	*lre[SZE] = {NULL};

	for (int i = 0; i != SZE; i++) {
		tny[i] = malloc(TNY - TNY / 4);
		sml[i] = malloc(SML - SML / 4);
		lre[i] = malloc(SML * 1.5);
	}

	free(tny[12]);

	int brk = 0;
	for (int i = 0; i != SZE; i++) {
		free(tny[i]);
		if (i == 3) {
			tny[0] = malloc(123);
		}
	}

	return 0;
}
