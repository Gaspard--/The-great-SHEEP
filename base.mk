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

