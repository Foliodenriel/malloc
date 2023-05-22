NAME		= libft.a

FLAGS		= -Wall -Wextra -Werror

INCLUDES	= -I./includes

# SRCS

SRCS_BASE	=	ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isprint.c ft_strlen.c ft_memset.c ft_bzero.c \
				ft_memcpy.c ft_memmove.c ft_strlcpy.c ft_strlcat.c ft_toupper.c ft_tolower.c ft_strchr.c \
				ft_strrchr.c ft_strncmp.c ft_memchr.c ft_memcmp.c ft_strnstr.c ft_atoi.c ft_calloc.c \
				ft_strdup.c ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c ft_putchar_fd.c ft_putstr_fd.c \
				ft_putendl_fd.c ft_itoa.c ft_strmapi.c ft_striteri.c ft_strtoupper.c ft_strtolower.c \
				ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c ft_lstdelone.c \
				ft_lstclear.c ft_lstiter.c ft_lstmap.c ft_itoa_base.c ft_uitoa_base.c ft_ulitoa_base.c \
				ft_strndup.c ft_has.c

SRCS_PRINTF	=	ft_printf.c ft_printf_fill.c ft_printf_flag.c ft_printf_compute.c

SRCS_GNL		=	get_next_line.c

# FULL SRCS / OBJS

SRCS			=	$(addprefix srcs/, $(SRCS_BASE)) \
				$(addprefix srcs/, $(addprefix ft_printf/, $(SRCS_PRINTF))) \
				$(addprefix srcs/, $(addprefix gnl/, $(SRCS_GNL))) \

OBJS			=	$(SRCS_BASE:.c=.o) \
				$(SRCS_PRINTF:.c=.o) \
				$(SRCS_GNL:.c=.o) \

CC			= gcc -g

all: $(OBJS)

$(OBJS):
	$(CC) -c $(INCLUDES) $(SRCS)
	ar -rcs $(NAME) $(OBJS)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: $(NAME) all clean fclean re