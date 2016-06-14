CPPC =		g++

RM =		rm -rf

CPPFLAGS =	`sdl2-config --cflags` -W -Wall -Wextra -Iinclude/ -std=c++11 -g

LDFLAGS =	`sdl2-config --libs` -lSDL2_image

NAME =		The-great-SHEEP

SRC =		source/main.cpp \
		source/display.cpp \
		source/terrain.cpp \
		source/camera.cpp \
		source/game.cpp \
		source/menustate.cpp \
		source/playstate.cpp \
		source/renderable.cpp \
		source/fixture.cpp \

OBJ =		$(SRC:.cpp=.o)

all:		$(NAME)

$(NAME):	$(OBJ)
		$(CPPC) $(OBJ) -o $(NAME) $(LDFLAGS)

clean:
		$(RM) $(OBJ)

fclean:		clean
		$(RM) $(NAME)

re:		fclean all

%.o:		%.cpp
		$(CPPC) -c -o $@ $^ $(CPPFLAGS)

.PHONY:		all clean fclean re
