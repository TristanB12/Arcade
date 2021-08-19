##
## EPITECH PROJECT, 2021
## arcade [WSL: Ubuntu-20.04]
## File description:
## Makefile
##

SUBDIRS := $(wildcard */.)

all:
	for dir in $(SUBDIRS); do \
		make -C $$dir all; \
	done

clean:
	for dir in $(SUBDIRS); do \
		make -C $$dir clean; \
	done

fclean:
	for dir in $(SUBDIRS); do \
		make -C $$dir fclean; \
	done

re:
	for dir in $(SUBDIRS); do \
		make -C $$dir re; \
	done

.PHONY: all clean fclean re $(SUBDIRS)