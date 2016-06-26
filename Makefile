#
# paths
#
SRCDIR :=	./source
INCDIR :=	./include

#
# compilation options
#
CXX :=		g++
CXXFLAGS :=	`sdl2-config --cflags` -I $(INCDIR) -W -Wall -Wextra -std=c++11 -g -Winvalid-pch -Wconversion

#
# link options
#
LINKER :=	$(CXX)
LDFLAGS :=	`sdl2-config --libs`
LDLIBS :=	-l SDL2_image -l SDL2_ttf

#
# binary options
#
NAME :=		The-great-SHEEP

SRC :=		main.cpp \
		camera.cpp \
		display.cpp \
		entity.cpp \
		entity_handler.cpp \
		fixture.cpp \
		game.cpp \
		logic.cpp \
		menustate.cpp \
		object.cpp \
		perso.cpp \
		playstate.cpp \
		physics.cpp \
		renderable.cpp \
		terrain.cpp \
		texture.cpp \
		timer.cpp \
		random.cpp \
		terrain_generator.cpp \
		renderable_compare.cpp \

SRC :=		$(addprefix $(SRCDIR)/, $(SRC))
OBJ :=		$(SRC:.cpp=.o)
PCH :=		$(wildcard $(INCDIR)/*.gch)

#
# build rules
#
all:		$(NAME)

%.hpp.gch:	%.hpp Makefile
		$(CXX) $(CXXFLAGS) $< -o $@

# The first argument of this function (the `$(1)`) is the file name
#
# Note: Print a tabulation with `echo` is a real pain, implementations
# differs than the POSIX standard. `printf` is better for this.
#
# Note: We could probably do something better with the $(eval ...)
# function.
obj_gen = \
	$(shell printf $(dir $(1)) >> targets.mk); \
	$(shell $(CXX)  $(CXXFLAGS) -MM $(1) | \
		sed 's/.hpp/.hpp.gch/g;$$s/$$/ Makefile/' >> targets.mk); \
	$(shell printf '\t$(CXX) -c $(CXXFLAGS) $$< -o $$@\n\n' >> targets.mk);

$(shell printf "# Generated file - do not edit\n\n" > targets.mk)
$(foreach var, $(SRC), $(call obj_gen,$(var)))
include targets.mk

$(NAME):	$(OBJ)
		$(LINKER) -o $@ $(OBJ) $(LDFLAGS) $(LDLIBS)

#
# clean rules
#
RM :=		rm -fv

clean:
		$(RM) $(OBJ) $(PCH) targets.mk

fclean:		clean
		$(RM) $(NAME)

re:		fclean all

#
# special rules
#
.PHONY:		all clean fclean re

.SILENT:	clean fclean
