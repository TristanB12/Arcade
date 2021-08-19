##
## EPITECH PROJECT, 2021
## Arcade
## File description:
## Makefile
##

CC			=	g++

SRC			=	Nibbler.cpp
OBJ			=	$(SRC:.cpp=.o)

SRC_UT		=	$(addprefix $(SRC_UT_D), $(SRC_UT_F))
OBJ_UT		=	$(SRC_UT:.cpp=.o)
SRC_UT_D	=	tests/
SRC_UT_F	=	testNibbler.cpp

INC			=	-I../../inc -I./

CXXFLAGS	=	-std=c++17 $(WFLAGS) $(INC)

WFLAGS		=	-W -Wall -Wextra -Werror

DBFLAGS		=	-g -g3 -ggdb

LDFLAGS 	=	-L../../ -lparser

LDFLAGS_UT  =	-lgtest -lgtest_main -lpthread

NAME		=	arcade_nibbler.so

NAME_UT		=	unit_tests

all: $(NAME)

%.o: %.cpp
	$(CC) $(CXXFLAGS) -fPIC -c $< -o $@

$(NAME): $(OBJ)
	$(CC) $(CXXFLAGS) --shared -o $(NAME) $(OBJ) $(LDFLAGS)
	mv $(NAME) ../../

debug: $(OBJ)
	$(CC) $(CXXFLAGS) $(DBFLAGS) -o $(NAME) $(OBJ)

tests_run: clean $(OBJ) $(OBJ_UT)
	$(CC) $(CXXFLAGS) -o $(NAME_UT) $(OBJ) $(OBJ_UT) $(LDFLAGS) $(LDFLAGS_UT)
	./$(NAME_UT)

coverage:
	gcovr -s --exclude tests/

clean:
	rm -f $(OBJ)
	rm -f $(OBJ_UT)
	rm -f *.gc*

fclean: clean
	rm -f ../../$(NAME)
	rm -f $(NAME_UT)

re: fclean all