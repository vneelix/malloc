############################## HOST ############################################

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME = libft_malloc.so

HOSTLIB = libft_malloc_$(HOSTTYPE).so

SRC =	allocator_restricted.c  init.c     restricted_area_op.c		\
		ft_memcpy.c             malloc.c   tool.c					\
		ft_memset.c             realloc.c  unrestricted_area_op.c	\

SRCDIR = src/

OBJDIR = obj/

CFLAGS = -O2 -Wall -Wextra -Werror -fPIC

LDFLAGS = -shared

DEP = inc/malloc.h

CC = clang

OBJ = $(addprefix $(OBJDIR), $(SRC:.c=.o))

INCL = -Iinc

all: ${NAME}

${NAME}: ${HOSTLIB}
	ln -fs ${HOSTLIB} ${NAME}

${HOSTLIB}: ${OBJ} ${DEP}
	${CC} ${LDFLAGS} ${INCL} -o $@ ${OBJ}

${OBJDIR}%.o: ${SRCDIR}%.c ${DEP}
	@/bin/mkdir -p ${OBJDIR}
	${CC} ${CFLAGS} ${INCL} -c $< -o $@

clean:
	/bin/rm -Rf ${OBJDIR}

fclean: clean
	/bin/rm -f ${NAME}
	/bin/rm -f ${HOSTLIB}

re: fclean all

.PHONY: all clean fclean re test test