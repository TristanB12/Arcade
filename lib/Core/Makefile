##
## EPITECH PROJECT, 2021
## Arcade
## File description:
## Core Makefile
##

CC			=	g++

MAIN		=	$(addprefix $(SRC_D), main.cpp)
OBJ_M		=	$(MAIN:.cpp=.o)

SRC			=	$(addprefix $(SRC_D), $(SRC_F))
OBJ			=	$(SRC:.cpp=.o)
SRC_D		=	src/
SRC_F		=	Core.cpp \
				CoreGame.cpp \
				CoreMenu.cpp \
				DLLoader.cpp

SRC_UT		=	$(addprefix $(SRC_UT_D), $(SRC_UT_F))
OBJ_UT		=	$(SRC_UT:.cpp=.o)
SRC_UT_D	=	tests/
SRC_UT_F	=

INC			=	-I./inc -I../inc/

DEP			=	$(OBJ:.o=.d)

-include $(DEP)

CXXFLAGS	=	-std=c++17 $(WFLAGS) $(INC) -MMD

WFLAGS		=	-W -Wall -Wextra -Werror

DBFLAGS		=	-g -g3 -ggdb

LDFLAGS		=	-ldl -L../ -lparser

LDFLAGS_UT  =	-lgtest -lgtest_main -lpthread

NAME		=	arcade

NAME_UT		=	unit_tests

all: $(NAME)

$(NAME): $(OBJ_M) $(OBJ)
	$(CC) $(CXXFLAGS) -o $(NAME) $(OBJ_M) $(OBJ) $(LDFLAGS)
	mv $(NAME) ../../

debug: $(OBJ_M) $(OBJ)
	$(CC) $(CXXFLAGS) $(DBFLAGS) -o $(NAME) $(OBJ_M) $(OBJ) $(LDFLAGS)
	mv $(NAME) ../../

tests_run: clean $(OBJ) $(OBJ_UT)
	$(CC) $(CXXFLAGS) -o $(NAME_UT) $(OBJ) $(OBJ_UT) $(LDFLAGS) $(LDFLAGS_UT)
	./$(NAME_UT)

clean:
	rm -f $(OBJ) $(OBJ_M) $(OBJ_UT) $(DEP) *.gc*

fclean: clean
	rm -f ../../$(NAME)
	rm -f $(NAME_UT)

re: fclean all

.PHONY: all debug doc tests_run coverage coding-style clean fclean re