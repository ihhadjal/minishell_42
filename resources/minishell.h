/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihhadjal <ihhadjal@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 12:16:45 by ihhadjal          #+#    #+#             */
/*   Updated: 2025/05/22 13:00:04 by ihhadjal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/header/ft_printf.h"
# include "libft/header/get_next_line.h"
# include "libft/header/libft.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

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
	t_lexer						*current;
}								t_expander;

void							minishell_loop(t_mini *mini,
									t_environnement *mini_env, t_expander *exp);
void							print_list(t_lexer *lex);
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
									t_environnement *mini_env);
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
void							export_builtin(t_lexer *builtin,
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
void							export_with_arguments(t_environnement *mini_env,
									t_lexer *builtin);
t_environnement					*add_argument_to_env(t_lexer *builtin);
void							handle_unset_builtin(t_lexer *builtin,
									t_environnement *mini_env);
void							unset_builtin(t_lexer *builtin,
									t_environnement *mini_env);
void							delete_node(t_lexer *builtin,
									t_environnement **mini_env);
void							free_node(char *var_name,
									t_environnement *current);
int								get_pwd(void);
void							put_env(char **env);
void							put_echo(t_lexer *lexer);
int								cd(t_lexer *lexer);
int								ft_exit(t_lexer *lexer);
int								expansion_checker(char *str);
char							*expand_variable_value(char *str,
									t_environnement *mini_env, t_expander *exp);
void							expand_commands(t_lexer *lex,
									t_environnement *mini_env, t_expander *exp);
int								update_env(t_environnement *env_argument,
									t_environnement *mini_env);
void							execute_builtins(t_lexer *current,
									t_environnement *mini_env);
int								check_if_builtin(t_lexer *current,
									int command_found);
int								find_dollar(char *str);
void							substitution(t_lexer *current, int start_index,
									int end_index, char *expanded_variable);
int								find_var_end(char *str, int start);
#endif