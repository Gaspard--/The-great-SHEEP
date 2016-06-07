##
## Makefile
##
## Made by Jakob Kellendonk
## Login   <kellen_j@epitech.net>
##
## Started on  Fri Nov 13 17:19:42 2015 Jakob Kellendonk
## Last update Tue Apr  5 09:34:46 2016 Jakob Kellendonk
##

CC =	g++

RM =	rm -f

CFLAGS +=	-W -Wextra -Wall
CFLAGS +=	-I./

CPPFLAGS +=	-W -Wextra -Wall
CPPFLAGS +=	-I./include -I. -std=c++11 -g -O3

LDFLAGS = `pkg-config --static --libs glfw3`

NAME =	bullethell

SRCS_C = gl3w.c

SRCS_CPP = 	source/main.cpp \
		source/game_state.cpp \
		source/game_display.cpp \
		source/game_logic.cpp \
		source/game_input.cpp \
		source/my_opengl.cpp \
		source/triangle_render_queue.cpp \
		source/tile.cpp \
		source/my_random.cpp \
		source/terrain_generator.cpp \
		source/image_render_queue.cpp \

OBJS = 	$(SRCS_C:.c=.o) $(SRCS_CPP:.cpp=.o)

all: $(NAME)

$(NAME):$(OBJS)
	$(CC) $(OBJS) -o $(NAME) $(LDFLAGS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
