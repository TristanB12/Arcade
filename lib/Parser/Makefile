##
## EPITECH PROJECT, 2021
## Arcade
## File description:
## Parser Makefile
##

CC			=	g++

SRC			=	Parser.cpp
OBJ			=	$(SRC:.cpp=.o)

HEADER		=	Parser.hpp

SRC_UT		=	$(addprefix $(SRC_UT_D), $(SRC_UT_F))
OBJ_UT		=	$(SRC_UT:.cpp=.o)
SRC_UT_D	=	tests/
SRC_UT_F	=	parser/testParser.cpp

INC			=	-I./inc -I../inc/

CXXFLAGS	=	-std=c++17 -fPIC $(WFLAGS) $(INC)

WFLAGS		=	-W -Wall -Wextra -Werror

DBFLAGS		=	-g -g3 -ggdb

LDFLAGS_UT  =	-lgtest -lgtest_main -lpthread

NAME		=	libparser.a

NAME_UT		=	unit_tests

all: $(NAME)

$(NAME): $(OBJ)
	ar rc $(NAME) $(OBJ)
	cp $(NAME) ../
	cp $(HEADER) ../inc

tests_run: clean $(OBJ) $(OBJ_UT)
	$(CC) $(CXXFLAGS) -o $(NAME_UT) $(OBJ) $(OBJ_UT) $(LDFLAGS) $(LDFLAGS_UT)
	./$(NAME_UT)

coverage:
	gcovr -s --exclude tests/

coding-style:
	cpplint --recursive --filter=-legal/copyright --verbose=3 .

clean:
	rm -f $(OBJ)
	rm -f $(OBJ_UT)
	rm -f *.gc*

fclean: clean
	rm -f $(NAME)
	rm -f ../$(NAME)
	rm -f ../inc/$(HEADER)
	rm -f $(NAME_UT)

re: fclean all

.PHONY: all debug tests_run coverage coding-style clean fclean re