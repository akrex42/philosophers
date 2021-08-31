NAME		= philo

#NAME_1		= checker

SRCS_DIR	= ./srcs

SRCS		= ./srcs/philo_main.c

OBJS		= $(patsubst %.c,%.o,$(SRCS))

DEPENDS		= $(patsubst %.c,%.d,$(SRCS))

HEADERS		= ./includes/philo.h

CC			= gcc

CFLAGS		= -Wall -Wextra -Werror -g -fsanitize=address

LDFLAGS		= -Wall -Wextra -Werror -g -fsanitize=address

RM			= rm -f

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(LDFLAGS) $^ -o $@

#$(NAME_1): $(OBJS_1) $(LIBFT)
#	$(CC) $(LDFLAGS) $^ -o $@

$(SRCS_DIR)%.o: $(SRCS_DIR)%.c Makefile
	$(CC) $(CFLAGS) -MMD -MP -c $< -o $@

-include $(DEPENDS)

clean:
		$(RM) $(OBJS) $(DEPENDS)
		clean

#fclean: clean
#		fclean

re: fclean all

#bonus: $(NAME_1)

.PHONY: all clean fclean re