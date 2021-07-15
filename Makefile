NAME = pipex

HEAD = includes/

SRCSDIR = srcs/

BONUS_DIR = srcs_bonus/

LIB = lib/

SRCSFILES = execute_process.c main.c execute_commands.c free_vars.c check_open_files.c \
			first_last_files.c find_path.c \


BONUS_FILES = execute_process_bonus.c main_bonus.c execute_commands_bonus.c \
			free_vars_bonus.c check_open_files_bonus.c \
			first_last_files_bonus.c find_path_bonus.c \

SRCS = $(addprefix $(SRCSDIR), $(SRCSFILES))

B_SRCS = $(addprefix $(BONUS_DIR), $(BONUS_FILES))

OBJS = ${SRCS:.c=.o}

B_OBJS = ${B_SRCS:.c=.o}

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
	${RM} ${B_OBJS}

fclean: clean
	${RM} ${NAME}
	make fclean -C $(LIB)libft


re: fclean all

bonus: $(B_OBJS) $(HEAD)*.h
	@make -C $(LIB)libft all
	${CC} ${CFLAGS} $(B_OBJS) $(FLAGS)  -o ${NAME}

norme:
	norminette -R CheckForbiddenSourceHeader $(SRCSDIR)*.c $(BONUS_DIR)*.c $(HEAD)*.h

.PHONY: all clean fclean re norme bonus
