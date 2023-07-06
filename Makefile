NAME = fractol

CC = cc

CFLAGS = -Wall -Wextra -Werror

SRC = fractol.c	fractol_utils.c	complex_operators.c	events_actions.c events_actions1.c

SRC_BONUS = fractol_bonus.c	fractol_utils.c	complex_operators.c	events_actions_bonus.c events_actions1_bonus.c	bonus.c

OBJS = $(SRC:.c=.o)

OBJS_BONUS = $(SRC_BONUS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $^ -lm -lmlx -framework OpenGL -framework AppKit -o $@

%.o:%.c fractol.h
	$(CC) $(CFLAGS) -Imlx -c $< -o $@

bonus: $(OBJS_BONUS)
	$(CC) $(CFLAGS) $^ -lm -lmlx -framework OpenGL -framework AppKit -o fractol_bonus

clean:
	rm -f $(OBJS) $(OBJS_BONUS)

fclean: clean
	rm -f $(NAME) fractol_bonus

re: fclean all

.PHONY: all clean fclean re
