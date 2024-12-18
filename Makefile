.PHONY		: 	all clean fclean re

CC			=	gcc
CFLAGS		= 	-Wall -Wextra -Werror

NAME		=	libgnl.a

INCLUDE		=	include
SRC_DIR		=	src/
OBJ_DIR		=	obj/

SRC_FILES	= 	get_next_line

SRC 		= 	$(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_FILES)))
OBJ 		= 	$(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_FILES)))

RM			=	rm -rf
LIBC		=	ar rc
LIBR		= 	ranlib

all		: $(NAME)

$(NAME)	: $(OBJ_DIR) $(OBJ) $(INCLUDE)/get_next_line.h $(INCLUDE)/libft.h
		$(LIBC) $(NAME) $(OBJ)
		$(LIBR) $(NAME)

$(OBJ_DIR)	:
			mkdir $(OBJ_DIR)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
		$(CC) $(CFLAGS) -I $(INCLUDE) -c $< -o $@

clean	:
		$(RM) $(OBJ_DIR)

fclean	: clean
		$(RM) $(NAME)

re		: fclean all