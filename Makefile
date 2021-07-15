NAME = pipex

HEAD = includes/

SRCSDIR = srcs/

LIB = lib/

SRCSFILES = execute_process.c main.c execute_commands.c free_vars.c check_open_files.c \
			first_last_files.c find_path.c \


SRCS = $(addprefix $(SRCSDIR), $(SRCSFILES))

OBJS = ${SRCS:.c=.o}

CC = gcc -g -Wall -Wextra -Werror

RM = rm -f

CFLAGS = -I $(HEAD)

FLAGS = -L $(LIB)libft -lft

$(NAME) : $(OBJS) $(HEAD)*.h
	@make -C $(LIB)libft all
	${CC} ${CFLAGS} $(OBJS) $(FLAGS)  -o ${NAME}

%.o: %.c $(HEAD)
	$(CC) -c  $< -o $@ -I$(HEAD)

all: ${NAME}

clean:
	make clean -C $(LIB)libft
	${RM} ${OBJS}

fclean: clean
	${RM} ${NAME}
	make fclean -C $(LIB)libft


re: fclean all

bonus: all

norme:
	norminette -R CheckForbiddenSourceHeader $(SRCSDIR)*.c  $(HEAD)*.h

.PHONY: all clean fclean re norme bonus
