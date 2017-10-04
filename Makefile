SRC_PATH 	= ./src/
OBJ_PATH	= ./.obj/
INC_PATH	= ./include/

NAME		= rabidja
CC			= gcc
CFLGS		= -Werror -Wextra -Wall
SDL2FLGS	= -lSDL2 -lSDL2_ttf -lSDL2_image -lSDL2_mixer

SRC_NAME	= main.c player.c map.c init.c draw.c inputs.c monster.c font.c sound.c
OBJ_NAME	= $(SRC_NAME:.c=.o)

SRC			= $(addprefix $(SRC_PATH), $(SRC_NAME))
OBJ			= $(addprefix $(OBJ_PATH), $(OBJ_NAME))
INC			= $(addprefix -I, $(INC_PATH))

.PHONY: re all clean fclean

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLGS) $(SDL2FLGS) $(INC) $(OBJ) -o $(NAME)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@mkdir -p $(OBJ_PATH)
	$(CC) $(CFLGS) $(INC) -o $@ -c $<

clean:
	rm -fv $(OBJ)
	rm -rf $(OBJ_PATH)

fclean: clean
	rm -fv $(NAME)

re: fclean all
	
