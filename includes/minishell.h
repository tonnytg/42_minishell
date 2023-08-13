/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caalbert <caalbert@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 02:55:02 by antthoma          #+#    #+#             */
/*   Updated: 2023/08/11 12:25:09 by caalbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/* Libs */
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <signal.h>
# include <sys/wait.h>
# include "../libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>

/* Macros */
# define ECHO_BUILTIN	"echo"
# define CD_BUILTIN		"cd"
# define PWD_BUILTIN	"pwd"
# define EXPORT_BUILTIN	"export"
# define UNSET_BUILTIN	"unset"
# define ENV_BUILTIN	"env"
# define EXIT_BUILTIN	"exit"
# define TEST_FD		"test_fd"

# define STDIN_FILENO 0
# define STDOUT_FILENO 1
# define STDERR_FILENO 2

# define HEAD 1
# define MID 2
# define TAIL 3

# define DGREAT 0
# define GREAT 1

# define READ 0
# define CREATE 1
# define APPEND 2
# define HEREDOC 3

# define S_DEFAULT 0
# define S_RECEIVER 1
# define S_SENDER 2
# define S_SKIP_NEXT_FD 3
# define S_PIPED 4
# define S_DLESS_CURRENT 5

/* Structs */
struct	s_cmds;
struct	s_command;
struct	s_cmd_node;

typedef struct s_tk_node
{
	char				token[256];
	char				tk_type[256];
	struct s_tk_node	*next;
}	t_tk_node;

/* Each Command */
typedef struct s_command
{
	char	*name;
	int		(*execute)(struct s_cmds *);
}	t_command;

typedef struct s_cmd_node
{
	char				*phrase;
	int					disabled;
	int					strategy;
	char				*phrase_temp;
	char				**phrase_parsed;
	int					is_active_to_run;
	char				*cmd_name;
	char				*full_args;
	char				**split_args;
	t_command			*cmd_builtin;
	char				*type;
	int					position;
	pid_t				pid;
	int					fd[2];
	int					fd_backup_in;
	int					fd_backup_out;
	int					fd_is_active;
	int					fd_file_is_active;
	int					fd_file;
	int					file_type;
	int					*fd_ptr_input;
	int					*fd_ptr_output;
	struct s_cmd_node	*next;
	struct s_cmd_node	*prev;
}	t_cmd_node;

typedef struct s_exit_code
{
	int		code;
	char	*msg;
}	t_exit_code;

/* Read Keyboard command and arguments */
typedef struct s_input
{
	char		*data;
	char		*datacpy;
	char		*cmd_name;
	char		*cmd_args;
	char		**phrase;
}	t_input;

typedef struct s_here_doc{
	char	buffer[1024];
	char	*eof_keyword;
	char	*content;
	ssize_t	bytes_read;
	size_t	total_size;
	size_t	buffer_size;
	ssize_t	bytes_written;
}	t_here_doc;

typedef struct s_env_convert
{
	int		trigger;
	int		rest_active;
	char	*converted;
	char	rest[256];
	char	word[256];
	char	*converted_arr;
	char	**arr;
	int		i;
	int		r;
	int		w;
	int		a;
}	t_env_convert;

typedef struct s_cmd_build
{
	t_tk_node	*actual_tk;
	char		*temp;
	int			first_word;
	char		*str;
	int			has_quote;
}	t_cmd_build;

typedef struct s_envs
{
	char	*name;
	char	*value;
}	t_envs;

typedef struct s_path
{
	char	**path;
	int		i;
	char	*path_complete;
	int		return_access;
	char	*name;
}	t_path;

typedef struct s_strategy
{
	int	strategy;
	int	c_words;
	int	c_pipe;
	int	c_dgreat;
	int	c_great;
	int	c_dless;
	int	c_less;
	int	c_unknown;
}	t_strategy;

/* Array of commands */
typedef struct s_cmds
{
	t_input		*input;
	t_command	*cmd_finded;
	size_t		num_cmds;
	t_command	*arr_cmds;
	int			strategy;
	int			has_quote;
	int			is_quote_opened;
	t_path		*path;
	t_exit_code	exit_code;
	char		**lexical;
	char		**envs;
	t_cmd_node	*cmd_list;
	t_cmd_node	*current;
	int			cmds_list_count;
	int			exit;
	int			signal_exit;
	int			redirects_count;
	t_exit_code	strategy_error;
	int			signal;
	int			new;
	void		(*signal_handler)(int);
	char		*previous_dir;
}	t_cmds;

/* file */
void		create_fd_file(t_cmds *cmds);
void		open_file(t_cmds *cmds);
void		save_file(t_cmds *cmds);
void		read_file(t_cmds *cmds, char *file_name, int *write_in);

/* Here Document */
void		here_doc(t_cmds *cmds);

/* Commands */
void		find_command(t_cmds *cmds);
int			count_nodes(t_cmds *cmds);
void		exec_builtin(t_cmds *cmds);
void		run_node(t_cmds *cmds);
void		load_commands(t_cmds *cmds);

/* Types Commands */
void		exec_builtin(t_cmds *cmds);
void		exec_external(t_cmds *cmds);
void		exec_redirect(t_cmds *cmds);
int			check_type_command(t_cmds *cmds);

/* Path */
char		*check_path(t_cmd_node *node);
char		*get_fullpath(t_cmds *cmds);
void		free_split(char **split_array);

/* Builtins */
int			echo_adapter(t_cmds *cmds);
int			cd_adapter(t_cmds *cmds);
int			env_adapter(t_cmds *cmds);
int			test_fd_adapter(t_cmds *cmds);
int			unset_adapter(t_cmds *cmds);
int			pwd_adapter(t_cmds *cmds);
int			exit_adapter(t_cmds *cmds);
int			export_adapter(t_cmds *cmds);
void		execute_cmd(t_cmds *cmds);
void		set_commands(t_cmds *cmds);
void		free_commands(t_cmds *cmds);

/* Strategy */
void		set_strategy(t_cmds *cmds);
void		run_strategy(t_cmds *cmds);
void		check_dless(t_cmds *cmds);
void		check_less(t_cmds *cmds);
void		check_pipe(t_cmds *cmds);
void		write_in_fd(t_cmds *cmds, char *msg);
char		*read_from_file(t_cmds *cmds);
void		run_strategy_piped(t_cmds *cmds);
void		set_piped_stdout(t_cmds *cmds);
void		set_restore_stdout(t_cmds *cmds);
void		strategy_has_errors(t_cmds *cmds);
void		check_great(t_cmds *cmds);

/* Export Command Utils srcs/builtins/export_utils.c */
void		save_converted_word(t_cmds *cmds, t_env_convert *env_c);
void		save_rest(t_env_convert *env_c);
void		search_for_word(t_cmds *cmds, t_env_convert *env_c,
				const char *value);
void		search_for_rest(t_env_convert *env_c, const char *value);

/* Commands */
void		init_interpreter(t_cmds *cmds);

/* Interpreter */
void		parse_values_args(t_cmds *cmds);
char		*parse_to_folder(t_cmds *cmds, char *str);

/* Command Echo echo_utils2.c */
int			echo_arg_with_quotes(t_cmds *cmds);

/* Pipes */
void		open_pipe(t_cmds *cmds);
int			count_pipes(t_cmds *cmds, char *str);
void		connect_nodes_with_pipes(t_cmds *cmds);
void		set_head_word_fd(t_cmds *cmds);
void		set_mid_word_fd(t_cmds *cmds);
void		set_mid_redirect_fd(t_cmds *cmds);
void		set_tail_word_fd(t_cmds *cmds);

/* Quotes srcs/quotes/quotes.c */
int			is_single_quote(char *str);
int			is_double_quote(char *str);
char		*remove_single_quotes(t_cmds *cmds);
char		*remove_double_quotes(t_cmds *cmds);
int			check_quotes(t_cmds *cmds);
int			search_code_caracter(char *str);

/* Redirects */
void		check_exist_redirect(t_cmds *cmds);

/* Set envs */
int			set_env_var(t_cmds *cmds, char *key, char *value);
void		set_envs(char **envp, t_cmds *cmds);
int			count_envp(char **envp);
int			append_envs(t_cmds *cmds, char *name, char *value);
void		free_envs(t_cmds *cmds);
//char		*get_env(char *str, int config);
char		*get_env(t_cmds *cmds, char *str, int config);
char		*getvarenv(t_cmds *cmds, char *var);

/* Syntax Analysis */
void		syntax_analysis(t_cmds *cmds);
void		build_struct_to_exec(t_cmds *cmds, t_tk_node *list_tokens);
void		free_cmd_nodes(t_cmd_node *list_cmds);
void		check_quote(char *word, t_cmd_build *cmds);

/* Token Analysis */
int			token_analysis(t_cmds *cmds);

/* Read Keyboard */
int			read_keyboard(t_cmds *cmds);
char		*check_data_input(t_cmds *cmds);
int			is_empty_data(t_cmds *cmds);

/* Signals (signals.c) */
void		load_signals(void);
void		signal_generic_handler(int signal);

/* Minishell Utils */
int			interactive_exit(t_cmds *cmds);
void		free_arr(char **arr);
char		*remove_string(char *str, char to_remove);
int			count_arr(char **arr);

/* Minishell Utils minishell_utils2.c */
int			count_all_len_in_arr(char **arr);
char		*concatenate_strings(char **arr, char c);

/* Minishell  main.c */
int			minishell(t_cmds *cmds);

char		*get_correct_path(t_cmds *cmds, char *input_path);
int			change_directory(t_cmds *cmds, char *path, char *temp);
int			cd_adapter(t_cmds *cmds);
char		*ft_strsub(char const *s, unsigned int start, size_t len);
char		*parse_to_folder(t_cmds *cmds, char *str);
void		parse_values_args(t_cmds *cmds);
void		prepare_phrase(t_cmds *cmds);
void		init_interpreter(t_cmds *cmds);
char		*get_env_value(t_cmds *cmds, char *name);
// char		*handle_tilde_path(t_cmds *cmds, char *str);
// char		*handle_relative_path(t_cmds *cmds, char *str);
#endif