NAME		= philo

#NAME_1		= philo2

SRCS_DIR	= ./srcs/

SRCS		= $(wildcard $(SRCS_DIR)*.c)

OBJS		= $(patsubst %.c,%.o,$(SRCS))

DEPENDS		= $(patsubst %.c,%.d,$(SRCS))

HEADERS		= ./includes/philo.h

CC			= gcc

CFLAGS		= -Wall -Wextra -Werror -g

LDFLAGS		= -Wall -Wextra -Werror -g

RM			= rm -f

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(LDFLAGS) $^ -o $@

#$(NAME_1): $(OBJS_1)
#	$(CC) $(LDFLAGS) $^ -o $@

$(SRCS_DIR)%.o: $(SRCS_DIR)%.c Makefile
	$(CC) $(CFLAGS) -MMD -MP -c $< -o $@

-include $(DEPENDS)

clean:
			$(RM) $(OBJS) $(DEPENDS)

fclean: clean
			$(RM) $(NAME)

re: fclean all

#bonus: $(NAME_1)

.PHONY: all clean fclean re