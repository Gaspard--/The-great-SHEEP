##
## Makefile for  in /home/melis_m/code/github/irc_client
##
## Made by
## Login   <melis_m@epitech.net>
##
## Started on  Sun Mar  6 13:34:43 2016
## Last update Tue Jun  7 13:50:35 2016 
##

CC		=	g++

CXXFLAGS	+=	-W -Wall -Wextra -Iinclude \
			-lsfml-graphics -lsfml-window -lsfml-system

NAME		=	test

SRC_DIR		=	source/

SRCS		=	main.cpp \

SRCS		:= 	$(addprefix $(SRC_DIR), $(SRCS))

OBJS		=	$(SRCS:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(SRCS) $(CXXFLAGS) -o $(NAME)

.cpp.o:
	$(CC) -c -o $@ $< -Iinclude

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all
