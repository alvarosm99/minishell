NAME 					= minishell

CC						= cc

LIBFT					= ./libft/libft.a

STD_FLAGS 				= -Wall -Wextra -Werror -L/usr/local/opt/readline/lib -I/usr/local/opt/readline/include -lreadline

SRCS					= src/main/main.c \
						  src/main/errors.c \
						  src/main/welcome_message.c \
						  src/main/signal.c \
						  src/redirection/free_heredoc.c \
						  src/main/init_data.c \
						  src/main/init_data_handler.c \
						  src/main/free_data.c \
						  src/main/read_input.c \
						  src/parsing/parsing.c \
						  src/parsing/exec_counter.c \
						  src/parsing/tokenizer.c \
						  src/utils/check_closing_quotes.c \
						  src/utils/ft_get_path.c \
						  src/utils/ft_free_tab.c \
						  src/utils/ft_get_env.c \
						  src/utils/ft_strcmp.c \
						  src/utils/ft_is_only_spaces.c \
						  src/utils/file_finder.c \
						  src/utils/ft_strinsert.c \
						  src/expansion/env_var_expansion.c \
						  src/expansion/expand_token.c \
						  src/expansion/field_split.c \
						  src/redirection/heredoc.c \
						  src/execution/execution_setup.c \
						  src/execution/pipeline_builder.c \
						  src/execution/pipeline_stream.c \
						  src/execution/exec_commands.c \
						  src/execution/exec_handlers.c \
						  src/redirection/redirect_setup.c \
						  src/redirection/heredoc_utils.c \
						  src/builts/echo.c \
						  src/builts/cd.c \
						  src/builts/pwd.c \
						  src/builts/export.c \
						  src/builts/export_checks.c \
						  src/builts/export_utils.c \
						  src/builts/unset.c \
						  src/builts/env.c \
						  src/builts/exit.c \
						  src/builts/export_var_exp.c \


OBJS					= ${SRCS:.c=.o}

REMOVE					= rm -f ${OBJS}

all:					${LIBFT} ${NAME}

${NAME}:
						${CC} ${SRCS} ${LIBFT} ${STD_FLAGS} -o ${NAME}

${LIBFT}:				
						make bonus -C ./libft

clean:					
						${REMOVE}
						make clean -C ./libft

fclean:					clean
						make fclean -C ./libft
						rm -f minishell
						
re:						fclean all

.PHONY:					all clean fclean re