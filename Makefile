#
# paths
#
SRCDIR :=	./source
INCDIR :=	./include

#
# compilation options
#
CXX :=		g++
CXXFLAGS :=	`sdl2-config --cflags` -I $(INCDIR) -W -Wall -Wextra -std=c++11 -g -Winvalid-pch

#
# link options
#
LINKER :=	$(CXX)
LDFLAGS :=	`sdl2-config --libs`
LDLIBS :=	-l SDL2_image

#
# binary options
#
NAME :=		The-great-SHEEP

SRC :=		main.cpp \
		display.cpp \
		terrain.cpp \
		camera.cpp \
		game.cpp \
		menustate.cpp \
		playstate.cpp \
		renderable.cpp \
		fixture.cpp
SRC :=		$(addprefix $(SRCDIR)/, $(SRC))
OBJ :=		$(SRC:.cpp=.o)
PCH :=		$(wildcard $(INCDIR)/*.gch)

#
# build rules
#
all:		$(NAME)

%.hpp.gch:	%.hpp Makefile
		$(CXX) $(CXXFLAGS) $< -o $@

obj_gen = 	$(shell echo -n $(dir $1) >> targets.mk); \
		$(shell g++ -I $(INCDIR) -MM $1 | sed 's/.hpp/.hpp.gch/g;$$s/$$/ Makefile/' >> targets.mk); \
		$(shell echo $2 >> targets.mk) \
		$(shell echo >> targets.mk);

# The '\t' is substitued by the 'echo' built-in called in `obj_gen`
RULE_CONTENT :=	'\tg++ -c $$(CXXFLAGS) $$< -o $$@'

$(shell echo -n > targets.mk)
$(foreach var, $(SRC), $(call obj_gen, $(var), $(RULE_CONTENT)))
include targets.mk

$(NAME):	$(OBJ)
		$(LINKER) -o $@ $(OBJ) $(LDFLAGS) $(LDLIBS)

#
# clean rules
#
RM :=		rm -fv

clean:
		$(RM) $(OBJ) $(PCH)

fclean:		clean
		$(RM) $(NAME)

re:		fclean all

#
# special rules
#
.PHONY:		all clean fclean re

.SILENT:	clean fclean
