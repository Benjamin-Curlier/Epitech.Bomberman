##
## Makefile
## 
## Made by 
## Login   <@epitech.eu>
## 
## Started on  lun. mai 18 19:21:27 2015 
## Last update dim. juin 14 20:46:08 2015 
##

SRC	= main.cpp \

NAME	= bomberman

FLAG	= -ILibBomberman_linux_x64/includes -LLibBomberman_linux_x64/libs -lgdl_gl -lSDL2 -lpthread -lGL -ldl -lrt -lfbxsdk -lGLEW -std=c++0x -lsfml-audio
#FLAG	+= -Wall -Wextra -W -Werror
FLAG	+= -g
FLAG	+= -O3 -s

CPPFLAGS= $(FLAG)

LDFLAGS	= $(FLAG)

OBJ	= $(SRC:.cpp=.o)

RM	= rm -f

CC	= g++

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(SRC) $(FLAG) -o $(NAME)
	@echo "Don't forget to : export LD_LIBRARY_PATH=./LibBomberman_linux_x64/libs"

clean:
	$(RM) $(OBJ) *.swp *~ *#

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re

