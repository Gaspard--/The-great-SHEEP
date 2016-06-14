CC =		g++

RM =		rm -rf

CPPFLAGS =	`sdl2-config --cflags` -W -Wall -Wextra -Iinclude/ -std=c++11 -g

LDFLAGS =	`sdl2-config --libs` -lSDL2_image

NAME =		The-great-SHEEP

SRC =		source/main.cpp \
		source/display.cpp \
		source/terrain.cpp \
		source/camera.cpp \

OBJ =		$(SRC:.cpp=.o)

all:		$(NAME)

$(NAME):	$(OBJ)
		$(CC) $(OBJ) -o $(NAME) $(LDFLAGS)

clean:
		$(RM) $(OBJ)

fclean:		clean
		$(RM) $(NAME)

re:		fclean all

.PHONY:		all clean fclean re
