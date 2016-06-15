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

MK :=		$(SRC:.cpp=.d)

OBJ :=		$(SRC:.cpp=.o)

all:		$(NAME)

$(NAME):	$(OBJ)
		$(CPPC) $(OBJ) -o $(NAME) $(LDFLAGS)

clean:
		$(RM) $(OBJ)

fclean:		clean
		$(RM) $(NAME)

re:		fclean all

%.d:		%.cpp
		$(shell echo -n $(dir $(@)) > $(@))
		$(shell gcc $(<) -MM $(CPPFLAGS) | sed s/.hpp/.hpp.gch/g >> $(@))
		$(shell echo >> $(@))

%.o:		%.cpp 
		$(CPPC) -c $(<) -o $(@) $(CPPFLAGS)

%.hpp.gch:	%.hpp
		$(CPPC) $< $(HPPFLAGS)

%.hpp:

Makefile:	base.mk $(MK)
		$(shell cp base.mk Makefile)
		$(shell cat $(MK) >> Makefile)

.PHONY:		all clean fclean re

source/main.o: source/main.cpp include/game.hpp.gch include/display.hpp.gch \
 include/camera.hpp.gch include/vect.hpp.gch include/terrain.hpp.gch \
 include/gamestate.hpp.gch include/display.hpp.gch include/terrain.hpp.gch \
 include/vect.hpp.gch

source/display.o: source/display.cpp include/top_header.hpp.gch include/game.hpp.gch \
 include/display.hpp.gch include/camera.hpp.gch include/vect.hpp.gch \
 include/terrain.hpp.gch include/gamestate.hpp.gch include/display.hpp.gch \
 include/terrain.hpp.gch include/tile.hpp.gch include/camera.hpp.gch

source/terrain.o: source/terrain.cpp include/top_header.hpp.gch include/terrain.hpp.gch \
 include/vect.hpp.gch include/tile.hpp.gch

source/camera.o: source/camera.cpp include/top_header.hpp.gch include/camera.hpp.gch \
 include/vect.hpp.gch

source/game.o: source/game.cpp include/top_header.hpp.gch include/game.hpp.gch \
 include/display.hpp.gch include/camera.hpp.gch include/vect.hpp.gch \
 include/terrain.hpp.gch include/gamestate.hpp.gch include/gamestate.hpp.gch \
 include/menustate.hpp.gch include/playstate.hpp.gch

source/menustate.o: source/menustate.cpp include/top_header.hpp.gch include/game.hpp.gch \
 include/display.hpp.gch include/camera.hpp.gch include/vect.hpp.gch \
 include/terrain.hpp.gch include/gamestate.hpp.gch include/menustate.hpp.gch \
 include/playstate.hpp.gch

source/playstate.o: source/playstate.cpp include/top_header.hpp.gch include/game.hpp.gch \
 include/display.hpp.gch include/camera.hpp.gch include/vect.hpp.gch \
 include/terrain.hpp.gch include/gamestate.hpp.gch include/playstate.hpp.gch

source/renderable.o: source/renderable.cpp include/renderable.hpp.gch \
 include/vect.hpp.gch

source/fixture.o: source/fixture.cpp include/fixture.hpp.gch include/vect.hpp.gch

source/physics.o: source/physics.cpp include/physics.hpp.gch include/vect.hpp.gch \
 include/fixture.hpp.gch

