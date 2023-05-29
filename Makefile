ifeq ($(HOSTTYPE),)
	HOSTTYPE	= $(shell uname -m)_$(shell uname -s)
endif

NAME			= libft_malloc_$(HOSTTYPE).so

NAME_LINK		= libft_malloc.so

CC				= gcc

FLAGS			= -Wall -Wextra -Werror

INCLUDES		= -Iincludes/ -Ilibft/includes/

SRCS			= ft_malloc.c ft_allocate.c ft_alloc_helper.c ft_free.c ft_realloc.c

OBJS			= $(SRCS:.c=.o)

all: $(NAME)

$(NAME):
	@echo -n "Compiling library"
	@sleep 2
	@echo -n "\r20% - libft compiling"
	@make -C libft
	@echo -n "\r40% - compiling obj files"
	@$(CC) -c $(FLAGS) -fpic -pthread $(addprefix srcs/, $(SRCS)) $(INCLUDES)
	@echo -n "\r60% - creating dynamic library"
	@$(CC) -shared -o $(NAME) $(OBJS) libft/*.o
	@echo -n "\r80% - cleaning libft folder"
	@make fclean -C libft/
	@make clean
	@echo -n "\r99% - linking dynamic library"
	@ln -s $(NAME) $(NAME_LINK)
	@echo "\rComplete!"

test:
	$(CC) -g main.c -L . -lft_malloc $(INCLUDES)

thread:
	$(CC) -g main.c -L . -lft_malloc -pthread $(INCLUDES)


re: fclean all

clean:
	rm -f $(OBJS)

fclean: clean
	make fclean -C libft
	rm -f $(NAME) $(NAME_LINK)

.PHONY: $(NAME) all re fclean