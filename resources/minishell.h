/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fakambou <fakambou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 12:16:45 by ihhadjal          #+#    #+#             */
/*   Updated: 2025/04/16 19:57:37 by fakambou         ###   ########.fr       */
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
}							t_tokens;

typedef struct s_lexer
{
	char					*str;
	t_tokens				token_type;
	struct s_lexer			*next;
}							t_lexer;

typedef struct s_mini
{
	char					*str1;
	char					*tmp;
}							t_mini;

void						minishell_loop(t_mini *mini, char **env);
void						print_list(t_lexer *lex);
t_lexer						*get_token(char *str);
t_lexer						*lexer(char *str);
int							check_quotes(char *str);
int							is_sep(char c);
void						add_token_to_list(t_lexer **list, t_lexer *token);
void						free_lexer_list(t_lexer *list);
t_lexer						*get_word(char *str, t_lexer *token);
int							pipe_token(char *str, t_lexer *token);
int							redirec_out_token(char *str, t_lexer *token);
int							redirec_in_token(char *str, t_lexer *token);
void						quotes_loop(char **str, t_mini *mini);
void						free_all(char *str, t_lexer *lex);
void	builtin(t_lexer *builtin, char **env);

#endif