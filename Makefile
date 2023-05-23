SRC = $(wildcard src/*.c)
SRC += main.c
OBJ = $(SRC:.c=.o)
NAME = inject


# Add the bfd library name
LDLIBS = -lbfd

all: $(NAME)

$(NAME): $(OBJ)
	gcc -Wall -Wextra -O3 -o $@ $^ $(LDLIBS)

clean:
	find . -name "*.o" -delete
	find . -name "*.gcda" -delete
	find . -name "*.gcno" -delete

fclean: clean
	rm -f $(NAME)
	rm -f unit_tests

debug: $(OBJ)
	gcc -g -Wall -Wextra -O3 -o $(NAME) $^ $(LDLIBS)

re: fclean all

.PHONY: all clean fclean debug re
