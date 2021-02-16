ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

# Executable name
NAME				=	libft_malloc.so

# Compilation mode
WALL				=	yes
WEXTRA				=	yes
WERROR				=	yes
WEVERYTHING			=	no

FSANITIZE			=	no
DEBUG				=	yes
O2					=	no

ifeq ($(UNAME), Linux)
	CC					:=	gcc -lm -fPIC
else
	CC					:=	gcc -fPIC
endif
GEN					:=	"Generation in mode"

ifeq ($(WALL), yes)
	CC				:=	$(CC) -Wall
	GEN				:=	$(GEN) all
endif

ifeq ($(WEXTRA), yes)
	CC				:=	$(CC) -Wextra
	GEN				:=	$(GEN) extra
endif

ifeq ($(WERROR), yes)
	CC				:=	$(CC) -Werror
	GEN				:=	$(GEN) error
endif

ifeq ($(WEVERYTHING), yes)
	CC				:=	$(CC) -Weverything
	GEN				:=	$(GEN) all
endif

ifeq ($(FSANITIZE), yes)
	CC				:=	$(CC) -fsanitize=address
	GEN				:=	$(GEN) sanitize
endif

ifeq ($(DEBUG), yes)
	CC				:=	$(CC) -g3
	GEN				:=	$(GEN) debug
endif

ifeq ($(O2),yes)
	CC				:=	$(CC) -O2
	GEN				:=	$(GEN) O2
endif

ifeq ($(GEN), "Generation in mode")
	GEN				:=	$(GEN) no flags
endif

# Text format
_DEF				=	$'\033[0m
_END				=	$'\033[0m
_GRAS				=	$'\033[1m
_SOUL				=	$'\033[4m
_CLIG				=	$'\033[5m
_SURL				=	$'\033[7m

# Colors
_BLACK				=	$'\033[30m
_RED				=	$'\033[31m
_GREEN				=	$'\033[32m
_YELLOW				=	$'\033[33m
_BLUE				=	$'\033[34m
_PURPLE				=	$'\033[35m
_CYAN				=	$'\033[36m
_GREY				=	$'\033[37m

# Background
_IBLACK				=	$'\033[40m
_IRED				=	$'\033[41m
_IGREEN				=	$'\033[42m
_IYELLOW			=	$'\033[43m
_IBLUE				=	$'\033[44m
_IPURPLE			=	$'\033[45m
_ICYAN				=	$'\033[46m
_IGREY				=	$'\033[47m

SRC_NAME =			malloc.c					\
					free.c						\
					show_alloc_mem.c			\
					heap.c						\
					utils.c						\
					block.c						\
					# realloc.c					\

SRC_PATH =			./srcs/

OBJ_PATH =			./obj/

INC_PATH =			./include/

INC_NAME =			malloc.h					\

INC = $(addprefix $(INC_PATH), $(INC_NAME))
SRC = $(addprefix $(SRC_PATH), $(SRC_NAME))
OBJ = $(patsubst $(SRC_PATH)%.c, $(OBJ_PATH)%.o, $(SRC))

DYNAMIC_LIB =	libft_malloc_$(HOSTTYPE).so

.PHONY :	all clean fclean re create

all: $(NAME)

$(NAME) : $(DYNAMIC_LIB)
			@ln -sf $(DYNAMIC_LIB) $(NAME)

$(DYNAMIC_LIB) : $(OBJ)
		@$(CC) $(CC_FLAGS) $(OBJ) -shared -o $(DYNAMIC_LIB)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c $(INCLUDE)
	@mkdir -p $(OBJ_PATH)
	@$(CC) -I $(INC_PATH) -c $< -o $@

clean:
	@rm -rf $(OBJ_PATH) 2> /dev/null || true
	@rm -rf $(DYNAMIC_LIB) 2> /dev/null || true

fclean: clean
	@rm -f $(NAME)
	@rm -f test* 2> /dev/null || true

re : fclean all create

create:
	@gcc -o test0 tests/test0.c
	@gcc -o test1 tests/test1.c
	@gcc -o test2 tests/test2.c
	@gcc -o test3 tests/test3.c
	@gcc -o test4 tests/test4.c
	@gcc -o test5 tests/test5.c
	@gcc -o test6 tests/test6.c -L. -lft_malloc
