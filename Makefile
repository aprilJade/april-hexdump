NAME	=	april-hexdump

CC		=	gcc

FLAG	=	-Wall -Wextra -Werror

INCLUDE	=	-I includes/

SRC_DIR	=	src

OBJ_DIR	=	obj

SRCS	=	$(notdir $(wildcard $(SRC_DIR)/*.c))

OBJS	=	$(SRCS:.c=.o)

OBJECTS	=	$(patsubst %.o, $(OBJ_DIR)/%.o, $(OBJS))

TARGET	=	$(NAME)

debug	:	FLAG += -g

debug	:	$(TARGET)

release	:	$(TARGET)

all		:	debug

CLEAN	=	rm -rf $(OBJECTS)
FCLEAN	=	rm -rf $(TARGET)

ifeq ($(OS), Windows_NT)
	CLEAN = del -Force .\obj\*.o
	FCLEAN = del -Force .\$(TARGET).exe
endif

clean	:	
	$(CLEAN)
	 
fclean	:	clean
	$(FCLEAN)

re		:	fclean all

$(OBJ_DIR)/%.o	: $(SRC_DIR)/%.c
	$(CC) $(FLAG) -c $< -o $@

$(OBJ_DIR)	:
	mkdir -p $(OBJ_DIR)

$(NAME)	:	$(OBJECTS)
	$(CC) $(OBJECTS) $(FLAG) -o $(NAME)

.PHONY	:	all clean fclean re debug release