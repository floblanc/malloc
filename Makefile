## PIMPED MAKEFILE ##

# COLORS #

# This is a minimal set of ANSI/VT100 color codes
_END		=	\e[0m
_BOLD		=	\e[1m
_UNDER		=	\e[4m
_REV		=	\e[7m

# Colors
_GREY		=	\e[30m
_RED		=	\e[31m
_GREEN		=	\e[32m
_YELLOW		=	\e[33m
_BLUE		=	\e[34m
_PURPLE		=	\e[35m
_CYAN		=	\e[36m
_WHITE		=	\e[37m

# Inverted, i.e. colored backgrounds
_IGREY		=	\e[40m
_IRED		=	\e[41m
_IGREEN		=	\e[42m
_IYELLOW	=	\e[43m
_IBLUE		=	\e[44m
_IPURPLE	=	\e[45m
_ICYAN		=	\e[46m
_IWHITE		=	\e[47m

# **************************************************************************** #

# NORMINETTE #

NORMINETTE	:=	$(shell which norminette)

ifeq (, $(shell which norminette))
	NORMINETTE := ${HOME}/.norminette/norminette.rb
endif

# HOSTTYPE #

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

## VARIABLES ##

# COMPILATION #

CC			=	gcc

# fPIC needed to compile on xubuntu because of mutex

CC_FLAGS	=	-Wall -Wextra -Werror -fPIC

# DELETE #

RM			=	rm -rf


# DIRECTORIES #

DIR_HEADERS		=	./includes/

DIR_SRCS		=	./srcs/

DIR_OBJS		=	./compiled_srcs/

SUB_DIRS		=	.

SUB_DIR_OBJS	=	$(SUB_DIRS:%=$(DIR_OBJS)%)


SRCS =				malloc.c					\
					free.c						\
					show_alloc_mem.c			\
					heap.c						\
					utils.c						\
					block.c						\
					realloc.c					\

# COMPILED_SOURCES #

OBJS		=	$(SRCS:%.c=$(DIR_OBJS)%.o)

NAME		=	libft_malloc.so

DYNAMIC_LIB =	libft_malloc_$(HOSTTYPE).so

# **************************************************************************** #

## RULES ##

all:			$(NAME)

# VARIABLES RULES #

$(NAME):		$(DYNAMIC_LIB)
				@ln -sf $(DYNAMIC_LIB) $(NAME)
				@printf "$(_GREEN) Library '$(DYNAMIC_LIB)' linked as '$(NAME)'. $(_END)✅\n"

$(DYNAMIC_LIB):	$(OBJS)
				@printf "\033[2K\r$(_GREEN) All files has been compiled into '$(DIR_OBJS)'. $(_END)✅\n"
				@$(CC) $(CC_FLAGS) $(OBJS) -shared -o $(DYNAMIC_LIB)
				@printf "$(_GREEN) Library '$(DYNAMIC_LIB)' created. $(_END)✅\n"

# COMPILED_SOURCES RULES #

$(OBJS):		| $(DIR_OBJS)

$(DIR_OBJS)%.o: $(DIR_SRCS)%.c
				@printf "\033[2K\r $(_YELLOW)Compiling $< $(_END)⌛"
				@$(CC) $(CC_FLAGS) -I $(DIR_HEADERS) -c $< -o $@

$(DIR_OBJS):	$(SUB_DIR_OBJS)

$(SUB_DIR_OBJS):
				@mkdir -p $(SUB_DIR_OBJS)

# OBLIGATORY PART #

clean:
				@$(RM) $(DIR_OBJS)
				@printf "$(_RED) '"$(DIR_OBJS)"' has been deleted. $(_END)🗑️\n"

fclean:			clean
				@$(RM) $(NAME)
				@printf "$(_RED) '"$(NAME)"' has been deleted. $(_END)🗑️\n"
				@$(RM) $(DYNAMIC_LIB)
				@printf "$(_RED) '"$(DYNAMIC_LIB)"' has been deleted. $(_END)🗑️\n"

norm:
				@$(NORMINETTE) $(DIR_SRCS)
				@$(NORMINETTE) $(DIR_HEADERS)

create:
	@gcc -o test0 tests/test0.c
	@gcc -o test1 tests/test1.c
	@gcc -o test2 tests/test2.c
	@gcc -o test3 tests/test3.c
	@gcc -o test4 tests/test4.c
	@gcc -o test5 tests/test5.c
	@gcc -o test6 tests/test6.c -L. -lft_malloc

re : fclean all create

.PHONY:			all clean fclean norm create re