##
## EPITECH PROJECT, 2021
## Arcade
## File description:
## Makefile
##

all: parser core games graphicals

parser:
	make -C ./lib/Parser/ all

core: parser
	make -C ./lib/Core/ all

games: parser
	make -C ./lib/Games/ all

graphicals: parser
	make -C ./lib/Display/ all

doc: FORCE
	doxygen Doxyfile
FORCE:

coding-style:
	cpplint --recursive --quiet --filter=-legal/copyright,-build/c++11 --verbose=3 ./lib

clean:
	make -C ./lib/Parser/ clean
	make -C ./lib/Core/ clean
	make -C ./lib/Games/ clean
	make -C ./lib/Display/ clean

fclean: clean
	make -C ./lib/Parser/ fclean
	make -C ./lib/Core/ fclean
	make -C ./lib/Games/ fclean
	make -C ./lib/Display/ fclean

re: fclean all

.PHONY: all debug doc tests_run coverage coding-style clean fclean re