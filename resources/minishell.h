/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihhadjal <ihhadjal@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 12:16:45 by ihhadjal          #+#    #+#             */
/*   Updated: 2025/06/11 14:30:11 by ihhadjal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/header/ft_printf.h"
# include "libft/header/get_next_line.h"
# include "libft/header/libft.h"
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
# define NEWLINE_ERROR "syntax error near unexpected token `newline'"
# define HEREDOC_ERROR "syntax error near unexpected token `<<'"
# define APPEND_ERROR "syntax error near unexpected token `>>'"

typedef enum e_tokens
{
	WORD,
	PIPE,
	REDIREC_IN,
	REDIREC_OUT,
	APPEND,
	HEREDOC,
	ECHO,
	CD,
	PWD,
	EXPORT,
	UNSET,
	ENV,
	EXIT,
	ECHO2,
	FAKE_REDIREC,
	FAKE_REDIREC2,
}								t_tokens;

typedef struct s_lexer
{
	char						*str;
	t_tokens					token_type;
	struct s_lexer				*next;
}								t_lexer;

typedef struct s_parser_commands
{
	char						**cmd_str;
	int							num_redirections;
	char						*hd_file_name;
	t_lexer						*redirections;
	struct s_parser_commands	*next;
	struct s_parser_commands	*prev;
}								t_parser_commands;

typedef struct s_mini
{
	char						*str1;
	char						*tmp;
	int							i;
	int							newline;
	char						**new_array;
	char						*array_temp;
	int							last_exit_status;
	int							newline1;
	int							i1;
	int							in_single;
	int							in_double;
	t_parser_commands			*first_list_element;
	t_parser_commands			*new_list_element;
	t_parser_commands			*current_list_element;
	t_lexer						*current_token;
	t_lexer						*token;
	t_lexer						*new_redirec_element;
	t_lexer						*add_to_the_back;
	t_lexer						*head;
	t_lexer						*current;
	t_lexer						*filename;
	t_lexer						*processed_token;

}								t_mini;

typedef struct s_environnement
{
	char						*variable_name;
	char						*variable_value;
	struct s_environnement		*next;
}								t_environnement;

typedef struct s_expander
{
	int							dollar_pos;
	int							var_end;
	int							var_len;
	char						*var_name;
	t_environnement				*current1;
	char						*env_name;
	char						*expanded_variable;
	int							start;
	int							end;
	int							i;
	char						*old_str;
	t_lexer						*current;
}								t_expander;

int								minishell_loop(t_mini *mini,
									t_environnement *mini_env);
t_lexer							*get_token(char *str);
t_lexer							*lexer(char *str);
int								check_quotes(char *str);
int								is_sep(char c);
void							add_token_to_list(t_lexer **list,
									t_lexer *token);
void							free_lexer_list(t_lexer *list);
t_lexer							*get_word(char *str, t_lexer *token);
int								pipe_token(char *str, t_lexer *token);
int								redirec_out_token(char *str, t_lexer *token);
int								redirec_in_token(char *str, t_lexer *token);
void							builtin_tokens(char *str, t_lexer *lexer);
void							builtin_tokens2(char *str, t_lexer *lexer);
void							quotes_loop(char **str, t_mini *mini);
void							free_all(char *str, t_lexer *lex);
void							init_new_cmd(t_mini *mini);
t_parser_commands				*parser(t_lexer *lexer, t_mini *mini);
void							pipe_handler(t_lexer *lexer, t_mini *mini);
void							redirections_handler(t_lexer *lexer,
									t_mini *mini);
int								builtin(t_lexer *builtin,
									t_environnement *mini_env, t_mini *mini);
int								is_number(char *str);

t_lexer							*redirections_and_commands_handler(t_mini *mini);
void							create_redirection_node(t_mini *mini);
void							init_new_redirection(t_mini *mini);
void							handle_heredocs(t_mini *mini);
void							handle_filename(t_mini *mini);
void							create_parser_node(t_mini *mini);
char							**add_string_to_array(char **array, char *str,
									t_mini *mini);
void							free_parser_list(t_parser_commands *list);
void							free_redirections_list(t_lexer *list);
void							redirection_cleanup(t_mini *mini);
int								error_handling(t_lexer *lex);
void							check_next_token(t_lexer *next_lexer);
int								handle_redirection_errors(t_lexer *lex);
int								handle_redirection_errors2(t_lexer *lex);
int								fake_redirec_token(char *str, t_lexer *token);
int								export_builtin(t_lexer *builtin,
									t_environnement *mini_env);
void							init_env_container(t_environnement *env_container);
t_environnement					*get_env(char **env);
void							print_env(t_environnement *mini_env);
char							**sort_variable_name(t_environnement *mini_env);
t_environnement					*copy_env(t_environnement *mini_env);
t_environnement					*env_sort(t_environnement *env_copy);
void							value_swap(t_environnement *current,
									char *temp_value);
void							free_env_variables(t_environnement *temp);
int								export_with_arguments(t_environnement *mini_env,
									t_lexer *builtin);
t_environnement					*add_argument_to_env(t_lexer *builtin);
int								handle_unset_builtin(t_lexer *builtin,
									t_environnement *mini_env);
void							unset_builtin(t_lexer *builtin,
									t_environnement *mini_env);
void							delete_node(t_lexer *builtin,
									t_environnement **mini_env);
void							free_node(char *var_name,
									t_environnement *current);
int								get_pwd(void);
void							put_env(char **env);
int								put_echo(t_lexer *lexer, t_mini *mini);
int								cd(t_lexer *lexer);
int								ft_exit(t_lexer *lexer);
int								expansion_checker(char *str);
char							*expand_variable_value(char *str,
									t_environnement *mini_env, t_expander *exp);
void							expand_commands(t_lexer *lex,
									t_environnement *mini_env, t_expander *exp,
									t_mini *mini);
int								update_env(t_environnement *env_argument,
									t_environnement *mini_env);
int								execute_builtins(t_lexer *current,
									t_environnement *mini_env, t_mini *mini);
int								check_if_builtin(t_lexer *current,
									int command_found);
int								find_dollar(char *str);
void							substitution(t_lexer *current, int start_index,
									int end_index, char *expanded_variable);
int								find_var_end(char *str, int start);
void							handle_special_cases(t_lexer *lex,
									t_mini *mini);
char							*remove_quotes(char *str, t_mini *mini);
int								count_new_len(char *str);
void							expansion_logic(t_expander *exp,
									t_environnement *mini_env);
void							print_error(char *str1, char *str);
int								ft_symbols(char *str);
char							*handle_dollar_quote(char *str);
int								check_if_pipe(t_lexer *lex);
void							minishell_logic(t_parser_commands *pars,
									t_mini *mini, t_environnement *mini_env);
void							append_node(t_environnement *head,
									t_environnement *mini_env,
									t_environnement *current);
void							name_swap(t_environnement *current,
									char *temp_name);
int								error_print(t_lexer *builtin);
int								is_valid_export_argument(char *str,
									int name_length);
int								handle_valid_argument(t_lexer *builtin,
									t_environnement **mini_env);
int								is_not_builtin_command(t_lexer *builtin,
									int command_found);
void							process_quote(char c, t_mini *mini,
									char *new_str, int *j);
int								ft_error(t_lexer *builtin);
int								is_valid_identifier(char *str);
void							add_to_env_list(t_environnement *env_argument,
									t_environnement *mini_env);
int								process_valid_export(t_lexer *builtin,
									t_environnement *mini_env);
int								validate_and_add_export(t_lexer *builtin,
									t_environnement *mini_env);
int								execute_parsarg_builtins(t_parser_commands *pars,
									t_environnement *mini_env, t_mini *mini);
int								parsarg_echo(char **str);
int								parsarg_cd(char **str);
int								parsarg_pwd(void);
int								parsarg_exit(char **str);
int								parsarg_export(char **str,
									t_environnement *mini_env);
int								parsarg_export_with_arguments(t_environnement *mini_env,
									char **str);
int								parsarg_validate(char *str,
									t_environnement *mini_env);
int								parsarg_valid_id(char *str);
t_environnement					*parsadd_argument_to_env(char *str);
int								parsarg_valid_export(char *str,
									t_environnement *mini_env);
int								parsupdate_env(t_environnement *env_argument,
									t_environnement *mini_env);
int								parsarg_unset(char **str,
									t_environnement *mini_env);
void							parsdelete_node(char *var_to_unset,
									t_environnement **mini_env);
void							parsfree_node(char *var_name,
									t_environnement *node);

void							setup_signals(void);
void							setup_child_signals(void);
void							ignore_signals(void);
void							handle_sigint(int sig);
void							handle_sigquit(int sig);

int								execute_commands(t_parser_commands *pars,
									t_environnement *mini_env, t_mini *mini);
int								execute_pipeline(t_parser_commands *pars,
									t_environnement *mini_env, t_mini *mini);
int								execute_single_command(t_parser_commands *cmd,
									t_environnement *mini_env, t_mini *mini);
int								execute_external_command(t_parser_commands *cmd,
									t_environnement *mini_env);
int								is_builtin_command(t_parser_commands *cmd);
int								count_commands(t_parser_commands *pars);

int								execute_pipe_chain(t_parser_commands *pars,
									t_environnement *mini_env, int cmd_count);
int								**create_pipes(int pipe_count);
void							cleanup_pipes(int **pipes, int pipe_count);
void execute_pipe_processes(t_parser_commands *pars, t_environnement *mini_env, int **pipes, int *pids, int cmd_count);
void close_all_pipes_in_parent(int **pipes, int pipe_count);
int								wait_for_children(int *pids, int cmd_count);
void							execute_child_process(t_parser_commands *cmd,
									t_environnement *mini_env, int **pipes,
									int cmd_index);

int								setup_redirections(t_parser_commands *cmd);
int								handle_single_redirection(t_lexer *redir);
int								handle_input_redirection(char *filename);
int								handle_output_redirection(char *filename);
int								handle_append_redirection(char *filename);
int								handle_heredoc_redirection(char *delimiter);
void							handle_heredoc_child(int *pipefd,
									char *delimiter);
int								handle_heredoc_parent(int *pipefd, int pid);

char							**env_to_array(t_environnement *mini_env);
char							*get_env_value(char *var_name,
									t_environnement *mini_env);
char							*find_command_path(char *cmd,
									t_environnement *mini_env);
char							*create_full_path(char *dir, char *cmd);
void							free_env_array(char **env_array);
void							free_split_array(char **array);
int	handle_command_not_found(char *cmd_name, char **env_array);
void	execute_external_child(t_parser_commands *cmd, char *path,
		char **env_array);
int	wait_for_external_child(int pid, char *path, char **env_array);
void	setup_pipe_redirections(int **pipes, int cmd_index);
void	close_all_pipes(int **pipes);
int	execute_builtin_in_pipe(t_parser_commands *cmd, t_environnement *mini_env);
void	execute_external_in_pipe(t_parser_commands *cmd, t_environnement *mini_env);
int	count_env_vars(t_environnement *mini_env);
char	*create_env_string(t_environnement *env_var);
void	free_env_array_partial(char **env_array, int count);
void restore_stdio(int original_stdin, int original_stdout);
void	skip_empty_tokens(t_mini *mini);
#endif