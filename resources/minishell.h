/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iheb <iheb@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 12:16:45 by ihhadjal          #+#    #+#             */
/*   Updated: 2025/04/23 14:18:47 by iheb             ###   ########.fr       */
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
	char						**new_array;
	t_parser_commands			*first_list_element;
	t_parser_commands			*new_list_element;
	t_parser_commands			*current_list_element;
	t_lexer *current_token; // current_token = lexer dans parsing;
	t_lexer *token;         // token = current_token dans redirection_handler;
	t_lexer						*new_redirec_element;
	t_lexer						*add_to_the_back;
	t_lexer						*head;
	t_lexer						*current;
	t_lexer						*filename;
    t_lexer *processed_token;

}								t_mini;

void							minishell_loop(t_mini *mini);
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
t_lexer							*redirections_and_commands_handler(t_mini *mini);
void							create_redirection_node(t_mini *mini);
void							init_new_redirection(t_mini *mini);
void								handle_heredocs(t_mini *mini);
void								handle_filename(t_mini *mini);
void							create_parser_node(t_mini *mini);
char	**add_string_to_array(char **array, char *str, t_mini *mini);
#endif