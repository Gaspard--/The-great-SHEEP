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

MK :=		$(SRC:.cpp=.mk)

OBJ :=		$(SRC:.cpp=.o)

all:		$(NAME)

$(NAME):	$(OBJ)
		$(CPPC) $(OBJ) -o $(NAME) $(LDFLAGS)

clean:
		$(RM) $(OBJ)

fclean:		clean
		$(RM) $(NAME)

re:		fclean all

%.mk:		%.cpp
		$(shell echo -n $(dir $(@)) > $(@))
		$(shell gcc $(<) -MM -Iinclude >> $(@))
		$(shell echo >> $(@))

%.o:		%.cpp 
		$(CPPC) -c $(<) -o $(@) $(CPPFLAGS)

%.hpp.gch:	%.hpp
		$(CPPC) $< $(HPPFLAGS)

%.hpp:
		echo "hello"

Makefile:	base.mk $(MK)
		$(shell cat base.mk > Makefile)
		$(shell cat $(MK) >> Makefile)

.PHONY:		all clean fclean re

source/main.o: source/main.cpp include/game.hpp include/display.hpp \
 include/camera.hpp include/terrain.hpp include/vect.hpp \
 include/gamestate.hpp include/display.hpp include/terrain.hpp \
 include/vect.hpp

source/display.o: source/display.cpp include/top_header.hpp include/game.hpp \
 include/display.hpp include/camera.hpp include/terrain.hpp \
 include/vect.hpp include/gamestate.hpp include/display.hpp \
 include/terrain.hpp include/tile.hpp include/object.hpp \
 include/character.hpp include/camera.hpp

source/terrain.o: source/terrain.cpp include/top_header.hpp include/terrain.hpp \
 include/vect.hpp include/tile.hpp include/object.hpp \
 include/character.hpp

source/camera.o: source/camera.cpp include/top_header.hpp include/camera.hpp

source/game.o: source/game.cpp include/top_header.hpp include/game.hpp \
 include/display.hpp include/camera.hpp include/terrain.hpp \
 include/vect.hpp include/gamestate.hpp include/gamestate.hpp \
 include/menustate.hpp include/playstate.hpp

source/menustate.o: source/menustate.cpp include/top_header.hpp include/game.hpp \
 include/display.hpp include/camera.hpp include/terrain.hpp \
 include/vect.hpp include/gamestate.hpp include/menustate.hpp \
 include/playstate.hpp

source/playstate.o: source/playstate.cpp include/top_header.hpp include/game.hpp \
 include/display.hpp include/camera.hpp include/terrain.hpp \
 include/vect.hpp include/gamestate.hpp include/playstate.hpp

source/renderable.o: source/renderable.cpp include/renderable.hpp \
 include/vect.hpp

source/fixture.o: source/fixture.cpp include/fixture.hpp include/vect.hpp

source/physics.o: source/physics.cpp include/physics.hpp include/vect.hpp \
 include/fixture.hpp

