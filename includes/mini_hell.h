/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_hell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmilner- <pmilner-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 06:42:39 by mforest-          #+#    #+#             */
/*   Updated: 2025/04/29 00:59:27 by pmilner-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_HELL_H
# define MINI_HELL_H

/* ========== INCLUDES ========== */

# include "libft.h"
# include <curses.h>            /* pour les fonctions termcap */
# include <dirent.h>            /* opendir, readdir, closedir */
# include <fcntl.h>             /* open */
# include <readline/history.h>  /* add_history */
# include <readline/readline.h> /* readline, rl_clear_history, rl_on_new_line,
									rl_replace_line, rl_redisplay */
# include <signal.h>            /* signal, sigaction, sigemptyset, sigaddset,
									kill */
# include <stdio.h>             /* printf, perror */
# include <stdlib.h>            /* malloc, free, exit, getenv */
# include <string.h>            /* strerror */
# include <sys/ioctl.h>         /* ioctl */
# include <sys/stat.h>          /* stat, lstat, fstat */
# include <sys/wait.h>          /* wait, waitpid, wait3, wait4 */
# include <unistd.h>            /* write, access, close, fork, getcwd, chdir,
									unlink, execve, dup, dup2, pipe, isatty,
										ttyslot */
# include <errno.h>             /* the errno variable */

/* ========== DEFINES ========== */

# define HISTORY_SIZE 4096
# define LINE_MAX 4096

/* ========== ENUMS ========== */

enum					e_token_type
{
	TOKEN_UNCLASSED = 0,
	TOKEN_COMMAND = 1,
	TOKEN_ARGUEMENT = 2,
	TOKEN_OPERATOR = 3,
	TOKEN_REDIRECTION = 4,
	TOKEN_FILENAME = 5,
	TOKEN_DELIMITER = 6,
	TOKEN_ASSIGNMENT = 7
};

/* ========== STRUCTURES ========== */

typedef struct s_arguements
{
	int					type;
	char				*arg;
}						t_arguements;

typedef struct s_read
{
	char				prompt[LINE_MAX];
	char				*user;
	char				*current_dir;
	char				**line;
	char				**envp;
	char				**exports;
	int					executed;
	int					linesize;
	t_arguements		*tokens;
}						t_read;

typedef struct s_history
{
	char				*history_buffer[HISTORY_SIZE];
	int					history_count;
	int					history_index;
}						t_history;

typedef struct s_data
{
	int					exit_code;
	t_history			*s_history;
	t_read				*s_read;
}						t_data;

typedef struct s_iofiles
{
	int					in;
	int					out;
}						t_iofiles;

typedef struct s_node
{
	int					type;
	struct s_iofiles	io_fds;
	char				**cmd;
	struct s_node		*left;
	struct s_node		*right;
}						t_node;

typedef struct s_exec
{
	int					**pipefds;
	char				**envp;
	char				**path_dirs;
	t_arguements		*tokens;
	int					cmd_count;
	int					saved_in;
	int					saved_out;
	char				*tmp_file;
	t_data				*data;
	t_read				*entry;
	t_node				*first;
}						t_exec;

typedef struct s_builtins
{
	char				*entry;
	void				(*f)(t_exec *, t_node *);
	int					flag;
}						t_builtins;

typedef struct s_indices
{
	int					i;
	int					j;
	int					k;
}						t_indices;

typedef struct s_dollar_indices
{
	int					i;
	int					j;
	int					k;
}						t_dollar_indices;

/* ========== GLOBAL VARIABLES ========== */

extern pid_t			g_signal_pid;

/* ========== FUNCTION PROTOTYPES ========== */

/* --------- Core Functions --------- */
void					init_data(t_data *data, char **envp);
void					ft_free(t_data *data);
t_exec					init_exec(t_read *entry, t_data *data);

/* --------- History Functions --------- */
void					add_to_history_buffer(char *input, t_data *data);
void					free_history_buffer(t_data *data);

/* --------- Builtin Functions --------- */
void					ft_exit(t_exec *exec, t_node *node);
void					cd(t_exec *exec, t_node *node);
void					unset(t_exec *exec, t_node *node);
void					ft_export(t_exec *exec, t_node *node);
void					env(t_exec *exec, t_node *node);
void					ft_echo(t_exec *exec, t_node *node);
void					pwd(t_exec *exec, t_node *node);
void					solo_export_cmd(t_read *entry);
void					add_to_exports(t_read *entry, char *name);
void					export_single_var(char *env_var);
void					set_in_env(t_read *entry, char *name, char *value);
void					append_to_env(t_read *entry, char *name, char *value);
char					*create_env_string(char *name, char *value);
char					*append_value(char *old_value, char *append_value);
void					add_to_env(t_read *entry, char *name, char *value);

/* --------- Execution Functions --------- */
void					exec_cmds(t_data *data, t_read *entry);
void					exec_builtins(t_data *data, t_read *entry);
void					exec_bin(t_data *data, t_read *entry);
void					exec_not_bin(t_data *data, t_read *entry);
void					launch_command(t_data *data, t_read *entry,
							char *cmd_path);
void					execute_child_process(char *cmd_path, char **args,
							char **envp);
void					handle_exit_status(int status, int *exit_code);
void					wait_loop(t_exec *exec);
void					exit_with_error(t_exec *exec, int errornum,
							char *command);
void					destroy_exec(t_exec *exec_st);
char					*command_verif(t_iofiles *io_fds, t_exec *exec,
							char *command);
void					handle_override(t_node *node, int **pipefds, int layer,
							int max);
void					ft_exec(t_node *node, t_exec *exec);
void					full_exec(t_node *node, t_exec *exec);
void					exec_nodes(t_node *node, t_exec *exec, int layer);
int						execbuiltins(t_node *node, t_exec *exec);
char					***get_cmd_args(t_arguements *array, int size);
t_node					*set_cmds(t_node *current, char ***cmds, int layer,
							t_iofiles *io_fds);
int						cmd_count(t_arguements *array);
void					fill_cmd_array(char *arg, int *j, char **ret);
char					**create_cmd_array(t_arguements *array);
int						**init_pipes(void);
char					**get_path_dirs(char **envp);
t_node					*create_nodes(t_arguements *array, t_exec *exec);
int						check_builtin_match(t_node *node,
							const t_builtins *builtin);
int						handle_io_errors(t_node *node, t_exec *exec);
void					restore_std_fds(int oldin, int oldout);
void					setup_io_redirection(t_node *node, int *oldin,
							int *oldout);

/* --------- Signal Functions --------- */
void					setup_signals(t_data *data);
void					handle_sigint(int sig);
char					*get_signal_name(int signal);
void					print_signal(int signal);
void					handle_sigquit(int sig);
void					killsignal(void);
void					setup_child_signals(void);
void					check_for_sigint(t_data *data);

/* --------- Environment Functions --------- */
void					set_env(t_read *entry, char *var_name, char *contents);
void					append_env(t_read *entry, char *var_name, char *to_add);
char					*get_var(t_read *entry, char *var_name);
int						find_var_index(char **envp, char *var_name);
void					set_env_var(t_read *entry, char *var_name,
							char *contents, int i);
void					append_env_var(t_read *entry, char *to_add, int i);
char					*create_env_var(char *var_name, char *contents);
char					*get_env_value(char **envp, char *name);
int						find_in_env(char **envp, char *name);
void					create_env(t_read *entry, char *var_name,
							char *contents);
void					unset_check_null_params(t_exec *exec, t_node *node);
void					unset_free_envp_dup(char **envp_dup, int j);
void					unset_free_old_envp(char **envp);
char					**unset_alloc_new_envp(t_exec *exec);
void					unset_process_variable(t_exec *exec, char *var_name,
							char **envp_dup, int var_size);
int						handle_heredoc_fd(char *filename, t_exec *exec);
char					*heredoc(char *delimiter, t_exec *exec);
void					temp_file_create(int *fd, char **filename);
char					**alloc_split(char *in);
char					**export_split(char *in);

/* --------- I/O Functions --------- */
int						redirec(char *comm, int indesc, int outdesc,
							t_data *data);
int						open_io_fd(char *arg, char *filename, t_exec *exec);
int						replace_io_fd(int old, char *arg, char *filename,
							t_exec *exec);
void					get_io_files(t_arguements *array, t_iofiles *iostruct,
							t_exec *exec);
t_iofiles				*get_all_fds(t_arguements *array, t_exec *exec);
void					dup2_and_close(int oldfd, int newfd);
void					close_useless_fds(t_iofiles *cmdio, int **pipefds,
							t_exec *exec);
void					close_after_use(int *fd);
void					execbuiltins_closefd_1(t_node *node);
void					execbuiltins_closefd_2(t_node *node);

/* --------- Parsing Functions --------- */
char					**split_line(char *line);
char					**split_quotes(char *line);
char					**split_tokens(char **line);
char					**split_dollars(char *arg);
t_arguements			*tokenise_entry(char **split);
void					test_tokenisation(char **split, t_read *entry);
char					*strip_quotes(char *line);
void					strip_all_quotes(char **entry);
char					*expansion(t_read *entry, char *line, t_data *data);
void					replace_dollars(char **split, t_read *entry,
							t_data *data);
void					replace_dollar(char **src, t_read *entry, t_data *data);
char					*join_arg(char **split);
void					process_quote_expansion(char **quote_split,
							t_read *entry, t_data *data, int i);
void					process_str_array_creation(char **str_array, char *line,
							int *i, int *j);
char					**create_str_array(char *line);
void					copy_arguement(char *dest, char *line, int *i);
void					process_line_split(char **str_array, char *line, int *i,
							int *k);
void					process_entry_quote(char **entry, int i);
void					strcpy_until_c(char *dest, char *src, char c);
void					process_quote_section(char **ret, char *line, int *i,
							int *j);
void					process_dollar_split(char **ret, char *arg,
							t_dollar_indices *idx);
void					process_split_dollars(char **ret, char *arg,
							t_dollar_indices *idx);
void					copy_variable(char **dest, char *src, int *i, int *k);
void					fill_quote_str(char *dest, char *src, int *i, int *j);
void					fill_non_operator_str(char *dest, char *src, int *i);
void					fill_sub_str(char *dest, char *src, int *i);
void					process_src_line(char **dest, char **src, int i,
							int *k);
void					pipeline_cleanup(int **pipefds);
void					free_nodes(t_node *node);
void					fill_split(char **dest, char **src);
void					initialise_ijk(int *i, int *j, int *k);
t_node					*create_node(char **cmd, int type);
char					***get_cmd_args(t_arguements *array, int size);
void					generate_prompt(char *prompt, t_data *data);
int						ft_printf_err(const char *s, ...);
int						check_name_validity(char *name);
int						check_tokens(t_arguements *token_args);
int						check_redirections(t_arguements *token_args);
int						check_redirection_length(t_arguements *token_args);
int						get_pipes(t_arguements *array);
void					findset_operators(t_arguements *token_args);
void					findset_commands(t_arguements *token_args);
void					findset_arguments(t_arguements *token_args);
void					findset_files(t_arguements *token_args);
void					set_command_type(t_arguements *token_args, int i);
int						is_operator(char c);
int						is_whitespace(char c);
int						ft_isvalid(int c);
void					free_str_array(char **str_array);
void					append_equals(char **str);
int						subquote_count(char *line, char c);
int						process_token_check(t_arguements *argst, int i);
int						handle_quote_size(char *line, int *i);
int						getsize_stripped(char *line);
void					handle_quote_copy(char *ret, char *line, int *i,
							int *j);
void					fill_until_quote_string(char *ret, char *src);
int						count_quote_section(char *line, int *i);
char					*create_quote_string(char *src, char c);
void					fill_quote_string(char *ret, char *src, char c);
char					*dup_quotes(char *src, char c);
int						check_previous_operator(t_arguements *token_args,
							int i);
int						check_next_command(t_arguements *token_args, int i);
int						check_operators(t_arguements *token_args, int i);
char					**split_line(char *line);
void					copy_arguement(char *dest, char *line, int *i);
int						handle_quote_count(char *line, int *i);
int						handle_arg_count(char *line, int *i);
int						argcount(char *line);
int						find_dollars(char *arg);
int						get_operator_size(char *src);
int						get_non_operator_size(char *src);
int						get_size_tok(char *src);
int						handle_operator_count(char *arg, int *i);
int						count_sub_splits(char *arg);
int						get_arg_count(char **line);
void					increment_until_next_c(char *line, int *i, char c);
int						chr_present(char *str, char c);
void					expand_all_args(t_arguements *argst, t_data *data);
int						lettercount_line(char *line);
void					free_tokens(t_arguements *token_array);
void					remove_all_quotes(t_arguements *argst);

/* --------- Main Utils --------- */
void					exit_errorcode(t_data *data, int exit_code);
void					expand_all_args(t_arguements *argst, t_data *data);
void					remove_all_quotes(t_arguements *argst);
void					lexer(char *line, t_data *data, t_read *entry);
void					print_art(void);

/* --------- alloc Protection Utils --------- */
void freethreestar(void ***threestar);
void freearrayarray(void **arrayarray);

/* --------- Quote Parsing Functions --------- */
void					strip_all_quotes(char **entry);
char					*strip_quotes(char *line);
void					strcpy_until_c(char *dest, char *src, char c);
int						subquote_count(char *line, char c);
int						getsize_stripped(char *line);
void					process_quotes(char *ret, char *line, int *i, int *j);

/* --------- Expansion Functions --------- */
char					*expansion(t_read *entry, char *line, t_data *data);
char					**split_dollars(char *arg);
char					*join_arg(char **split);
void					replace_dollars(char **split, t_read *entry,
							t_data *data);
char					**create_dollar_split(char *arg);
int						ft_isvalid(int c);
int						find_dollars(char *arg);
void					initialise_ijk(int *i, int *j, int *k);
void					copy_variable(char **dest, char *src, int *i, int *k);
void					replace_dollar(char **src, t_read *entry, t_data *data);
void					handle_dollar(char **ret, char *arg, int *i, int *k);
void					process_dollar_split(char **ret, char *arg,
							t_dollar_indices *idx);
void					process_split_dollars(char **ret, char *arg,
							t_dollar_indices *idx);
char					*join_quotes(char **quote_split);
char					*get_path(char **dirs_split, char *command);

#endif
