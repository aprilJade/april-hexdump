NAME	=	april_hexdump

CC		=	gcc

FLAG	=	-Wall -Wextra -Werror

INCLUDE	=	-Iincludes/

SRC_DIR	=	src

OBJ_DIR	=	obj

SRCS	=	$(notdir $(wildcard $(SRC_DIR)/*.c))

OBJS	=	$(SRCS:.c=.o)

OBJECTS	=	$(patsubst %.o, $(OBJ_DIR)/%.o, $(OBJS))

TARGET	=	$(OBJ_DIR) $(NAME)

debug	:	FLAG += -g
debug	:	$(TARGET)

release	:	$(TARGET)

all		:	debug

clean	:	
	rm -rf $(OBJECTS)

fclean	:	clean
	rm -rf $(TARGET)

re		:	fclean all

$(OBJ_DIR)/%.o	: $(SRC_DIR)/%.c
	$(CC) $(FLAG) -c $< -o $@

$(OBJ_DIR)	:
	mkdir -p $(OBJ_DIR)

$(NAME)	:	$(OBJECTS)
	$(CC) $(OBJECTS) $(FLAG) -o $(NAME)

.PHONY	:	all clean fclean re debug release
