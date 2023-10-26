NAME = get_next_line

SRCS = get_next_line.c \
	   get_next_line_utils.c

OBJS = $(patsubst %.c,%.o,$(SRCS))

BSRCS = get_next_line_bonus.c \
		get_next_line_utils_bonus.c

BOBJS=$(patsubst %.c,%.o,$(BSRCS))

HEADER_DIR=get_next_line.h

HEADER_DIR_BONUS=get_next_line_bonus.h

CC=cc

CFLAGS=-Wall -Werror -Wextra -I $(HEADER_DIR)

CFLAGS_BONUS=-Wall -Werror -Wextra -I $(HEADER_DIR_BONUS)

.PHONY: all bonus clean fclean re

all: $(NAME)

$(NAME): $(OBJS)
	ar -rcs $@ $^

%.o:%.c
	$(CC) $(CFLAGS) -c -o $@ $^

%bonus.o:%bonus.c
	$(CC) $(CFLAGS_BONUS) -c -o $@ $^

bonus: $(BOBJS)
	ar -rcs $(NAME) $^

clean:
	rm -f $(OBJS) $(BOBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
