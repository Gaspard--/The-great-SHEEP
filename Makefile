CPPC :=		g++

RM :=		rm -rf

CPPFLAGS :=	`sdl2-config --cflags` -W -Wall -Wextra -Iinclude/ -std=c++11
CPPFLAGS +=	-Winvalid-pch

HPPFLAGS :=	-std=c++11

LDFLAGS :=	`sdl2-config --libs` -lSDL2_image

NAME :=		The-great-SHEEP

SRC :=		source/main.cpp \
		source/display.cpp \
		source/terrain.cpp \
		source/camera.cpp \
		source/game.cpp \
		source/menustate.cpp \
		source/playstate.cpp \
		source/renderable.cpp \
		source/fixture.cpp \
		source/physics.cpp \

OBJ :=		$(SRC:.cpp=.o)

all:		$(NAME)

$(NAME):	$(OBJ)
		$(CPPC) $(OBJ) -o $(NAME) $(LDFLAGS)

clean:
		$(RM) $(OBJ) $(MK)

fclean:		clean
		$(RM) $(NAME)

re:		fclean all

%.o:		%.cpp
		$(CPPC) -c $< -o $@ $(CPPFLAGS)


%.hpp.gch:	%.hpp
		$(CPPC) $< $(HPPFLAGS)

%.hpp:

.PHONY:		all clean fclean re

$(shell echo > pointo.mk)
$(foreach var, $(SRC), $(shell (echo -n $(dir $(var));g++ -Iinclude -MM $(var); echo -e "\t"g++ -c '$$<' -o '$$@'  $(CPPFLAGS); echo ) >> pointo.mk))
include pointo.mk

