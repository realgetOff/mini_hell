CC = clang
NAME = mini_hell
SRCS = main/mini_hell.c builtins/cd/cd.c builtins/echo/echo.c builtins/env/env.c \
builtins/export/export.c builtins/pwd/pwd.c builtins/unset/unset.c history/history.c exec/signal.c init/init_data.c exec/prompt.c\
exec/exec_builtins.c parsing/arg_split.c parsing/tokenisation.c utils/env_utils.c \
utils/ft_printf_err.c parsing/quote_parsing.c parsing/quote_parsing_utils.c exec/signal_utils.c \
parsing/expansion.c parsing/expansion_utils.c parsing/quote_split.c parsing/token_split.c \
builtins/exit/exit.c exec/free.c builtins/export/export_utils.c \
exec/exec.c exec/exec_cmd.c exec/exec_destroy.c exec/exec_init.c exec/exec_io_handling.c exec/exec_exit.c exec/exec_utils.c exec/exec_fork_utils.c\
exec/nodes.c parsing/token_parsing.c parsing/arg_split_utils.c builtins/unset/unset_utils.c exec/exec_io_handling_utils.c \
exec/exec_signals.c exec/exec_cmd_array.c exec/exec_init_utils.c exec/exec_exit_utils.c exec/exec_destroy_utils.c \
builtins/export/export_alloc.c builtins/export/export_alloc2.c builtins/export/export_noargval.c \
builtins/export/export_print.c builtins/export/export_split.c utils/env_utils_two.c parsing/expansion_utils_two.c \
utils/utils.c utils/utils_two.c exec/heredoc.c parsing/token_split_size.c parsing/tokenisation_utils.c \
parsing/token_split_fill.c utils/protec_utils.c

HEADER = includes/mini_hell.h
OBJS = $(SRCS:.c=.o)
CFLAGS = -Wall -Wextra -Werror -I includes -I libft -g
LDFLAGS = -Llibft -lft -lreadline

# Colors
BLACK	= \033[0;30m
RED		= \033[0;31m
GREEN	= \033[0;32m
YELLOW	= \033[0;33m
BLUE	= \033[0;34m
PURPLE	= \033[0;35m
CYAN	= \033[0;36m
WHITE	= \033[0;37m
BOLD	= \033[1m
RESET	= \033[0m

# Libft variables
LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a

all: $(LIBFT) $(NAME)

$(LIBFT):
	@echo "$(CYAN)╔════════════════════════════════════════════════════════════╗$(RESET)"
	@echo "$(CYAN)║$(RESET) $(BOLD)Building libft...$(RESET) $(CYAN)║$(RESET)"
	@echo "$(CYAN)╚════════════════════════════════════════════════════════════╝$(RESET)"
	@make -C $(LIBFT_DIR)

$(NAME): $(OBJS) $(LIBFT)
	@echo "$(GREEN)╔════════════════════════════════════════════════════════════╗$(RESET)"
	@echo "$(GREEN)║$(RESET) $(BOLD)Linking objects...$(RESET) $(GREEN)║$(RESET)"
	@echo "$(GREEN)╚════════════════════════════════════════════════════════════╝$(RESET)"
	@$(CC) $(OBJS) $(LDFLAGS) -o $(NAME)
	@echo "$(GREEN)╔════════════════════════════════════════════════════════════╗$(RESET)"
	@echo "$(GREEN)║$(RESET) $(BOLD)minishell successfully compiled!$(RESET) $(GREEN)║$(RESET)"
	@echo "$(GREEN)╚════════════════════════════════════════════════════════════╝$(RESET)"

%.o : %.c $(HEADER)
	@echo "$(BLUE)Compiling:$(RESET) $(YELLOW)$<$(RESET)"
	@$(CC) $(CFLAGS) -c $< -o $@

fclean: clean
	@echo "$(RED)╔════════════════════════════════════════════════════════════╗$(RESET)"
	@echo "$(RED)║$(RESET) $(BOLD)Removing executable...$(RESET) $(RED)║$(RESET)"
	@echo "$(RED)╚════════════════════════════════════════════════════════════╝$(RESET)"
	@rm -f $(NAME)
	@make -C $(LIBFT_DIR) fclean

clean:
	@echo "$(PURPLE)╔════════════════════════════════════════════════════════════╗$(RESET)"
	@echo "$(PURPLE)║$(RESET) $(BOLD)Cleaning object files...$(RESET) $(PURPLE)║$(RESET)"
	@echo "$(PURPLE)╚════════════════════════════════════════════════════════════╝$(RESET)"
	@rm -f $(OBJS)
	@make -C $(LIBFT_DIR) clean

re: fclean all
	@echo "$(CYAN)╔════════════════════════════════════════════════════════════╗$(RESET)"
	@echo "$(CYAN)║$(RESET) $(BOLD)Project rebuilt!$(RESET) $(CYAN)║$(RESET)"
	@echo "$(CYAN)╚════════════════════════════════════════════════════════════╝$(RESET)"

run: all
	./$(NAME) $(ARGS)

run2: all
	valgrind --leak-check=full --show-leak-kinds=all --suppressions=./vsupp --trace-children=yes --track-fds=yes ./$(NAME)

.PHONY: all fclean clean re run run2
