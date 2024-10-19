NAME = minishell
SRCS = \
	libft/ft_isalpha.c libft/ft_isdigit.c libft/ft_isalnum.c libft/ft_isascii.c libft/ft_isprint.c \
	libft/ft_strlen.c libft/ft_memset.c libft/ft_bzero.c libft/ft_memcpy.c libft/ft_memmove.c \
	libft/ft_strlcpy.c libft/ft_strlcat.c libft/ft_toupper.c libft/ft_tolower.c libft/ft_strchr.c \
	libft/ft_strrchr.c libft/ft_strncmp.c libft/ft_memchr.c libft/ft_memcmp.c libft/ft_strnstr.c libft/ft_atoi.c \
	libft/ft_calloc.c libft/ft_strdup.c libft/ft_substr.c libft/ft_strjoin.c libft/ft_strtrim.c libft/ft_split.c \
	libft/ft_itoa.c libft/ft_strmapi.c  libft/ft_putchar_fd.c libft/ft_putstr_fd.c \
	libft/ft_lstnew_bonus.c libft/ft_lstadd_back_bonus.c libft/ft_lstsize_bonus.c  main/extra_args.c\
	libft/ft_putnbr_fd.c libft/ft_putendl_fd.c libft/ft_strcmp.c main/get_file_path.c main/ambigous.c\
	main/env.c main/minishell.c main/initialisation.c main/cheack_lexical.c main/cheack_lexical_utils.c \
	main/cheack_redir.c main/parsing.c main/parsing_utils.c main/allocation.c main/cmd_args.c main/redirections.c\
	main/env__utils.c main/execution.c  main/redirection_utils.c  main/extra_arg.c main/tab_to_space.c main/heredoc.c main/is_cmd.c \
	main/pwd.c main/cd.c  main/echo.c main/env_cmd.c main/exit.c main/unset.c main/envp_ex.c main/append.c main/get_path.c \

OBJS = ${SRCS:.c=.o}

CC = cc
RM = rm -f

CFLAGS = -Wall -Wextra -Werror 


$(NAME): ${OBJS}
	$(CC) $(CFLAGS) ${OBJS} -o ${NAME}  -lreadline -L /Users/ielhasso/goinfre/ielhasso/.brew/opt/readline/lib -I /Users/ielhasso/goinfre/ielhasso/.brew/opt/readline/include
all: ${NAME}

clean:
	${RM}  ${OBJS}

fclean: clean
	${RM} ${NAME}

re: fclean all
.SECONDARY: ${OBJS}
